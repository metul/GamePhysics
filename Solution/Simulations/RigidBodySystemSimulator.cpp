#include "RigidBodySystemSimulator.h"

RigidBodySystemSimulator::RigidBodySystemSimulator()
{
	m_iTestCase = 0;
}

// Functions

const char * RigidBodySystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3,Demo4";
}

void RigidBodySystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	this->DUC = DUC;
	// TODO: Different UI for demo scenes?
	switch (m_iTestCase)
	{
	case 0:break;
	case 1:break;
	case 2:
		TwAddVarRW(DUC->g_pTweakBar, "Use Collision", TW_TYPE_BOOL8, &useCollision, "");
		break;
	case 3:break;
	default:break;
	}
}

void RigidBodySystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void RigidBodySystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	// TODO: Call different draw methods for demo scenes
	switch (m_iTestCase)
	{
	case 0: break;
	case 1: {
		Mat4 transformation = calculateTransform(0);
		drawRigidBox(transformation);	
	}	
		break;
	case 2: break;
	case 3: break;
	default: break;
	}
}

void RigidBodySystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	// Reset
	rigidBodies.clear();
	// TODO: Initialize different values for demo scenes?
	switch (m_iTestCase)
	{
	case 0:
	{
		//Debug
		addRigidBody(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.6f, 0.5f), 2.0f);
		setOrientationOf(0, Quat(Vec3(0.0f, 0.0f, 1.0f), (float)(M_PI)* 0.5f));
		applyForceOnBody(0, Vec3(0.3f, 0.5f, 0.25f), Vec3(1.0f, 1.0f, 0.0f));
		//rigidBodies[0].setExternalForces(Vec3(1, 1, 0));
		//rigidBodies[0].mainAlgorithm(2);
		foo(0, 2);
		Vec3 position, LinearVelocity, torque, AngularMomentum, AngularVelocity;
		Mat4d inertiaTensorCurrent;
		position = rigidBodies[0].getPosition();
		LinearVelocity = rigidBodies[0].getLinearVelocity();
		torque = rigidBodies[0].getTorque();
		AngularMomentum = rigidBodies[0].getMomentum();
		AngularVelocity = rigidBodies[0].getAngularVelocity();
		inertiaTensorCurrent = rigidBodies[0].getinertiaTensorCurrent();
		std::cout << "position:" << position << endl << "Velocity:" << LinearVelocity << endl <<
			"Torque:" << torque << endl << "AngularMomentum" << AngularMomentum << endl <<
			"InertiaTensor:" << endl << inertiaTensorCurrent << "AngularVelocity:" << AngularVelocity << std::endl;
	}
		break;
	case 1: {
		// Debug
		addRigidBody(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.5f, 0.5f), 2.0f);
		setOrientationOf(0, Quat(Vec3(0.0f, 0.0f, 1.0f), (float)(M_PI)* 0.5f));
		applyForceOnBody(0, Vec3(0.3f, 0.5f, 0.25f), Vec3(1.0f, 1.0f, 0.0f));
		//rigidBodies[0].setExternalForces(Vec3(1, 1, 0));
	}
		break;
	case 2: break;
	case 3: break;
	default: break;
	}
}

void RigidBodySystemSimulator::externalForcesCalculations(float timeElapsed)
{
	// Apply the mouse deltas to g_vfMovableObjectPos (move along cameras view plane)
	Point2D mouseDiff;
	mouseDiff.x = m_trackmouse.x - m_oldtrackmouse.x;
	mouseDiff.y = m_trackmouse.y - m_oldtrackmouse.y;
	if (mouseDiff.x != 0 || mouseDiff.y != 0)
	{
		Mat4 worldViewInv = Mat4(DUC->g_camera.GetWorldMatrix() * DUC->g_camera.GetViewMatrix());
		worldViewInv = worldViewInv.inverse();
		Vec3 inputView = Vec3((float)mouseDiff.x, (float)-mouseDiff.y, 0);
		Vec3 inputWorld = worldViewInv.transformVectorNormal(inputView);
		// find a proper scale!
		float inputScale = 0.001f;
		inputWorld = inputWorld * inputScale;
		m_externalForce = inputWorld;
		rigidBodies[0].applyForce(Vec3(m_mouse.x, m_mouse.y, 0), m_externalForce*10);
	}
}

