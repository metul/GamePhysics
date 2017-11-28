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
	case 2:break;
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
	case 1: break;
	case 2: break;
	case 3: break;
	default: break;
	}
}

void RigidBodySystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	// TODO: Initialize different values for demo scenes?
	switch (m_iTestCase)
	{
	case 0: 
		//Debug
		addRigidBody(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.6f, 0.5f), 2.0f);
		setOrientationOf(0, Quat(Vec3(0.0f, 0.0f, 1.0f), (float)(M_PI)* 0.5f));
		//applyForceOnBody(0, Vec3(0.3f, 0.5f, 0.25f), Vec3(1.0f, 1.0f, 0.0f));
		break;
	case 1: break;
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
	}
	else {
		m_externalForce = Vec3(0, 0, 0);
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
		break;
	case 2:
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
	return rigidBodies[i].position;
}

Vec3 RigidBodySystemSimulator::getLinearVelocityOfRigidBody(int i)
{
	return rigidBodies[i].LinearVelocity;
}

Vec3 RigidBodySystemSimulator::getAngularVelocityOfRigidBody(int i)
{
	return rigidBodies[i].AngularVelocity;
}

void RigidBodySystemSimulator::applyForceOnBody(int i, Vec3 loc, Vec3 force)
{
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass)
{
	RigidBodySystem tmp;
	tmp.position = position;
	tmp.size = size;
	tmp.mass = mass;
	tmp.initializeInverseInertiaTensor();
	rigidBodies.push_back(tmp);
}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation)
{
	rigidBodies[i].orientation = orientation;
}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity)
{
	rigidBodies[i].LinearVelocity = velocity;
}