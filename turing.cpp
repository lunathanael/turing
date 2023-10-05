#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include <algorithm>

using namespace std;

static constexpr int64_t HALT = -1;

class result {
private:
	int64_t state;
	bool move_tape;
	bool symbol;
public:
	result(const bool passed_symbol, const bool passed_move_tape, const int64_t passed_state) {
		state = passed_state;
		move_tape = passed_move_tape;
		symbol = passed_symbol;
	}
	int64_t get_state() {
		return state;
	}
	bool get_move_tape() {
		return move_tape;
	}
	bool get_symbol() {
		return symbol;
	}
};


class State {
private:
	bool current_symbol;
	int64_t current_state;

	bool next_symbol;
	bool next_move_tape;
	int64_t next_state;

public:
	State(const bool passed_current_symbol, const int64_t passed_current_state, const bool passed_symbol, const bool passed_move_tape, const int64_t passed_next_state) {
		current_symbol = passed_current_symbol;
		current_state = passed_current_state;

		next_symbol = passed_symbol;
		next_move_tape = passed_move_tape;
		next_state = passed_next_state;
	}
	bool get_current_symbol() {
		return current_symbol;
	}
	int64_t get_current_state() {
		return current_state;
	}
	bool get_next_symbol() {
		return next_symbol;
	}
	bool get_next_move_tape() {
		return next_move_tape;
	}
	int64_t get_next_state() {
		return next_state;
	}

	void set_current_symbol(const bool passed_current_symbol) {
		current_symbol = passed_current_symbol;
	}
	void set_current_state(const int64_t passed_current_state) {
		current_state = passed_current_state;
	}
	void set_next_symbol(const bool passed_next_symbol) {
		next_symbol = passed_next_symbol;
	}
	void set_next_move_tape(const bool passed_next_move_tape) {
		next_move_tape = passed_next_move_tape;
	}
	void set_next_state(const int64_t passed_next_state) {
		next_state = passed_next_state;
	}
};

template <typename T> result turing_function(T &state) {
	result res(state.get_next_symbol(), state.get_next_move_tape(), state.get_next_state());
	return res;
}

class Turing {
private:
	uint64_t state_count;

	uint64_t cycles;
	int64_t head;
	int64_t state;
	unordered_map<int64_t, bool> tape;
	vector<State> state_table[2];

	int64_t lower;
	int64_t upper;

public:
	Turing(const uint64_t passed_states, const int64_t passed_initial_state, vector<State> &passed_state_table) {
		state_count = passed_states;
		head = 0;
		state = passed_initial_state;

		lower = -1;
		upper = 1;

		for (int i = 0; i < 2; ++i) {
			for(int j = 0; j < state_count; ++j) {
				state_table[i].push_back(State(0, 0, 0, 0, 0));			
			}
		}
		for (int i = 0; i < passed_state_table.size(); ++i) {
			State &passed_state = passed_state_table[i];
			State &modified_state = state_table[passed_state.get_current_symbol()][passed_state.get_current_state()];
			modified_state.set_current_state(passed_state.get_current_state());
			modified_state.set_current_symbol(passed_state.get_current_symbol());

			modified_state.set_next_state(passed_state.get_next_state());
			modified_state.set_next_symbol(passed_state.get_next_symbol());
			modified_state.set_next_move_tape(passed_state.get_next_move_tape());
		}
	}

	bool next_cycle() {
		State &current_state = state_table[tape[head]][state];
		result res = turing_function(current_state);

		tape[head] = res.get_symbol();
		if(res.get_move_tape()) ++head;
		else --head;
		state = res.get_state();

		++cycles;

		lower = min(lower, head);
		upper = max(upper, head);
		if(state == HALT) return false;
		return true;
	}

	const uint64_t get_state_count() {
		return state_count;
	}

	uint64_t get_cycles() {
		return cycles;
	}

	void print_tape() {
		for(int64_t i = lower; i <= upper; ++i) {
			cout << tape[i] << ' ';
		}
		cout << '\n';
	}


};


int main() {
	// const int state_count = 2;
	// vector<State> state_table;
	// state_table.push_back(State(0, 0, 1, 1, 1));
	// state_table.push_back(State(1, 0, 1, 0, 1));
	// state_table.push_back(State(0, 1, 1, 0, 0));
	// state_table.push_back(State(1, 1, 1, 1, HALT));
	// Turing machine1(state_count, 0, state_table);


	// machine1.print_tape();
	// while(machine1.next_cycle());
	// machine1.print_tape();

	// const int state_count = 3;
	// vector<State> state_table;
	// state_table.push_back(State(0, 0, 1, 1, 1));
	// state_table.push_back(State(1, 0, 1, 1, HALT));
	// state_table.push_back(State(0, 1, 0, 1, 2));
	// state_table.push_back(State(1, 1, 1, 1, 1));
	// state_table.push_back(State(0, 2, 1, 0, 2));
	// state_table.push_back(State(1, 2, 1, 0, 0));
	// Turing machine1(state_count, 0, state_table);


	// machine1.print_tape();
	// while(machine1.next_cycle());
	// machine1.print_tape();

	const int state_count = 4;
	vector<State> state_table;
	state_table.push_back(State(1, 0, 1, 0, 1));
	state_table.push_back(State(0, 0, 1, 1, 1));

	state_table.push_back(State(1, 1, 0, 0, 2));
	state_table.push_back(State(0, 1, 1, 0, 0));

	state_table.push_back(State(1, 2, 1, 0, 3));
	state_table.push_back(State(0, 2, 1, 1, HALT));

	state_table.push_back(State(1, 3, 0, 1, 0));
	state_table.push_back(State(0, 3, 1, 1, 3));
	Turing machine1(state_count, 0, state_table);


	while(machine1.next_cycle())machine1.print_tape();
	machine1.print_tape();

	return 1;
}