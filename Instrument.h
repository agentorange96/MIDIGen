//Peter Miller
//5-19-2016
#ifndef INSTRUMENT_H_
#define INSTRUMENT_H
#include "Channel.h"
#include "toString.h"

//Instrument
//Each instrument is a track on the MIDI file
//Pure Virtual
class instrument{
public:
	instrument(int l);
	virtual ~instrument();
	friend ostream& operator<<(ostream& , const instrument& );
	void addNote(int n, int t, int l, int v=0x7F, int c=0);
protected:
	channel channels[2] = {channel(0,0,0,0), channel(0,0,0,0)}; //Initializes two channels
	int length; //Length of song
	int minNoteLength = 0x10; //This could theoretically change, but 0x10 works well
	int voice; //0=Treble, 1=Alto, 2=Tenor, 3=Bass
	int ID; //MIDI ID
	int numChannels; //Number of channels
};

//Definitions of derived instruments
class violin : public instrument{
public:
	violin( int l );
	~violin(){};
};
class viola : public instrument{
public:
	viola( int l );
	~viola(){};
};
class cello : public instrument{
public:
	cello( int l );
	~cello(){};
};
class stringBass : public instrument{
public:
	stringBass( int l );
	~stringBass(){};
};

#endif
