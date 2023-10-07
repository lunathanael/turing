// TuringStates.h
#ifndef TURING_STATES_H
#define TURING_STATES_H

#include <iostream>
#include <vector>

namespace TuringStates {
	class Output {
	private:
		const int64_t state;
		const bool move_tape;
		const bool symbol;
	public:
		Output(const bool passed_symbol, const bool passed_move_tape, const int64_t passed_state);
		const int64_t get_state();
		const bool get_move_tape();
		const bool get_symbol();
	};
	class State {
	private:
		int64_t current_state;
		bool scanned_symbol;

		bool print_symbol;
		bool move_tape;
		int64_t next_state;
	public:
		State(
			const int64_t passed_current_state, 
			const bool passed_scanned_symbol, 
			const bool passed_print_symbol, 
			const bool passed_move_tape, 
			const int64_t passed_next_state
		);

		int64_t get_current_state();
		bool get_scanned_symbol();

		bool get_print_symbol();
		bool get_move_tape();
		int64_t get_next_state();

		void set_current_state(const int64_t passed_current_state);
		void set_scanned_symbol(const bool passed_scanned_symbol);

		void set_print_symbol(const bool passed_print_symbol);
		void set_move_tape(const bool passed_move_tape);
		void set_next_state(const int64_t passed_next_state);

		void print_state();
	};
}



#endif
