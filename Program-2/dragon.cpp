/*
 * dragon.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: Quan Nghiem
 */

#include "dragon.h"

const int Left = 90;
const int Right = -90;
//------------------------- dragon Arrowhead ----------------------------
Dragon::Dragon( float initX, float initY, float initAngle )
  : Turtle( initX, initY, initAngle ) {
}

//------------------------------ leftCurve ----------------------------------
// draw a level-l left curve with distance d
void Dragon::leftCurve( int level, float d ) {
  if ( level > 0 ) {
    leftCurve(level-1, d);
    turn(Left);
    rightCurve(level-1, d);
    turn(Left);
  }
  else
    draw(d);
}

//------------------------------ rightCurve ---------------------------------
// draw a level-l right curve with distance d
void Dragon::rightCurve( int level, float d ) {
  if ( level > 0 ) {
	    turn(Right);
	    leftCurve(level-1,d);
	    turn(Right);
	    rightCurve(level-1,d);
  }
  else
    draw(d);
}
