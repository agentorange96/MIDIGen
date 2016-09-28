//Peter Miller
//5-19-2016
#include "Note.h"
using namespace std;

note::note(int p, int t, int l, int v, int c){
		pitch = p;
		time = t;
		length = l;
		volume = v;
		channel = c;
	}

note::~note(){}

/*Sequence Function
 * MIDI files get instructions for when to start and when to stop each note
 * This function is given the current time and determines whether the note needs to start, stop or do nothing
 * Each note in a channel will have this function called
 * Having the channel sequence each notes stop and start on its own would be quite challenging
 * Whereas having each note decide for itself if its stop or start should be sequenced is fairly simple
 * The drawback being that looping through each note takes more processing time
 */
string note::Sequence(int t) const{
	string temp;

	//Start the note playing
	if(t==time){
		return note::start();
	}

	//End the note playing
	else if(t==time+length){
		return note::stop();
	}

	//Do nothing
	else{
		return "";
	}
}

string note::start() const{
	string temp = "";

	//First half-byte is on
	//Second half-byte is channel number
	int s = 0x90+channel;
	temp += char(s);

	//Second byte is pitch
	temp += char(pitch);

	//Third byte is volume
	temp += char(volume);

	return temp;
}

string note::stop() const{
	string temp = "";

	//First half-byte is off
	//Second half-byte is channel number
	int s = 0x80+channel;
	temp += char(s);

	//Second byte is pitch
	temp += char(pitch);

	//Third byte is volume
	temp += char(volume);

	return temp;
}
