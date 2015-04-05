#include "SimpleListener.h"
using namespace Leap;

enum Direction{ NONE, RIGHT, LEFT, DOWN, UP };
Direction leapDirection = NONE;

void SimpleListener::onConnect(const Controller& controller) {
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SimpleListener::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();

	const GestureList gestures = frame.gestures();

	for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];
		if (gesture.type() == Gesture::TYPE_SWIPE) {
			SwipeGesture swipe = gesture;
			Vector direction = swipe.direction();
			if (direction.x > 0.7) {
				std::cout << "right" << std::endl;
				leapDirection = RIGHT;
			}
			else if (direction.x < -0.7) {
				std::cout << "left" << std::endl;
				leapDirection = LEFT;
			}
			else if (direction.y < -0.9) {
				std::cout << "down" << std::endl;
			}
			else if (direction.y > 0.9) {
				std::cout << "up" << std::endl;
			}
			else if (direction.z < -0.9) {
				std::cout << "push" << std::endl;
			}
			else if (direction.z > 0.9) {
				std::cout << "pull" << std::endl;
			}
		}
	}
}