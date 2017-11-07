#include "MassSpringSystemSimulator.h";

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
}

// UI Functions

const char * MassSpringSystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3,Demo4";
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
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

void MassSpringSystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	// TODO: Call different draw methods for demo scenes
	switch (m_iTestCase)
	{
	case 0: break;
	case 1: break;
	case 2: break;
	case 3: break;
	}
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	// TODO: Initialize different values for demo scenes?
	switch (m_iTestCase)
	{
	case 0:
		cout << "Demo1 !\n";
		break;
	case 1:
		cout << "Demo2 !\n";
		break;
	case 2:
		cout << "Demo3 !\n";
		break;
	case 3:
		cout << "Demo4 !\n";
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	
}

void MassSpringSystemSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void MassSpringSystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

// Specific Functions

void MassSpringSystemSimulator::setMass(float mass)
{
	m_fMass = mass;
}

void MassSpringSystemSimulator::setStiffness(float stiffness)
{
	m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping)
{
	m_fDamping = damping;
}

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed)
{
	Point tmp;
	tmp.position = position;
	tmp.velocity = Velocity;
	tmp.isFixed = isFixed;
	points.push_back(tmp);
	return points.size() - 1; //Position of inserted Point 
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	Spring tmp;
	tmp.point1 = masspoint1;
	tmp.point2 = masspoint2;
	tmp.initialLength = initialLength;
	springs.push_back(tmp);
}

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	return points.size();
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return springs.size();
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index)
{
	return points[index].position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index)
{
	return points[index].velocity;
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
}
