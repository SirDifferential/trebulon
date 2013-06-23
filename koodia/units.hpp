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
*/

const int NOISE_SIZE = 2;
const int REGION_SIZE = 2048;
const int INITIAL_AREA = 8;

#endif
