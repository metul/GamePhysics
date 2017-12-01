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

	// Getter and setters
	Vec3 getPosition();
	Vec3 getSize();
	Quat getOrientation();
	int getMass();
	Vec3 getLinearVelocity();
	Vec3 getAngularVelocity();
	Vec3 getMomentum(); 
	void setPosition(Vec3 p);
	void setSize(Vec3 s);
	void setOrientation(Quat o);
	void setMass(int m);
	void setLinearVelocity(Vec3 lV);
	void setAngularVelocity(Vec3 aV);
	void setMomentum(Vec3 m);

	Vec3 getTorque();
	Vec3 getExternalForces();
	void setTorque(Vec3 t);
	void setExternalForces(Vec3 f);


private:
	//Attributes
	Vec3 position; //x_cm
	Vec3 size; 
	Quat orientation; // r
	int mass;
	Vec3 LinearVelocity; //v_cm
	Vec3 AngularVelocity; // w
	Vec3 AngularMomentum; // L

	//External Forces
	Vec3 torque; //auf Folien q
	Vec3 externalForces; //auf Folien F

	//Inertia Tensor
	Mat4d inertiaTensorRaw;
	Mat4d inertiaTensorInitial;
	Mat4d inertiaTensorCurrent;
	
	
};
