// TapeList.h
#ifndef TAPE_LIST_H
#define TAPE_LIST_H

#include <iostream>

static constexpr int64_t HALT = -1;
static constexpr int64_t NOSTATE = -2;

namespace TapeList {
	class List {
	private:
		struct Node {
			Node* prev;
			Node* next;
			bool data;
			Node(Node* passed_prev, Node* passed_next, Node* passed_data) : prev(passed_prev), next(passed_next), data(passed_data) {}
		};
		Node* front;
		Node* curr;
	public:
		List();
		void insert_node(bool direction, bool val);
		void print_list(int64_t state = NOSTATE);
		bool get_curr_data();
	};
}

#endif