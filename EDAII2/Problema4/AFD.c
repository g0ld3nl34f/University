#include <stdio.h>
#include <stdlib.h>
#include "AFD.h"

#define MAX_STATES 100

//Pair symbol/state in order to confirm state transition using the given symbol
struct transition
{
	char needed_symbol;
	short to_this_state;
};

//Initialization of a transition
struct transition *new_transition(char needed_symbol, short to_this_state)
{
	struct transition *new = malloc(sizeof(struct transition));

	new -> needed_symbol = needed_symbol;
	new -> to_this_state = to_this_state;

	return new;
}

_Bool can_transition(struct transition *this_transition, char needed_symbol)
{
	if (this_transition -> needed_symbol == needed_symbol)
	{
		return 1;
	}

	return 0;
}

//Freeing of a transition
_Bool free_transition(struct transition *this_transition)
{
	free(this_transition);

	if (this_transition == NULL)
	{
		return 1;
	}

	return 0;
}

//Saves the information of a state
//If it is an acception state and all possible transitions to other states with given symbols
struct state
{
	_Bool acception_state;
	struct transition *possible_transitions[MAX_STATES];
};

//Initialization of a state
//Transitions are't initialized, at this point they are still unknown
struct state *new_state(_Bool acception_state)
{
	struct state *new = malloc(sizeof(struct state));

	new -> acception_state = acception_state;

	for (int i = 0; i < MAX_STATES; ++i)
	{
		new -> possible_transitions[i] = NULL;
	}

	return new;
}

_Bool add_transition_to_state(struct state *this_state, struct transition *new_transition, short symbol)
{
	if (this_state -> possible_transitions[symbol] != NULL)
	{
		return 0;
	}

	this_state -> possible_transitions[symbol] = new_transition;

	if (this_state -> possible_transitions[symbol] == NULL)
	{
		return 0;
	}

	return 1;

}

//Freeing of a state
_Bool free_state(struct state *this_state)
{
	for (int i = 0; i < MAX_STATES; ++i)
	{
		if (this_state -> possible_transitions[i] != NULL)
		{
			free_transition(this_state -> possible_transitions[i]);
		}
	}

	free(this_state);

	if (this_state == NULL)
	{
		return 1;
	}

	return 0;
}

struct afd
{
	short n_states, n_symbols; //Probably unecessary
	struct state *states[MAX_STATES];
};

struct afd *new_afd(short n_states, short n_symbols)
{
	struct afd *new = malloc(sizeof(struct afd));

	new -> n_states = n_states;
	new -> n_symbols = n_symbols;

	for (int i = 0; i < n_states; ++i)
	{
		new -> states[i] = NULL;
	}

	return new;
}

_Bool add_state_to_afd(struct afd *this_afd, struct state *new_state)
{
	for (int i = 0; i < MAX_STATES; ++i)
	{
		if (this_afd -> states[i] == NULL)
		{
			this_afd -> states[i] = new_state;

			return 1;
		}
	}

	return 0;
}

short change_state_in_afd(struct afd *this_afd, short curr_state, char symbol_for_transition)
{
	if (this_afd -> states[curr_state] != NULL)
	{
		for (int i = 0; i < MAX_STATES; ++i)
		{
			if (this_afd -> states[curr_state] -> possible_transitions[i] != NULL)
			{
				if (can_transition(this_afd -> states[curr_state] -> possible_transitions[i], symbol_for_transition))
				{
					return this_afd -> states[curr_state] -> possible_transitions[i] -> to_this_state;
				}
			}

			else
			{
				return -1;
			}
		}
	}

	return -1;
}

_Bool word_accepted_by_afd(struct afd *this_afd, short curr_state)
{
	if (this_afd -> states[curr_state] -> acception_state)
	{
		return 1;
	}

	return 0;
}

_Bool free_afd(struct afd *this_afd)
{
	for (int i = 0; i < MAX_STATES; ++i)
	{
		if (this_afd -> states[i] != NULL)
		{
			free_state(this_afd -> states[i]);
		}
	}

	free(this_afd);

	if (this_afd == NULL)
	{
		return 1;
	}

	return 0;
}

int main()
{
	struct afd *coelho = new_afd(2, 2);

	coelho -> states[0] = new_state():
}