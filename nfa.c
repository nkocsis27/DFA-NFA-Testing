//
// NFA Source File
//

#include "nfa.h"

//members of NFA
struct NFA{
    int* statesarr; //int array pointer to the states
    int totalstates; //int for total states
    int initialstate; //int for initial state
    int* acceptingstates; //int array pointer for accepting states
    BitSet** transitionstates; //2d array pointer as type bitset
};

/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates)
{
    NFA n = (NFA)malloc(sizeof(struct NFA)); //creating a pointer for the DFA struct
    n->totalstates = nstates; //setting total number of states
    n->statesarr = (int*)calloc(n->totalstates, sizeof(int));
    n->initialstate = 0; //setting the initial state to 0
    n->acceptingstates = (int*)calloc(n->totalstates, sizeof(int));
    n->transitionstates = (BitSet**)calloc(n->totalstates, sizeof(BitSet*));
    for (int i = 0; i <n->totalstates; i++)
    {
        n->transitionstates[i] = (BitSet*)calloc(128, sizeof(BitSet));
    }

    //populating transition table with empty bit sets
    for (int r  = 0 ; r < n->totalstates; r++)
    {
        for (int c = 0; c < 128; c++)
        {
            BitSet b = new_BitSet();
            n->transitionstates[r][c] = b;
        }
    }
    return n;
}

/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa)
{
    free(nfa->statesarr);
    free(nfa->acceptingstates);
    for (int i = 0; i < nfa->totalstates; i++)
    {
        free(nfa->transitionstates[i]);
    }
    free(nfa->transitionstates);
    free(nfa);
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa)
{
   return nfa->totalstates;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
BitSet NFA_get_transitions(NFA nfa, int state, char sym)
{
    int ascii = sym; //converting character to int
    return nfa->transitionstates[state][ascii];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
    int ascii = sym; //converting character to int
        if (!BitSet_lookup(nfa->transitionstates[src][ascii], dst))
        {
            BitSet_insert(nfa->transitionstates[src][ascii], dst);
        }
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst)
{
    for (int i = 0; i < strlen(str); i++)
    {
        char c = str[i]; //takes character from input
        int ascii = c; //converts char to ascii value
        BitSet bitsetfortransarray = nfa->transitionstates[src][ascii];
        BitSet this_bitset = new_BitSet();
        BitSet_insert(this_bitset, dst);
        BitSet_union(bitsetfortransarray, this_bitset);
        nfa->transitionstates[src][ascii] = bitsetfortransarray;
    }
}
/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst)
{
    for (int i = 0; i < 128; i++)
    {
        if (!BitSet_lookup(nfa->transitionstates[src][i], dst))
        {
            BitSet_insert(nfa->transitionstates[src][i], dst);
        }
    }

}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value)
{
    if (value == true) //if state is accepting state
    {
        for (int i = 0; i < nfa->totalstates; i++)
        {
            if (nfa->acceptingstates[i] == -1)
            {
                nfa->acceptingstates[i] = state;
                break;
            }
        }
    }
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state)
{

    //state is the current state NFA is at
    for (int i = 0; i < nfa->totalstates; i++)
    {
        if (state == nfa->acceptingstates[i])
        {
            return true;
        }
    }
    return false;
}

//sets max number of accepting states to all -1
void NFA_set_accepting_default(NFA nfa)
{
    for (int i = 0; i < NFA_get_size(nfa); i++)
    {
        nfa->acceptingstates[i] = -1; //initialize state array to -1
    }
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input)
{
    int currstate = nfa->initialstate;
    BitSet possiblestates = new_BitSet();//creating s bitset of possible states
    BitSet_insert(possiblestates, currstate);
    int string_length = strlen(input);

    for (int i = 0; i < string_length; i++)
    {
        char symbol = input[i]; //reading the symbol
        BitSet newbitset = new_BitSet();
        //create an iterator for bitset NOTE need to free this
        BitSetIterator bsi = BitSet_iterator(possiblestates);
        while (BitSetIterator_hasNext(bsi))
        {
            int nextbit = BitSetIterator_next(bsi);
            BitSet nextstates = NFA_get_transitions(nfa, nextbit, symbol);
            BitSet_union(newbitset, nextstates);

        }
        free(bsi); //free the iterator
        BitSet_free(possiblestates); //free the possible states bitset
        possiblestates = newbitset;
        BitSet_union(possiblestates, newbitset);
    }

    //checking if there are any accepting states in the possible states set
    for (int i = 0; i < nfa->totalstates; i++)
    {
        int acceptstate = nfa->acceptingstates[i];
        BitSetIterator new_bsi = BitSet_iterator(possiblestates);
        while (BitSetIterator_hasNext(new_bsi))
        {
            if (BitSetIterator_next(new_bsi) == acceptstate)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa)
{
    printf("size of array: %d\n", NFA_get_size(nfa));
    //this will print out transition table
    printf("transition table\n");

    for (int i = 0; i < NFA_get_size(nfa); i++)
    {
        for (int j = 0; j < 128; j++)
        {
            char c = j;
            printf("printing bitset at state %d and character %c\n", i, c);
            BitSet_print(nfa->transitionstates[i][j]);
        }
    }

    printf("accepting states: \n");
    //this will print out the accepting states
    for (int i = 0; i < NFA_get_size(nfa); i++)
    {
        printf("%d",nfa->acceptingstates[i]);
    }

}