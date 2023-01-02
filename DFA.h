//
// DFA Header File
//


#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct DFA *DFA;

/**
 * Allocate and return a new DFA containing the given number of states.
 */
extern DFA new_DFA(int nstates);

/**
 * Free the given DFA.
 */
extern void DFA_free(DFA dfa);

/**
 * Return the number of states in the given DFA.
 */
extern int DFA_get_size(DFA dfa);

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
extern int DFA_get_transition(DFA dfa, int src, char sym);

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
extern void DFA_set_transition(DFA dfa, int src, char sym, int dst);

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
extern void DFA_set_transition_str(DFA dfa, int src, char *str, int dst);

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
extern void DFA_set_transition_all(DFA dfa, int src, int dst);

extern void DFA_set_accepting_default(DFA dfa);

/**
 * Set whether the given DFA's state is accepting or not.
 */
extern void DFA_set_accepting(DFA dfa, int state, bool value);

/**
 * Return true if the given DFA's state is an accepting state.
 */
extern bool DFA_get_accepting(DFA dfa, int state);

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool DFA_execute(DFA dfa, char *input);

/**
 * Print the given DFA to System.out.
 */
extern void DFA_print(DFA dfa);
