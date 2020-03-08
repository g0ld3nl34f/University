#ifndef AFD
#define AFD

#include <stdio.h>
#include <stdlib.h>

struct transition;

struct transition *new_transition(char needed_symbol, short to_this_state);
_Bool can_transition(struct transition *this_transition, char needed_symbol);
_Bool free_transition(struct transition *this_transition);

struct state;

struct state *new_state(_Bool acception_state);
_Bool add_transition_to_state(struct state *this_state, struct transition *new_transition, short symbol);
_Bool free_state(struct state *this_state);

struct afd;

struct afd *new_afd(short n_state, short n_symbols);
_Bool add_state_to_afd(struct afd *this_afd, struct state *new_state);
short change_state_in_afd(struct afd *this_afd, short curr_state, char symbol_for_transition);
_Bool word_accepted_by_afd(struct afd *this_afd, short curr_state);
_Bool free_afd(struct afd *this_afd);


#endif