//Peter Miller
//5-19-2016
#ifndef CANONMELODY_H_
#define CANONMELODY_H_
//Melody classes for Canon.h
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>

class melody{
public:
	melody(){}
	melody(int l){
		//Generate melody
		for(int i = 0; i<((l-l%4)/4); i++){
			int measure = 0; //Counts beats so far per measure (4 quarter notes or 16 beats)
			array<double, 4> temp; //A temporary holding place for each new note
			while(measure<16){ //While a measure has less than sixteen beats, more notes are added
				double note; //Temporary values for the to be added note
				double length;
				double octave=0;
				if(notes.size()<1){ //If first note in melody
					note = rand()%14+1; //Generates from scratch
				}
				else{ //Otherwise base on last note
					//Determine note
					if(rand()%2==0){ //50% chance to jump a multiple of 2 notes (for chords)
						note = notes.back()[1]+7*notes.back()[0]+(2*(rand()%5-3));
					}
					else{ //50% chance to jump any number of notes
						note = notes.back()[1]+7*notes.back()[0]+(rand()%9-4);
					}
					while(note>14){ //Keeps notes in range
						note--;
					}
					while(note<1){
						note++;
					}
					if(note>7){
						octave = 1;
						note-=7;
					}
				}
				temp[0] = octave; //Set octave
				temp[1] = note; //Set note


				//Determine length;
				if(measure%4 != 0){ //If not on an even quarter note
					if(measure%8 != 0){ //If not on even eighth note
						length = 1; //Add a sixteenth note
					}
					else{
						length = 2;//rand()%2+1; //Add a sixteenth or eighth note
					}
				}
				else{
					if(rand()%3 != 0){ //Two-thirds chance of some multiple of quarter notes
						length = 4*(rand()%4)+1;
					}
					else{ //One-third chance of an eighth or sixteenth note
						length = rand()%2+1;
					}
				}
				while((length + measure) > 16){ //If length goes over, trims
					length--;
				}

				temp[2] = measure+(16*i); //Set start time
				temp[3] = length; //Set length
				measure += length; //Advance time
				if(rand()%20 != 0){ //5% chance of a rest
					notes.push_back(temp);
				}
			}

		}
	}
	melody(melody *m){
		//Generate melody based off melody
		int offset;
		if(rand()%3 != 0){ //Two-thirds chance to shift the melody a multiple of two (chord)
			offset = 2*(rand()%2)+2;
		}
		else{ //Otherwise, shifts an arbitrary ammount
			offset = rand()%5+1;
		}
		if(rand()%2 == 0){ //50% chance of being negative offset
			offset *= -1;
		}
		for(int i=0; i < m->notes.size(); i++){ //Cycles through each note in the base and applies changes
			array<double, 4> temp; //Temporary note
			double note = m->notes[i][0]*7 + m->notes[i][1];
			note+=offset;
			double octave = 0;
			while(note>14){ //Keeps notes in range
				note-=4;
			}
			while(note<1){
				note+=4;
			}
			if(note>7){ //Sets appropriate octave
				octave = 1;
				note-=7;
			}

			//Applies new values to temporary note
			temp[0] = octave;
			temp[1] = note;
			temp[2] = m->notes[i][2];
			temp[3] = m->notes[i][3];

			//Adds note to vector of notes
			notes.push_back(temp);
		}
	}
	~melody(){} //Destructor

	//Adds the notes to the instrument's track
	void Generate(instrument *ins, int lowOctave=0, int offset=0){
		for(int i=0; i<notes.size(); i++){ //Cycles through each note and adds it
			ins->addNote(toNote(lowOctave+notes[i][0], notes[i][1] ), notes[i][2]+offset, notes[i][3], vol);
		}
	}
	vector<array<double, 4>> notes; //Stores values for each note
	//0: Octave Offset, 1: Note, 2: Start Time, 3: Length


protected:
	int vol = 0x7F; //Volume for section
};

class counterMelody : public melody{ //Derived from Melody
public:
	counterMelody(melody *m) : melody(){
		vol = 0x54; //Two-thirds melody volume;
		//Generate counterMelody based off melody

		//Offset is in a chord with the melody
		int offset = -2*(rand()%2)+2;

		if(rand()%3 != 0){ //66% chance of being negative offset
			offset *= -1;
		}
		int half = rand()%3; //If 0, then notes will be replaced with two notes of half their length
		for(int i=0; i < m->notes.size(); i++){

			array<double, 4> temp; //Temporary note
			double note = m->notes[i][0]*7 + m->notes[i][1]; //Gets note value from melody
			note+=offset; //Offsets that value
			double octave = 0;
			while(note>14){ //Keeps notes in range
				note-=4;
			}
			while(note<1){
				note+=4;
			}
			if(note>7){ //Sets approriate octave
				octave = 1;
				note-=7;
			}
			temp[0] = octave;
			temp[1] = note;

			//If doubling the notes
			if(half == 0 && m->notes[i][3]>2){
				//Sets the length to hald and creates two instances with appropriate delays
				temp[2] = m->notes[i][2];
				temp[3] = m->notes[i][3] /2;
				notes.push_back(temp);
				temp[2] += temp[3];
				notes.push_back(temp);
			}
			else{
				//Otherwise, adds note as usual
				temp[2] = m->notes[i][2];
				temp[3] = m->notes[i][3];
				notes.push_back(temp);
			}
		}
	}
};

class bassLine : public melody{
public:
	bassLine(melody *m) : melody(){
		vol = 0x54; //Two-thirds melody volume;
		//Generate bassLine based off melody

		//Offset is in a chord with the melody
		int offset = -2*(rand()%2)+2;

		if(rand()%3 != 0){ //66% chance of being negative offset
			offset *= -1;
		}

		for(int i=0; i < m->notes.size(); i++){
			if(notes.size()<1 || rand()%3==0 || notes.back()[3]>8){ //Checks to see if it shouldn't change the beat
				array<double, 4> temp; //Temporary note
				double note = m->notes[i][0]*7 + m->notes[i][1]; //Gets note value
				note+=offset; //Applies an offset
				double octave = 0;
				while(note>14){ //Keeps notes in range
					note--;
				}
				while(note<1){
					note++;
				}
				if(note>7){ //Sets approriate octave and note value
					octave = 1;
					note-=7;
				}
				//Sets note values
				temp[0] = octave;
				temp[1] = note;
				temp[2] = m->notes[i][2];
				temp[3] = m->notes[i][3];

				//Adds note to vector of notes
				notes.push_back(temp);
			}
			else{
				//Sometimes will ommit a note and lengthen the previous one
				notes.back()[3] += m->notes[i][3];
			}
		}
	}
};

#endif