void RigidBodySystemSimulator::simulateTimestep(float timeStep)
{
	// TODO: Update current setup for each frame
	switch (m_iTestCase)
	{
	case 0:
		break;
	case 1:	
		//rigidBodies[0].mainAlgorithm(timeStep);
		foo(0, 0.01);
		break;
	case 2:
		for (int i = 0; i < rigidBodies.size(); i++) {
			foo(i, timeStep);
		}
		break;
	case 3:
		break;
	default:
		break;
	}
}

void RigidBodySystemSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void RigidBodySystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

// Extra functions

int RigidBodySystemSimulator::getNumberOfRigidBodies()
{
	return rigidBodies.size();
}

Vec3 RigidBodySystemSimulator::getPositionOfRigidBody(int i)
{
	return rigidBodies[i].getPosition();
}

Vec3 RigidBodySystemSimulator::getLinearVelocityOfRigidBody(int i)
{
	return rigidBodies[i].getLinearVelocity();
}

Vec3 RigidBodySystemSimulator::getAngularVelocityOfRigidBody(int i)
{
	return rigidBodies[i].getAngularVelocity();
}

void RigidBodySystemSimulator::applyForceOnBody(int i, Vec3 loc, Vec3 force)
{
	//rigidBodies[i].setTorque(cross(loc, force));
	rigidBodies[i].applyForce(loc, force);
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass)
{
	RigidBodySystem tmp;
	tmp.setPosition(position);
	tmp.setSize(size);
	tmp.setMass(mass);
	tmp.setMomentum(Vec3(0,0,0));
	//tmp.setExternalForces(Vec3(1, 1, 0));
	rigidBodies.push_back(tmp);
}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation)
{
	rigidBodies[i].setOrientation(orientation);
	rigidBodies[i].initializeInverseInertiaTensor();
}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity)
{
	rigidBodies[i].setLinearVelocity(velocity);
}

void RigidBodySystemSimulator::drawRigidBox(Mat4 transformation)
{
	Vec3 emissiveColor, specularColor, diffuseColor;
	float specularPower;
	emissiveColor = Vec3();
	specularColor = 0.4 * Vec3(1, 1, 1);
	specularPower = 2000;
	diffuseColor = 0.5 * Vec3(1, 1, 1);
	DUC->setUpLighting(emissiveColor, specularColor, specularPower, diffuseColor);
	//BodyA.Obj2WorldMatrix = BodyA.scaleMat * BodyA.rotMat * BodyA.translatMat;
	//DUC->drawRigidBody( BodyA.Obj2WorldMatrix );
	DUC->drawRigidBody(transformation);
}

void RigidBodySystemSimulator::foo(int index, float timeStep)
{
	if (useCollision) {
		Mat4 transformA, transformB;
		transformA = calculateTransform(index);
		// Iterate over list to detect collision with other rigidbodies
		for (int i = 0; i < rigidBodies.size(); i++) {
			if (i != index) {
				transformB = calculateTransform(i);
				CollisionInfo simpletest = checkCollisionSAT(transformA, transformB);
				if (simpletest.isValid) {
					// Reaction
				}
			}
		}
	}
	rigidBodies[index].mainAlgorithm(timeStep);
}

Mat4 RigidBodySystemSimulator::calculateTransform(int index)
{
	Mat4 scale, rotation, translate;
	Vec3 tmpS = rigidBodies[index].getSize();
	scale = Mat4(tmpS.x, 0, 0, 0, 0, tmpS.y, 0, 0, 0, 0, tmpS.z, 0, 0, 0, 0, 1);
	rotation = rigidBodies[index].getOrientation().getRotMat();
	Vec3 tmpP = rigidBodies[index].getPosition();
	translate = Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tmpP.x, tmpP.y, tmpP.z, 1);
	Mat4 transformation = scale * rotation * translate;
	return transformation;
}