// Turing.h

#ifndef TURING_H
#define TURING_H

#include <string>
#include "TuringStates.h"
#include "TapeList.h"

namespace Turing {
	static constexpr int64_t HALT = -1;

	template <typename T> TuringStates::Output turing_function(T &state) {
		TuringStates::Output res(state.get_print_symbol(), state.get_move_tape(), state.get_next_state());
		return res;
	}

	class TuringMachine {
	private:
		const uint64_t state_count;

		uint64_t cycles;
		int64_t state;
		TapeList::List tape;
		std::vector<TuringStates::State> state_table[2];

	public:
		TuringMachine(const uint64_t passed_state_count, const int64_t passed_initial_state);

		void parse_state_table(std::vector<TuringStates::State> &passed_state_table);

		void parse_five_tuple_state_table(const std::string input);

		void print_state_table();

		bool next_cycle();

		const uint64_t get_state_count();

		uint64_t get_cycles();

		void print_tape();
	};
}



#endif