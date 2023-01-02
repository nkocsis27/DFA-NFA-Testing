# DFA-NFA-Testing
Deterministic Finite Automaton and Nondeterministic Finite Automaton are being used to test on specific word patterns.

For DFA:
Compile portion: gcc  -std=c99 -Wall -Werror DFA.c test_DFA.c -o test_DFA
Run portion: ./test_DFA

For NFA:
Compile portion: gcc -std=c99 -Wall -Werror nfa.c test_NFA.c BitSet.c -o test_NFA
Run portion: ./test_NFA

