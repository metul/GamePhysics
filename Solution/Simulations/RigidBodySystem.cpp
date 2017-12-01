#include "RigidBodySystem.h"

void RigidBodySystem::initializeInverseInertiaTensor()
{
	//Inverse Inertia Tensor initialisieren, muss 4x4 sein, da auch Rotationsmatrix 4x4
	double w = size.x;
	double h = size.y;
	double d = size.z;
	double I_w = ((pow(h, 2) + pow(d, 2)) / 12)*mass;
	double I_h = ((pow(w, 2) + pow(d, 2)) / 12)*mass;
	double I_d = ((pow(w, 2) + pow(h, 2)) / 12)*mass;
	inertiaTensorRaw  = Mat4d(I_w, 0, 0, 0, 0, I_h, 0, 0, 0, 0, I_d, 0, 0, 0, 0, 1);
	Mat4d rotMat = orientation.getRotMat();
	rotMat.transpose();
	inertiaTensorInitial = orientation.getRotMat() * inertiaTensorRaw.inverse() * rotMat;
	std::cout << inertiaTensorRaw << " " << orientation.getRotMat() << std::endl;
	std::cout << inertiaTensorInitial << std::endl;
	
}
