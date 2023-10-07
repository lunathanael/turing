#include "Turing.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	Turing::TuringMachine machine1(3LL, 0LL);
	machine1.parse_five_tuple_state_table("a01Rb a11Lc b01La b11Rb c01Lb c11NH");
	machine1.print_state_table();
	while(machine1.next_cycle());
	machine1.print_tape();
	return 0;
}