// TapeList.h
#ifndef TAPE_LIST_H
#define TAPE_LIST_H

#include <iostream>

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
		void print_list();
		bool get_curr_data();
	};
}

#endif