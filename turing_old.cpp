#include<iostream>
#include<vector>

using namespace std;

static constexpr int64_t HALT = -1;

class List {
private:
	struct Node {
		Node* prev;
		Node* next;
		bool data;
		Node(Node* passed_prev, Node* passed_next, Node* passed_data) : prev(passed_prev), next(passed_next), data(passed_data) {}
	};
	Node* front = new Node(nullptr, nullptr, 0);
	Node* curr;
public:
	List() {
		curr = front;
	}
	void insert_node(bool direction, bool val) {
		curr->data = val;
		if(direction) {
			if(!curr->next){
				curr->next = new Node(curr, nullptr, 0);
			}
			curr = curr->next;
		}
		else {
			if(!curr->prev) {
				curr->prev = new Node(nullptr, curr, 0);
				front = curr->prev;
			}
			curr = curr->prev;
		}
	}
	void print_list() {
		Node*temp = front;
		while(temp) {
			std::cout << temp->data << ' ';
			temp = temp->next;
		}
		std::cout << '\n';

		temp = front;
		while(temp) {
			if(temp == curr) std::cout << "^";
			std::cout << "  ";
			temp = temp->next;
		}
		std::cout << '\n';
	}
	bool get_curr_data() {
		return curr->data;
	}
};

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
	const uint64_t state_count;

	uint64_t cycles;
	int64_t head;
	int64_t state;
	List tape;
	vector<State> state_table[2];

public:
	Turing(const uint64_t passed_states, const int64_t passed_initial_state, vector<State> &passed_state_table) : state_count(passed_states) {
		head = 0;
		state = passed_initial_state;

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
		State &current_state = state_table[tape.get_curr_data()][state];
		result res = turing_function(current_state);

		tape.insert_node(res.get_move_tape(), res.get_symbol());
		state = res.get_state();

		++cycles;

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
		tape.print_list();
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

	const int state_count = 3;
	vector<State> state_table;
	state_table.push_back(State(0, 0, 1, 1, 1));
	state_table.push_back(State(1, 0, 1, 1, HALT));
	state_table.push_back(State(0, 1, 0, 1, 2));
	state_table.push_back(State(1, 1, 1, 1, 1));
	state_table.push_back(State(0, 2, 1, 0, 2));
	state_table.push_back(State(1, 2, 1, 0, 0));
	Turing machine1(state_count, 0, state_table);


	while(machine1.next_cycle());
	machine1.print_tape();


	// machine1.print_tape();
	// while(machine1.next_cycle());
	// machine1.print_tape();

	// const int state_count = 4;
	// vector<State> state_table;
	// state_table.push_back(State(1, 0, 1, 0, 1));
	// state_table.push_back(State(0, 0, 1, 1, 1));

	// state_table.push_back(State(1, 1, 0, 0, 2));
	// state_table.push_back(State(0, 1, 1, 0, 0));

	// state_table.push_back(State(1, 2, 1, 0, 3));
	// state_table.push_back(State(0, 2, 1, 1, HALT));

	// state_table.push_back(State(1, 3, 0, 1, 0));
	// state_table.push_back(State(0, 3, 1, 1, 3));
	// Turing machine1(state_count, 0, state_table);


	// while(machine1.next_cycle());
	// machine1.print_tape();

	// const int state_count = 5;
	// vector<State> state_table;
	// state_table.push_back(State(0, 0, 1, 0, 1));
	// state_table.push_back(State(1, 0, 1, 0, 0));

	// state_table.push_back(State(0, 1, 1, 1, 2));
	// state_table.push_back(State(1, 1, 1, 1, 1));

	// state_table.push_back(State(0, 2, 1, 0, 0));
	// state_table.push_back(State(1, 2, 1, 1, 3));

	// state_table.push_back(State(0, 3, 1, 0, 0));
	// state_table.push_back(State(1, 3, 1, 1, 4));

	// state_table.push_back(State(0, 4, 1, 1, HALT));
	// state_table.push_back(State(1, 4, 0, 1, 2));
	// Turing machine1(state_count, 0, state_table);


	// while(machine1.next_cycle());
	// machine1.print_tape();

	// const int state_count = 6;
	// vector<State> state_table;
	// state_table.push_back(State(0, 0, 1, 1, 1));
	// state_table.push_back(State(1, 0, 0, 0, 4));

	// state_table.push_back(State(0, 1, 1, 0, 2));
	// state_table.push_back(State(1, 1, 0, 1, 0));

	// state_table.push_back(State(0, 2, 1, 0, 3));
	// state_table.push_back(State(1, 2, 0, 1, 2));

	// state_table.push_back(State(0, 3, 1, 0, 4));
	// state_table.push_back(State(1, 3, 0, 0, 5));

	// state_table.push_back(State(0, 4, 1, 0, 0));
	// state_table.push_back(State(1, 4, 1, 0, 2));

	// state_table.push_back(State(0, 5, 1, 0, 4));
	// state_table.push_back(State(1, 5, 1, 1, HALT));

	// Turing machine1(state_count, 0, state_table);


	// while(machine1.next_cycle());
	// machine1.print_tape();

	return 1;
}