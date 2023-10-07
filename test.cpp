#include "Turing.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Create a Turing machine with 3 states and an initial state of 0.
    Turing::TuringMachine machine1(3LL, 0LL);
    
    // Parse a five-tuple state table defining the Turing machine's behavior.
    machine1.parse_five_tuple_state_table("a01Rb a11Lc b01La b11Rb c01Lb c11NH");

    // Print the state table.
    machine1.print_state_table();

    // Simulate the Turing machine one step at a time until it halts.
    while (machine1.next_cycle());

    // Print the final content of the tape.
    machine1.print_tape();
	return 0;
}