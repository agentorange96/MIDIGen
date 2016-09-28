//Peter Miller
//5-19-2016
#ifndef SONG_H_
#define SONG_H_
#include <vector>
#include <string>
#include "Instrument.h"


class song{
public:
	song(int l, int t, string T);
	virtual ~song();
	void writeMIDI();
	void generate();
protected:
	int length;
	int tempo;
	string title;
	 vector<instrument> instruments;
};



#endif
