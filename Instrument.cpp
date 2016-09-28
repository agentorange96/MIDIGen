//Peter Miller
//5-19-2016
#include "Instrument.h"
#include "Note.h"
#include <iostream>
using namespace std;

//This defines the main virtual instrument class as well as its derivatives

//Strings
	//Violin
	violin::violin( int l) : instrument(l){
		ID = 41;
		voice = 0;
		numChannels = 1;
		channels[0] = channel(l, 55, 103, 0);
	}

	//Viola
	viola::viola( int l) : instrument(l){
		ID = 42;
		voice = 1;
		numChannels = 1;
		channels[0] = channel(l, 48, 91, 0);
	}

	//Cello
	cello::cello( int l) : instrument(l){
		ID = 43;
		voice = 1;
		numChannels = 1;
		channels[0] = channel(l, 36, 76, 0);
	}

	//Bass
	stringBass::stringBass( int l) : instrument(l){
		ID = 44;
		voice = 1;
		numChannels = 1;
		channels[0] = channel(l, 28, 67, 0);
	}

instrument::~instrument(){}; //Destructor
instrument::instrument(int l){
	length = l; //Sets the length of the song
}

//Allows the addition of a note to the instruments tracks
void instrument::addNote(int n, int t, int l, int v, int c){
	channels[c].addNote(n, t, l, v);
}

//Outputs the instrument's track, which can be put into a file stream
ostream& operator<<(ostream &output, const instrument &ins ){
	delay d(ins.minNoteLength); //Delay is used to keep track of location in MIDI file
	string temp = ""; //String holds the eventual output

	//Set Instrument Voice
	for(int i=0; i<ins.numChannels; i++){
		//Set at time of zero
		temp+=char(0);
		//First half-byte is change voice
		//Second half-byte is channel number
		int s = 0xC0+i;
		temp += char(s);
		//Sets to correct voice
		temp += char(ins.ID);
	}

	//Populate with notes
	//Goes through each moment and lets any notes that need to be sequenced sequence themselves
	for(int i=0; i<ins.length; i++){
		string looptemp = "";
		//Iterates through all the channels
		for(int j=0; j<ins.numChannels; j++){
			//Sequences all notes
			temp += ins.channels[j].Sequence(i, &d);
		}
		++d; //Incriments delay
		if(looptemp == ""){ //Checks if empty time slot (No notes change)
			++d; //If so, increments delay to account for it
		}
		temp += looptemp; //Adds the current sequence to the full output
	}

	//Get length of track
	int channelLength = temp.size() + 0x4; //Finds the length of the track


	//Output Track
	output << "MTrk" << toString(channelLength, 4) //Track Header (Includes length)
			<< temp //content
			<< char(0x00) << char(0xFF) << char(0x2F) << char(0x00); //End of track
return output;
}
