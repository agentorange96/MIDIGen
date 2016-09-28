//Peter Miller
//5-19-2016
#include "toString.h"
#include <iostream>
#include <cmath>

//This functionm converts an integer to a string that is used to encode it in a file
string toString(int in, int bytes){
	string temp;
	for(int i = bytes; i > 0; i--){ //Encodes it to the given number of bytes
		int t = (in % (int)pow(2,(8*i))) - (in % (int)pow(2,(8*(i-1)))); //Isolates the given bits
		t = t / pow(2,(8*(i-1))); //Turns those bits to the first eight bits
		temp += char(t); //Encodes it as a character and adds it to the output
	}
	return temp;
}
