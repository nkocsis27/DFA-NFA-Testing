#include "DFA.h"


struct DFA{
    int totalstates; //int for total number of states
    int* statesarr; //pointer for int array for the states
    int initialstate; //int for initial state
    int* acceptingstates; //pointer for int array accepting states
    int** transitionstates; //pointer for a 2d int array - there will be
    //pointers inside each element of 1d array for a pointer of another
    //array
};

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates)
{
    DFA d = (DFA)malloc(sizeof(struct DFA)); //creating a pointer for the DFA struct
    d->totalstates = nstates; //settings the total number of states
    d->statesarr = (int*)calloc(d->totalstates, sizeof(int)); //allocating a pointer for the memory of array of states
    d->initialstate = 0; //setting the initial state to 0
    d->acceptingstates = (int*)calloc(d->totalstates, sizeof(int)); //allocating memory for a pointer for accepting
    // states array

    d->transitionstates = (int**)calloc(d->totalstates, sizeof(int*)); //allocating memory for a 2D pointer
    for (int i = 0; i <d->totalstates; i++)
    {
        d->transitionstates[i] = (int*)calloc(128, sizeof(int)); //int array pointer for each row array
    }

    return d; //returns a pointer for dfa
}

/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa)
{
    free(dfa->statesarr);
    free(dfa->acceptingstates);
    for (int i = 0; i <dfa->totalstates; i++)
    {
        free(dfa->transitionstates[i]);
    }
    free(dfa->transitionstates);
    free(dfa);
}
/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa)
{
    return dfa->totalstates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym)
{
    int j = sym; //converting char to ascii value
    return dfa->transitionstates[src][j];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst)
{
    int j = sym; //converting char to ascii value
    dfa->transitionstates[src][j] = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst)
{
    for (int i = 0; i < strlen(str); i++)
    {
        char c = str[i];
        int j = c;
        dfa->transitionstates[src][j] = dst;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst)
{
    for (int r = 0; r < dfa->totalstates; r++) //iterating through the rows of transition table
    {
        for (int c = 0; c < 128; c++) //iterating through the 128 possible symbol inputs
        {
            dfa->transitionstates[r][c] = dst;
        }
    }
}

void DFA_set_accepting_default(DFA dfa)
{
    for (int i = 0; i < sizeof*(dfa->acceptingstates); i++)
    {
        dfa->acceptingstates[i] = -1; //every position in accepting array is -1
    }
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value)
{
    if (value == true) //if state is accepting state
    {
        for (int i = 0; i < dfa->totalstates; i++)
        {
            if (dfa->acceptingstates[i] == -1)  //if accepting state array is -1 at given position
            {
                dfa->acceptingstates[i] = state; //add the state to the accepting state array
            }
        }
    }
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state)
{
    for (int i = 0; i < dfa->totalstates; i++)
    {
        if (state == dfa->acceptingstates[i])
        {
            return true;
        }
    }
    return false;
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 * //note this is the same function as DFA_run in the project instructions
 */
bool DFA_execute(DFA dfa, char *input)
{
    int currstate = dfa->initialstate; //current state starts at 0
    int string_length = strlen(input);
    for (int i = 0; i < string_length; i++) //iterating through the string input
    {
        currstate = DFA_get_transition(dfa, currstate, input[i]); //get the current state from transition table
        if (currstate == -1)
        {
            return false;
        }
    }

    //once entire character in string is looked at,
    // check to see if it's in accepting state or not
    if (DFA_get_accepting(dfa, currstate) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa)
{
    //print the size of the array
    printf("size of array: %d\n", DFA_get_size(dfa));
    //this will print out transition table
    printf("transition table\n");
    for (int i = 0; i < DFA_get_size(dfa); i++)
    {
        for (int j = 0; j < 128; j++)
        {
            char c = j;
            printf("at state %d and char input %c: %d\n", i, c, dfa->transitionstates[i][j]);
        }
    }
    printf("accepting states");
    //this will print out the accepting states
    for (int i = 0; i < DFA_get_size(dfa); i++)
    {
        printf("%d", dfa->acceptingstates[i]);
    }
}