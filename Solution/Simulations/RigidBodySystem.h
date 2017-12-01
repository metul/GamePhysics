#define RIGIDBODYSYSTEMSIMULATOR_h
#include "Simulator.h"


class RigidBodySystem {



public:
	//teil der notwendigen Methoden zur Vorberechnung und pro Zeitschritt
	void initializeInverseInertiaTensor();
	void calculatePosition(float timestep);
	void calculateLinearVelocity(float timestep);
	void calculateOrientation(float timestep);
	void calculateInertiaTensor(float timestep);




	//Attributes
	Vec3 position; //x_cm
	Vec3 size; 
	Quat orientation; // r
	int mass;
	Vec3 LinearVelocity; //v_cm
	Vec3 AngularVelocity; // w
	Vec3 AngularMomentum; // L

	//External Forces
	Vec3 Angular; //auf Folien q
	Vec3 Linear; //auf Folien F

	//Inertia Tensor
	Mat4d inertiaTensorRaw;
	Mat4d inertiaTensorInitial;
	Mat4d inertiaTensorCurrent;
	
	
};
