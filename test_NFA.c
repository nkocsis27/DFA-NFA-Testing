//
// NFA Test File
//
#include "nfa.h"


//Gets user input of string
void NFA_repl(NFA nfa)
{
    char input[256];
    char *p = input; //pointer of the string input
    char quit[5] = "quit";

    int valid = 1;
    while(valid == 1)
    {
        printf("Enter an input (type quit to quit): \n");
        scanf("%s", input); //takes in input

        int value = strcmp(input,quit); //comparing the given input and quit string
        if (value == 0)
        {
            //quit the program since the input was quit
            valid = 0;
        }
        else
        {
            bool bool_result = NFA_execute(nfa, p);
            //printing results
            printf("Result for input '%s': %s \n", input, bool_result ? "true" : "false");
            valid = 1;

        }
    }
    //frees all members of NFA
    NFA_free(nfa);
}

NFA NFA_for_ends_with_gs()
{
    //number of states : 3
    //accepting states 2
    //initial state : 0

    NFA n = new_NFA(3);

    //default for every value in transition
    NFA_add_transition_all(n, 0, 0); //any input at state zero stays state o

    NFA_add_transition(n, 0, 'g', 1);
    NFA_add_transition(n, 1, 's', 2);

    NFA_set_accepting_default(n); //sets the accepting states array to all -1 values
    NFA_set_accepting(n, 0, false);
    NFA_set_accepting(n, 1, false);
    NFA_set_accepting(n, 2, true);

    return n;
}

NFA NFA_for_contains_mas()
{
    NFA n = new_NFA(4);

    //default for every value in transition
    NFA_add_transition_all(n, 0, 0); //any input at state zero stays state o
    NFA_add_transition_all(n, 3, 3);

    NFA_add_transition(n, 0, 'm', 1);
    NFA_add_transition(n, 1, 'a', 2);
    NFA_add_transition(n, 2, 's', 3);

    NFA_set_accepting_default(n);
    NFA_set_accepting(n, 0, false);
    NFA_set_accepting(n, 1, false);
    NFA_set_accepting(n, 2, false);
    NFA_set_accepting(n,3,true);

    return n;
}

NFA NFA_not_anagram_codebreaker()
{
    NFA n = new_NFA(20);

    //add the self loops for any character
    NFA_add_transition_all(n,2,2);
    NFA_add_transition_all(n,4,4);
    NFA_add_transition_all(n,6,6);
    NFA_add_transition_all(n,8,8);
    NFA_add_transition_all(n,10,10);
    NFA_add_transition_all(n,12,12);
    NFA_add_transition_all(n,15,15);
    NFA_add_transition_all(n,19,19);

    //add specific transition given a character
    NFA_add_transition(n,0,'a',1);
    NFA_add_transition(n,1,'a', 2);

    NFA_add_transition(n,0,'b',3);
    NFA_add_transition(n,3,'b', 4);

    NFA_add_transition(n,0,'c', 5);
    NFA_add_transition(n,5,'c', 6);

    NFA_add_transition(n,0,'d', 7);
    NFA_add_transition(n,7,'d', 8);

    NFA_add_transition(n,0,'k', 9);
    NFA_add_transition(n,9,'k', 10);

    NFA_add_transition(n,0,'o', 11);
    NFA_add_transition(n,11,'o', 12);

    NFA_add_transition(n,0,'r', 13);
    NFA_add_transition(n,13,'r', 14);
    NFA_add_transition(n,14,'r', 15);

    NFA_add_transition(n,0,'e', 16);
    NFA_add_transition(n,16,'e', 17);
    NFA_add_transition(n,17,'e', 18);
    NFA_add_transition(n,18,'e', 19);

    NFA_add_transition_all(n, 0, 0); //self loop for all characters at start

    //self loop for every character EXCEPT one specific character using it's ascii value
    for (int i = 0; i < 128; i++) {
        if (i != 97) {
            NFA_add_transition(n,1,i,1);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 98) {
            NFA_add_transition(n,3,i,3);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 99) {
            NFA_add_transition(n,5,i,5);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 100) {
            NFA_add_transition(n,7,i,7);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 107) {
            NFA_add_transition(n,9,i,9);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 111) {
            NFA_add_transition(n,11,i,11);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 114) {
            NFA_add_transition(n,13,i,13);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 114) {
            NFA_add_transition(n,14,i,14);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 101) {
            NFA_add_transition(n,16,i,16);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 101) {
            NFA_add_transition(n,17,i,17);
        }
    }
    for (int i = 0; i < 128; i++) {
        if (i != 101) {
            NFA_add_transition(n,18,i,18);
        }
    }

    //sets accepting array positions all to -1
    NFA_set_accepting_default(n);

    //false states
    NFA_set_accepting(n, 0, false);
    NFA_set_accepting(n, 1, false);
    NFA_set_accepting(n, 3, false);
    NFA_set_accepting(n, 5, false);
    NFA_set_accepting(n, 7, false);
    NFA_set_accepting(n, 9, false);
    NFA_set_accepting(n, 11, false);
    NFA_set_accepting(n, 13, false);
    NFA_set_accepting(n, 14, false);
    NFA_set_accepting(n, 16, false);
    NFA_set_accepting(n, 17, false);
    NFA_set_accepting(n, 18, false);

    //true states
    NFA_set_accepting(n,32,true);
    NFA_set_accepting(n, 2, true);
    NFA_set_accepting(n, 4, true);
    NFA_set_accepting(n, 6, true);
    NFA_set_accepting(n, 8, true);
    NFA_set_accepting(n, 10, true);
    NFA_set_accepting(n, 12, true);
    NFA_set_accepting(n, 15, true);
    NFA_set_accepting(n, 19, true);

    return n;
}

int main(int argc, char *argv[])
{
    //prompts user which pattern is being tested
    printf("\nTesting NFA where the string ends in 'gs'...\n");
    //calls method to test that pattern
    NFA_repl(NFA_for_ends_with_gs());
    printf("\nTesting NFA where string contains 'mas'...\n");
    NFA_repl(NFA_for_contains_mas());
    printf("\nTesting NFA where the string is not anagram...\n ");
    NFA_repl(NFA_not_anagram_codebreaker());

    return 0;
}

