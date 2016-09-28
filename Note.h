#ifndef NOTE_H_
#define NOTE_H_
#include <string>

//Note
//This is the basic most unit
class note{
public:
	note(int p, int t, int l, int v, int c);
	~note();
	std::string Sequence(int t) const; //Starts/Stops note when necessary
private:
	std::string start() const; //Generates play string
	std::string stop() const; //Generates stop string
	int pitch; //Pitch of note
	int time; //Time to play
	int length; //Length of note
	int volume; //Volume of note
	int channel; //Which channel the note is in
};

//Used to count the delay before a note
//MIDI doesn't use absolute timestamps but rather times since the last action
class delay{
public:
	delay(int s){ //Constructor
		step = s; //Ammount to incriment each step (Minimum step value)
		value = 0; //Current value
	}
	~delay(){} //Destructor
	void setDelay(int d){ //Sets a value (or resets)
		value = d;
	}

	//MIDI uses Variable Length Quantity to encode timed events
	//This is a very peculiar system;
	std::string getDelay(){
		std::string temp = "";
		int tempVal=value;
		int val[4];

		//Step 1: Break up the binary representation into groups of 7-bits
		for(int i=0; i<4; i++){
			val[i]=tempVal%0b10000000;
			tempVal=tempVal-val[i];
			tempVal=tempVal/0b10000000;
		}

		//Step 2: Add 1 to the beginning of each 7-bit group (except the last)
		//Add zero to the beginning of the last 7-bit group (Now each group is eight bits)
		val[1] += 0b10000000;
		val[2] += 0b10000000;
		val[3] += 0b10000000;

		//Step 3: Convert each group into a hexidecimal number
		//Extra zeros can be omitted
		if(val[3]>0x80){ //Checks whether to use 4 bytes
			temp += char(val[3]);
			temp += char(val[2]);
			temp += char(val[1]);
			temp += char(val[0]);
		}
		else if(val[2]>0x80){ //Checks whether to use 3 bytes
			temp += char(val[2]);
			temp += char(val[1]);
			temp += char(val[0]);
		}
		else if(val[1]>0x80){ //Checks whether to use 2 bytes
			temp += char(val[1]);
			temp += char(val[0]);
		}
		else{ //Otherwise just uses one byte
			temp += char(val[0]);
		}

		return temp; //Returns output
	}
	int operator++(){ //Increments counter
		if(value + step <= 0x0FFFFFFF){ //Checks if at max value
			value += step; //Ic not, increments
		}
		return value;
	}
	int getSize(){ //Returns size in bytes, which contributes to size of track
		return getDelay().size();
	}

private:
	int value; //Current value
	int step; //Step value
};





#endif
