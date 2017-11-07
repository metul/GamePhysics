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
	tmp.mass = m_fMass;
	tmp.damping = m_fDamping;
	return 0;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	Spring tmp;
	tmp.point1 = masspoint1;
	tmp.point2 = masspoint2;
	tmp.initialLength = initialLength;
	tmp.stiffness = m_fStiffness;
}

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	return 0;
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return 0;
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index)
{
	return Vec3();
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index)
{
	return Vec3();
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
}
