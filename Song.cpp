//Peter Miller
//5-19-2016
#include "Song.h"
#include "toString.h"
#include <iostream>
#include <fstream>
using namespace std;

song::song( int l, int t, string T){
	tempo = t; //Sets tempo
	length = 4*l*(t/60); //Number of beats from time in seconds and tempo
	title = T; //Sets title
}

song::~song(){

}

void song::writeMIDI(){
	//Creates an output file stream
	ofstream test(title + ".mid", ios::out | ios::trunc | ios::binary);

	//Encode Header
	test << "MThd" //Marker for Midi File
			<< char(0x00) << char(0x00) << char(0x00) << char(0x06) //Marker for header size
			<< char(0x00) << char(0x01) //Type 1 MIDI
			<< toString( instruments.size(), 2) //Number of tracks (This should be dynamic)
			<< char(0x00) << char(0x80); //Ticks per quarter note

	//Encode Tempo
	//Convert from tempo to microseconds per beat
	int t = 60000000 / tempo;
	//Encode into file
	test << "MTrk" << char(0x00) << char(0x00) << char(0x00) << char(0x0B) //Encode Track header
			<< char(0x00) << char(0xFF) << char(0x51) << char(0x03) //FF = Control Signal, 51 = Tempo, 03=Number of following bytes
			<< toString(t, 3) //Encode tempo
			<< char(0x00) << char(0xFF) << char(0x2F) << char(0x00); //Track footer

	//Sequence Each Instrument
	for(int i=0; i<instruments.size(); i++){ //Iterates through each instrument and sequences it
		test << instruments[i];
	}


}
