//Peter Miller
//5-19-2016
#ifndef TONOTE_H_
#define TONOTE_H_
#include <string>
#include <cmath>

//Converts from octave and note to a MIDI note number
int toNote(int octave, double note){
	//Make sure octave is in a valid range
	if(octave < -5){
		octave = -5;
	}
	if(octave > 5){
		octave = 5;
	}
	//Makes sure note is in valid range
	while(note>7.5){
		note = note - 7;
	}
	if(note < 0.5 ){
		note = 0.5;
	};
	//Rounds down notes to nearest .5
	note *= 2;
	note = ceil(note);
	note /= 2;

	//Fixes any false sharps (Some don't exist)
	if(note == 2.5 || note == 5.5){
		note += .5;
	}
	//Sets Ab to G#
	if(note == 0.5){
		note = 7.5;
	}

	//Assigns Temporary Value dependent on notes
	double t;
	if(note <= 2){ //A-B
		t=2*note-1;
	}
	else if(note <=5){ //C-E
		t=2*(note+.5)-3;
	}
	else{ //F-G#
		t=2*(note+1)-5;
	}

	//Assigns note
	int outNote = t+12*(octave+5)-4; //Adds octave ammount to note number
	if(outNote < 0){ //Below middle octave
		outNote += 12;
	}
	if(outNote > 127){ //Above middle octave
		outNote -= 12;
	}

	//Return note
	return outNote;
}

//Converts from octave and note name to a MIDI note number
int toNote(int octave, std::string note){
	double noteNum;

	//Checks note string and assigns associated value
	//Similar to a switch, but with strings
	if(note == "Ab"){
		noteNum = 0.5;
	}
	else if(note == "A"){
		noteNum = 1;
	}
	else if(note == "A#"){
		noteNum = 1.5;
	}
	else if(note == "Bb"){
		noteNum = 1.5;
	}
	else if(note == "B"){
		noteNum = 2;
	}
	else if(note == "B#" || note == "Cb" || note == "C"){ //A# and Bb don't exist
		noteNum = 3;
	}
	else if(note == "C#"){
		noteNum = 3.5;
	}
	else if(note == "Db"){
		noteNum = 3.5;
	}
	else if(note == "D"){
		noteNum = 4;
	}
	else if(note == "D#"){
		noteNum = 4.5;
	}
	else if(note == "Eb"){
		noteNum = 4.5;
	}
	else if(note == "E"){
		noteNum = 5;
	}
	else if(note == "E#" || note == "Fb" || note == "F"){ //E# and Fb don't exist
		noteNum = 6;
	}
	else if(note == "F#"){
		noteNum = 6.5;
	}
	else if(note == "Gb"){
		noteNum = 6.5;
	}
	else if(note == "G"){
		noteNum = 7;
	}
	else if(note == "G#"){
		noteNum = 7.5;
	}
	else{
		noteNum = 1;
	}

	//Returns toNote value of given number
	return toNote(octave, noteNum);
}

//Converts from octave and note character to a MIDI note number
int toNote(int octave, char note){
	//Adds given character to a blank string and returns the string to note function
	std::string t = "";
	t  += note;
	return toNote(octave, t);
}

#endif
