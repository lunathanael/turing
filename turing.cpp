// Turing.cpp

#include "Turing.h"

namespace Turing {
	TuringMachine::TuringMachine(
		const uint64_t passed_state_count, 
		const int64_t passed_initial_state
	) 
	: state_count(passed_state_count) 
	{
		state = passed_initial_state;

		for (int i = 0; i < 2; ++i) {
			for(int j = 0; j < state_count; ++j) {
				state_table[i].push_back(TuringStates::State(0, 0, 0, 0, 0));			
			}
		}
	}

	void TuringMachine::parse_state_table(std::vector<TuringStates::State> &passed_state_table) {
		for (int i = 0; i < passed_state_table.size(); ++i) {
			TuringStates::State &passed_state = passed_state_table[i];
			TuringStates::State &modified_state = state_table[passed_state.get_scanned_symbol()][passed_state.get_current_state()];
			modified_state.set_current_state(passed_state.get_current_state());
			modified_state.set_scanned_symbol(passed_state.get_scanned_symbol());

			modified_state.set_next_state(passed_state.get_next_state());
			modified_state.set_print_symbol(passed_state.get_print_symbol());
			modified_state.set_move_tape(passed_state.get_move_tape());
		}
	}

	void TuringMachine::parse_five_tuple_state_table(std::string input) {
		std::vector<TuringStates::State> state_table;
		for(int i = 0; i < input.size(); ++i){
			const int64_t current_state = (input[i++] - 'a');
			const bool scanned_symbol = (input[i++] - '0');
			const bool print_symbol = (input[i++] - '0');
			const bool move_tape = (input[i++] == 'R');
			const int64_t next_state = (input[i] != 'H') ?  (input[i++] - 'a') : -1;
			state_table.push_back(TuringStates::State(current_state, scanned_symbol, print_symbol, move_tape, next_state));
		}

		parse_state_table(state_table);
	}

	void TuringMachine::print_state_table(bool debug) {
		std::cout << "Symbol\t";
		for(int j = 0; j < state_count; ++j) {
			std::cout << "  " << static_cast<char>('a'+j) << "  \t";
		}
		std::cout << std::endl;
		for (int i = 0; i < 2; ++i) {
			std::cout << i << '\t';
			for(int j = 0; j < state_count; ++j) {
				state_table[i][j].print_state(debug);
			}
			std::cout << '\n';
		}
		std::cout << std::endl;
	}

	bool TuringMachine::next_cycle() {
		TuringStates::State &current_state = state_table[tape.get_curr_data()][state];
		TuringStates::Output res = turing_function(current_state);

		tape.insert_node(res.get_move_tape(), res.get_symbol());
		state = res.get_state();

		++cycles;

		return (state != HALT);
	}

	const uint64_t TuringMachine::get_state_count() {
		return state_count;
	}

	uint64_t TuringMachine::get_cycles() {
		return cycles;
	}

	void TuringMachine::print_tape() {
		tape.print_list();
	}
}