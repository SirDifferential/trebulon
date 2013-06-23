#ifndef __UNITS_HPP_
#define __UNITS_HPP_

/** This file defines some constants used for the world generation
* See http://libnoise.sourceforge.net/tutorials/tutorial3.html
* for info on how these values work
*
* Here's a summary though:
* destSize for heightMaps defines the size of the map.
* This is directly the number of elements in x*y
* Then there is the setBounds function which defines what kind
* of area of the noise is used for this heightMap.
* A large heightMap with small bounds results in lower resolution noise
* It looks kind of like a noise texture stretched on too large surface
* It is, though, faster to calculate.
*
* Initial area refers to the noise coordinate space area which will be generated
* at the game's loading phase. Noise size of 8 and initial area of 16 would produce
* noise from -16 to 16
*
* SFML_SCALE_FACTOR is used for stretching the finished texture
* Since it's too expensive to calculate high quality terrain,
* the compromise in quallity has to be made and the terrain stretched
* Otherwise the player would be waiting all the time for new terrain to be created
* If this was done with CUDA things would be fine and dandy...
*
*/

const int NOISE_SIZE = 4;
const int REGION_SIZE = 1024;
const int INITIAL_AREA = 16;
const float SFML_SCALE_FACTOR = 8.0f;

#endif
