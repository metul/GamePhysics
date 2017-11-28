#include "RigidBodySystem.h"

void RigidBodySystem::initializeInverseInertiaTensor()
{
	//Inverse Inertia Tensor initialisieren, muss 4x4 sein, da auch Rotationsmatrix 4x4
	float h = position.y;
	float w = position.x;
	float d = position.z;
	float I_h = mass / 12 * (pow(w, 2) + pow(d, 2));
	float I_w = mass / 12 * (pow(d, 2) + pow(h, 2));
	float I_d = mass / 12 * (pow(w, 2) + pow(h, 2));
	inertiaTensorInitial.initRotationXYZ(I_h, I_w, I_d);
	std::cout << orientation.getRotMat() << "for real" << std::endl;
	std::cout << inertiaTensorInitial << "for real" << std::endl;
	
	
}
