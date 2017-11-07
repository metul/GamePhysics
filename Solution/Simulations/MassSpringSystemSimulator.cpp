#include "MassSpringSystemSimulator.h";

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
}

// UI Functions

const char * MassSpringSystemSimulator::getTestCasesStr()
{
	return nullptr;
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
}

void MassSpringSystemSimulator::reset()
{
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	
}

void MassSpringSystemSimulator::onClick(int x, int y)
{
}

void MassSpringSystemSimulator::onMouse(int x, int y)
{
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
	return points.size - 1; //Position of inserted Point 
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
	return points.size;
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return springs.size;
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
