//
// DFA Test File
//
#include "DFA.h"

DFA DFA_for_contains_ullman()
{
    // number of states : 7
    //initial state : 0
    //accepting states [6]
    DFA d = new_DFA(7); //this is a dfa pointer with 7 states

    DFA_set_transition_all(d, 0, -1);

    //now set values in the transition table
    DFA_set_transition(d, 0, 'u', 1);
    DFA_set_transition(d, 1, 'l', 2);
    DFA_set_transition(d, 2, 'l', 3);
    DFA_set_transition(d, 3, 'm', 4);
    DFA_set_transition(d, 4, 'a', 5);
    DFA_set_transition(d, 5, 'n', 6);
    DFA_set_accepting_default(d);
    DFA_set_accepting(d, 6, true);
    DFA_set_accepting(d, 0, false);
    DFA_set_accepting(d, 1, false);
    DFA_set_accepting(d, 2, false);
    DFA_set_accepting(d, 3, false);
    DFA_set_accepting(d, 4, false);
    DFA_set_accepting(d, 5, false);
    return d;
}

DFA DFA_for_starts_with_com()
{
    //having problems with this one
    //number of states : 4
    //accepting state : [3]
    //initial state : 0

    DFA d = new_DFA(4);

    DFA_set_transition_all(d, 0, -1);
    DFA_set_transition(d, 0, 'c', 1);
    DFA_set_transition(d, 1, 'o', 2);
    DFA_set_transition(d, 2, 'm', 3);
    for (int j = 0; j < 128; j++)
    {
        char c = j;
        DFA_set_transition(d, 3, c, 3);
    }
    //setting accepting states
    DFA_set_accepting_default(d);
    DFA_set_accepting(d, 3, true);
    DFA_set_accepting(d, 0, false);
    DFA_set_accepting(d, 1, false);
    DFA_set_accepting(d, 2, false);
    return d;
}

DFA DFA_for_contains_threes()
{

    DFA d = new_DFA(4);
    DFA_set_transition_all(d, 0, -1);

    for (int j = 0; j < 128; j++)
    {
        //setting self loops for all characters for state 0, 1 and 2
        if (j != 51)
        {
            char c = j;
            DFA_set_transition(d, 0, c, 0);
            DFA_set_transition(d, 1, c, 1);
            DFA_set_transition(d, 2, c, 2);
            DFA_set_transition(d, 3, c, 3);
        }
    }

    //since DFA should not have self loop when it's 3 input
    //set the correct transition
    DFA_set_transition(d, 0, '3', 1);
    DFA_set_transition(d, 1, '3', 2);
    DFA_set_transition(d, 2, '3', 3);

    //setting accepting states
    DFA_set_accepting_default(d);
    DFA_set_accepting(d, 3, true);
    DFA_set_accepting(d, 0, false);
    DFA_set_accepting(d, 1, false);
    DFA_set_accepting(d, 2, false);
    return d;
}

DFA DFA_for_contains_even0odd1()
{
    //number of states : 4
    // initial state : 1
    // accepting states : [1]
    DFA d = new_DFA(4);

    DFA_set_transition_all(d, 0, -1);

    DFA_set_transition_all(d, 0, -1);
    DFA_set_transition(d, 0, '0', 1);
    DFA_set_transition(d, 0, '1', 3);

    DFA_set_transition(d, 1 , '0', 0);
    DFA_set_transition(d, 1 , '1', 2);

    DFA_set_transition(d, 2 , '0', 3);
    DFA_set_transition(d, 2 , '1', 1);

    DFA_set_transition(d, 3 , '0', 2);
    DFA_set_transition(d, 3 , '1', 0);

    DFA_set_accepting_default(d);
    DFA_set_accepting(d, 3, true);
    DFA_set_accepting(d, 0, false);
    DFA_set_accepting(d, 1, false);
    DFA_set_accepting(d, 2, false);
    return d;
}

void DFA_repl(DFA dfa)
{
    char input[256];
    char *p = input; //pointer of the string input
    char quit[5] = "quit"; //quit input string

    int valid = 1;
    while(valid == 1)
    {

        printf("Enter an input (type quit to quit): ");
        scanf("%s", input);
        int value = strcmp(input,quit);
        if (value == 0)
        {
            valid = 0;
        }
        else
        {
            bool bool_result = DFA_execute(dfa, p);
            printf("Result for input '%s': %s \n", input, bool_result ? "true" : "false");
            valid = 1;

        }
    }
    DFA_free(dfa);
}


int main(int argc, char *argv[])
{
    printf("\nTesting DFA where the string is exactly 'ullman' ...\n");
    DFA_repl(DFA_for_contains_ullman());
    //DFA_free(DFA_for_contains_ullman());

    printf("\nTesting DFA where the string starts with 'com' ... \n");
    DFA_repl(DFA_for_starts_with_com());

    printf("\nTesting DFA where string contains exactly three 3s ... \n");
    //DFA_print(DFA_for_contains_threes());
    DFA_repl(DFA_for_contains_threes());

    printf("\nTesting DFA where binary input contains even number of 0s and odd number of 1s ... \n");
    DFA_repl(DFA_for_contains_even0odd1());

    return 0;
}

