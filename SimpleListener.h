#ifndef SIMPLELISTENER_H
#define SIMPLELISTENER_H

#include "Leap.h"

extern enum Direction;
extern Direction leapDirection;

class SimpleListener : public Leap::Listener {
public:
	virtual void onConnect(const Leap::Controller& controller);
	virtual void onFrame(const Leap::Controller&);
};

#endif