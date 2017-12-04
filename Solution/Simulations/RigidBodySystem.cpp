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
	//Mat4d rotMat = orientation.getRotMat();
	//rotMat.transpose();
	//inertiaTensorInitial = orientation.getRotMat() * inertiaTensorRaw.inverse() * rotMat;
	inertiaTensorInitial = inertiaTensorRaw.inverse();
	//std::cout << inertiaTensorInitial << std::endl;	
}

void RigidBodySystem::calculatePosition(float timestep)
{
	position += timestep * LinearVelocity;
}

void RigidBodySystem::calculateLinearVelocity(float timestep)
{
	LinearVelocity += timestep * externalForces / mass;
}

void RigidBodySystem::calculateOrientation(float timestep)
{
	double x = AngularVelocity.x;
	double y = AngularVelocity.y;
	double z = AngularVelocity.z;
	orientation += timestep / 2 * Quat(0, x, y, z) * orientation;
}

void RigidBodySystem::calculateInertiaTensor()
{
	Mat4d rotMat = orientation.getRotMat();
	rotMat.transpose();
	inertiaTensorCurrent = orientation.getRotMat() * inertiaTensorInitial * rotMat;

}

void RigidBodySystem::calculateAngularMomentum(float timestep)
{
	AngularMomentum += timestep * torque;
}

void RigidBodySystem::calculateAngularVelocity()
{
	AngularVelocity = inertiaTensorCurrent * AngularMomentum;
}

void RigidBodySystem::mainAlgorithm(float timestep)
{
	calculatePosition(timestep);
	calculateLinearVelocity(timestep);
	calculateOrientation(timestep);
	calculateAngularMomentum(timestep);
	calculateInertiaTensor();
	calculateAngularVelocity();

	//std::cout << "position:" << position << " velocity:" << LinearVelocity << " torque:" << torque << " AngularMomentum" << AngularMomentum << " InertiaTensor:" << inertiaTensorCurrent << " AngularVelocity:" << AngularVelocity << std::endl;
}

Vec3 RigidBodySystem::getPosition()
{
	return position;
}

Vec3 RigidBodySystem::getSize()
{
	return size;
}

Quat RigidBodySystem::getOrientation()
{
	return orientation;
}

int RigidBodySystem::getMass()
{
	return mass;
}

Vec3 RigidBodySystem::getLinearVelocity()
{
	return LinearVelocity;
}

Vec3 RigidBodySystem::getAngularVelocity()
{
	return AngularVelocity;
}

Vec3 RigidBodySystem::getMomentum()
{
	return AngularMomentum;
}

void RigidBodySystem::setPosition(Vec3 p)
{
	position = p;
}

void RigidBodySystem::setSize(Vec3 s)
{
	size = s;
}

void RigidBodySystem::setOrientation(Quat o)
{
	orientation = o;
}

void RigidBodySystem::setMass(int m)
{
	mass = m;
}

void RigidBodySystem::setLinearVelocity(Vec3 lV)
{
	LinearVelocity = lV;
}

void RigidBodySystem::setAngularVelocity(Vec3 aV)
{
	AngularVelocity = aV;
}

void RigidBodySystem::setMomentum(Vec3 m)
{
	AngularMomentum = m;
}

Vec3 RigidBodySystem::getTorque()
{
	return torque;
}

Vec3 RigidBodySystem::getExternalForces()
{
	return externalForces;
}

void RigidBodySystem::setTorque(Vec3 t)
{
	torque = t;
}

void RigidBodySystem::setExternalForces(Vec3 f)
{
	externalForces = f;
}

void RigidBodySystem::applyForce(Vec3 loc, Vec3 force)
{
	setTorque(cross(loc, force));
	setExternalForces(force);
}

