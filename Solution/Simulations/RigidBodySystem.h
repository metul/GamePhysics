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
	Vec3 position;
	Vec3 size;
	Quat orientation;
	int mass;
	Vec3 LinearVelocity;
	Vec3 AngularVelocity;

	//External Forces
	Vec3 Angular; //auf Folien q
	Vec3 Linear; //auf Folien F

	//Inertia Tensor
	Mat4f inertiaTensorRaw;
	Mat4f inertiaTensorInitial;
	Mat4f inertiaTensor;
	
	
};
