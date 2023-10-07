// TuringStates.cpp
#include "TuringStates.h"

namespace TuringStates {
	Output::Output(const bool passed_symbol, const bool passed_move_tape, const int64_t passed_state) :
		symbol(passed_symbol), move_tape(passed_move_tape), state(passed_state) {};
	const int64_t Output::get_state() {
		return state;
	}
	const bool Output::get_move_tape() {
		return move_tape;
	}
	const bool Output::get_symbol() {
		return symbol;
	}


	State::State(
		const int64_t passed_current_state, 
		const bool passed_scanned_symbol, 
		const bool passed_print_symbol, 
		const bool passed_move_tape, 
		const int64_t passed_next_state
		) 
		: current_state(passed_current_state)
		, scanned_symbol(passed_scanned_symbol)
		, print_symbol(passed_print_symbol)
		, move_tape(passed_move_tape)
		, next_state(passed_next_state)
	{}
	int64_t State::get_current_state() {
		return current_state;
	}
	bool State::get_scanned_symbol() {
		return scanned_symbol;
	}

	bool State::get_print_symbol() {
		return print_symbol;
	}
	bool State::get_move_tape() {
		return move_tape;
	}
	int64_t State::get_next_state() {
		return next_state;
	}

	void State::set_current_state(const int64_t passed_current_state) {
		current_state = passed_current_state;
	}
	void State::set_scanned_symbol(const bool passed_scanned_symbol) {
		scanned_symbol = passed_scanned_symbol;
	}

	void State::set_print_symbol(const bool passed_print_symbol) {
		print_symbol = passed_print_symbol;
	}
	void State::set_move_tape(const bool passed_move_tape) {
		move_tape = passed_move_tape;
	}
	void State::set_next_state(const int64_t passed_next_state) {
		next_state = passed_next_state;
	}

	void State::print_state(const bool debug) {
		if(debug) {
			std::cout << current_state << ' ';
			std::cout << scanned_symbol << ' ';
		}

		std::cout << print_symbol << ' ';
		std::cout << move_tape << ' ';
		if(next_state != -1) {
			std::cout << next_state << '\t';
		}
		else std::cout << 'h' << '\t';
	}
}