// TapeList.cpp
// TapeList.h

#include "TapeList.h"

namespace TapeList {
	List::List() {
		front = new Node(nullptr, nullptr, 0);
		curr = front;
	}
	void List::insert_node(bool direction, bool val) {
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
	void List::print_list() {
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
	bool List::get_curr_data() {
		return curr->data;
	}
}