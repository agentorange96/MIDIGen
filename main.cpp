//Peter Miller
//5-19-2016
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Canon.h"

//Main function
//Gathers user input and calls song generation
//In the future, would select the song type, but currently only "Canon" is available
int main(){
	//Song info (will be generated)
	int tempo;
	int time;
	string title;

	//Welcome Message
	cout << "MIDI Music Generator" << endl;

	//Get Title
	cout << "Please enter a title for the generated song" << endl
			<<"Or enter \"0\" for a random name" << endl
			<<"Title: ";
	cin >> title;
	if(title=="0"){
		for(int i=0; i<rand()%5+6; i++){
			title+=char(rand()%26+65);
		}
	}
	{

	}

	//Get Tempo
	cout << "Please enter the desired tempo in Beats Per Minute you'd like for your track "
			<<"or enter 0 to use the default (120 BPM)" << endl
			<<"Tempo: ";
	cin >> tempo;
	if(tempo == 0){
		tempo = 120;
	}

	//Get Time
	cout << "Please enter the desired time in the format minutes seconds" << endl
			<<"or enter \"0 0\" to use a random time" << endl
			<<"Time: ";
	int mins; int secs;
	cin >> mins >> secs;
	time = mins*60 + secs;
	if(time == 0){
		time = rand()%120+61; //Random time is between 1-3 minutes;
	}

	Canon c(time, tempo, title);
	c.Generate();
	c.writeMIDI();
	cout << title << ".mid has been generated.";
}
