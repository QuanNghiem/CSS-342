/*
 * dragon.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Quan Nghiem
 */

#ifndef SRC_DRAGON_H_
#define SRC_DRAGON_H_

#include "Turtle.h"
#include <iostream>
#include <math.h>
using namespace std;

class Dragon : public Turtle {
public:
  Dragon( float initX=0.0, float initY=0.0, float initAngle=0.0 );
  void leftCurve( int l, float d );  //draw a level-l left curve with distance d
  void rightCurve( int l, float d ); //draw a level-l right curve with distance d
};

#endif
