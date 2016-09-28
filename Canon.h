//Peter Miller
//5-19-2016
#ifndef CANON_H_
#define CANON_H_
#include "Song.h"
#include "toNote.h"
#include "CanonMelody.h"
#include <cstdlib>
#include <ctime>
#include <vector>


class Canon : public song{
public:
	Canon(int l, int t, string T) : song(l, t, T){}
	virtual ~Canon(){}
	void Generate(){
		//Seed srand
		srand(time(0));

		//Add instruments
		instruments.push_back(violin(length)); //Violin 1
		instruments.push_back(violin(length)); //Violin 2
		instruments.push_back(viola(length)); //Viola
		instruments.push_back(cello(length)); //Cello
		instruments.push_back(stringBass(length)); //String Bass

		//Generate Music
		int numSections = length/30; //~1 section every 15 seconds
		int sectionLength = length/numSections; //Sets each section length
		sectionLength -= sectionLength%4; //Trims it to a multiple of four
		vector<melody> melodies; //Vector of melodies
		vector<counterMelody> counterMelodies; //Vector of counter-melodies
		vector<bassLine> bassLines; //Vector of bass-lines
		for(int i=0; i<numSections; i++){ //Four related melodies will be generated per section
			melody temp(sectionLength); //Generates a melody
			for(int j=0; j<4; j++){ //There are four variations of each melody
				melodies.push_back(temp); //Adds a melody
				counterMelodies.push_back(counterMelody(&temp)); //Adds a related counter-melody
				bassLines.push_back(bassLine(&temp)); //Adds a related bass-line
				temp = melody(&temp); //Creates new related melody
			}
		}

		//Assign sections to instruments
		for(int i=0; i<numSections; i++){ //Sections will be assigned semi-randomly to instruments
			int section = rand()%(4*numSections);
			if(rand()%2==0){ //50% chance melody goes to 1st violins
				melodies[section].Generate(&instruments[0], 0, 4*i*sectionLength); //1st Violins
				if(rand()%2==0){ //50% chance countermelody goes to 2nd violins and violas
					counterMelodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
					counterMelodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
					bassLines[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
					bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
				}
				else{ //50% chance countermelody goes to violas and cellos
					melodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins (Get melody as well)
					counterMelodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
					counterMelodies[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
					bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
				}
			}
			else if(rand()%2==0){ //25% chance melody goes to 2nd violins & violas
				melodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
				melodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
				counterMelodies[section].Generate(&instruments[0], 0, 4*i*sectionLength); //1st Violins
				bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
				if(rand()%2==0){ //50% chance cellos get counter-melody
					counterMelodies[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
				}
				else{ //50% chance cellos get bass-line
					bassLines[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
				}

			}
			else if(rand()%2==0){ //12.5% chance melody goes to violas
				melodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
				counterMelodies[section].Generate(&instruments[0], 0, 4*i*sectionLength); //1st Violins
				counterMelodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
				bassLines[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
				bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass

			}
			else if(rand()%2==0){ //6.25% chance melody goes to 2nd violins
				melodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
				counterMelodies[section].Generate(&instruments[0], 0, 4*i*sectionLength); //1st Violins
				counterMelodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
				bassLines[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
				bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
			}
			else{ //6.25% chance melody goes cellos
				melodies[section].Generate(&instruments[3], -1, 4*i*sectionLength); //Cellos
				counterMelodies[section].Generate(&instruments[0], 0, 4*i*sectionLength); //1st Violins
				if(rand()%2==0){ //50% Bass gets counter-melody
					counterMelodies[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
					bassLines[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
					bassLines[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
				}
				else{
					counterMelodies[section].Generate(&instruments[1], 0, 4*i*sectionLength); //2nd Violins
					counterMelodies[section].Generate(&instruments[2], 0, 4*i*sectionLength); //Violas
					bassLines[section].Generate(&instruments[4], -2, 4*i*sectionLength); //Bass
				}
			}
		}


	}
};



#endif /* CANON_H_ */
