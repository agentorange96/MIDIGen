//Peter Miller
//5-19-2016
#include "Channel.h"
using namespace std;
#include <iostream>

//Constructor initializes variables
channel::channel(int l, int min, int max, int n){
	length = l;
	minNote = min;
	maxNote = max;
	channelNum = n;
}

channel::~channel(){

}

//The bytes for each track/instrument must be known for the MIDI file
int channel::getSize(){
	return notes.size()*3; //Multiplies number of notes by bytes per note
}

/*Sequence Function
 * All channels must run parallel to eachother, so they must both be sequenced for each time-step
 * This will be called by the instrument at every time step, and it sequences every note in the channel as appropriate
 */
string channel::Sequence( int t, delay *d) const {
	string temp = "";
	bool first = true;
		for(int i=0; i<notes.size(); i++){ //Runs through every note and checks if it needs to have an event sequenced
			if(notes[i].Sequence(t) != ""){
				temp += d->getDelay(); //Adds delay value
				temp += notes[i].Sequence(t); //Sequences a note
				if(first){ //Checks if it is the first note in the channel
					first = false;
					d->setDelay(0); //Resets the delay
				}
			}
	}
	return temp; //Returns the sequence
}

void channel::addNote(int n, int t, int l, int v){ //Allows the addition of a note
	notes.push_back(note(n, t, l, v, channelNum));
}
