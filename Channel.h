//Peter Miller
//5-19-2016
#ifndef CHANNEL_H_
#define CHANNEL_H_
#include "Note.h"
#include <vector>
using namespace std;

//Channel
//Most instruments have one Channel
//Piano has two
class channel{
public:
	channel(int l, int min, int max, int n); //Constructor
	~channel(); //Destructor
	string Sequence( int t, delay *d ) const; //Sequences the notes and returns it as a string
	int getSize(); //Returns size
	void addNote(int n, int t, int l, int v); //Allows the addition of a note
private:
	int length; //Length of channel
	int minNote; //Minimum possible note
	int maxNote; //Maximum possible note
	int channelNum; //Channel number, used for MIDI sequencing
	vector<note> notes; //A vector of notes
};

#endif
