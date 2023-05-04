#include "Neuron.h"

void Neuron::neuron() {
 
	// vvvvv put your code here vvvvv
	output_temp = input1.read()*w1 + input2.read()*w2 + b;
	y = (1.0/2) + (1.0/4)*output_temp - (1.0/48)*output_temp*output_temp*output_temp + (1.0/480)*output_temp*output_temp*output_temp*output_temp*output_temp;
	y = (y > 0.5) ? 1 : 0;
	output.write(y);
	// ^^^^^ put your code here ^^^^^
} 