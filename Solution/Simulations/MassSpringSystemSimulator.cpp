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
	springs.clear();
	points.clear();
	// TODO: Initialize different values for demo scenes?
	switch (m_iTestCase)
	{
	case 0:
	{
		cout << "Demo1 !\n";
		setMass(10);
		setStiffness(40);
		int massPoint1, massPoint2;
		massPoint1 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
		massPoint2 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
		addSpring(massPoint1, massPoint2, 1);

		// Determines how many steps to calculate
		int numSteps = 3;

		for (int i = 0; i < numSteps; i++) {
			// Calculate one euler step
			EulerStep(0.1f);
			// Print results
			cout << "Euler step " << i + 1 << ":\n";
			for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				std::cout << "Position: " << it->position << " Velocity: " << it->velocity << std::endl;
			}
		}

		// Reset
		springs.clear();
		points.clear();
		massPoint1 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
		massPoint2 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
		addSpring(massPoint1, massPoint2, 1);

		for (int i = 0; i < numSteps; i++) {
			// Calculate one midpoint step
			MidpointStep(0.1f);
			// Print values
			cout << "Midpoint step " << i + 1 << ":\n";
			for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				std::cout << "Position: " << it->position << " Velocity: " << it->velocity << std::endl;
			}
		}
	}
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
	tmp.currentLength = initialLength;
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

void MassSpringSystemSimulator::EulerStep(float timestep)
{
	for (int i = 0; i < springs.size(); i++) {
		Spring currentSpring = springs[i];
		Vec3 currentForce = calculateInternalForce(currentSpring);
		Vec3 currentAcceleration = calculateAcceleration(currentForce);
		// Calculate new positions
		Point p1 = points[currentSpring.point1];
		Point p2 = points[currentSpring.point2];
		Vec3 newPos1, newPos2;
		newPos1 = p1.position + timestep * p1.velocity;
		newPos2 = p2.position + timestep * p2.velocity;
		// Calculate new velocities
		Vec3 newVel1, newVel2;
		newVel1 = calculateNewVelocity(p1, currentAcceleration, timestep);
		newVel2 = calculateNewVelocity(p2, -currentAcceleration, timestep);
		// Calculate current length
		Vec3 diff = newPos1 - newPos2;
		float newLength = sqrtf(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
		// Save new values
		p1.position = newPos1;
		p2.position = newPos2;
		p1.velocity = newVel1;
		p2.velocity = newVel2;
		points[currentSpring.point1] = p1;
		points[currentSpring.point2] = p2;
		currentSpring.currentLength = newLength;
		springs[i] = currentSpring;
	}

}

void MassSpringSystemSimulator::MidpointStep(float timestep)
{
	for (int i = 0; i < springs.size(); i++) {
		Spring currentSpring = springs[i];
		Point p1 = points[currentSpring.point1];
		Point p2 = points[currentSpring.point2];
		// Calculate midpoint positions at t + h / 2
		Point p1temp, p2temp;
		p1temp = p1;
		p2temp = p2;
		Vec3 tmpPos1, tmpPos2;
		tmpPos1 = p1.position + (timestep / 2) * p1.velocity;
		tmpPos2 = p2.position + (timestep / 2) * p2.velocity;
		p1temp.position = tmpPos1;
		p2temp.position = tmpPos2;
		
		/* MARK
		points[currentSpring.point1] = p1temp;
		points[currentSpring.point2] = p2temp;
		MARK */ 

		//std::cout << "p1temp: " << p1temp.position << " p2temp: " << p2temp.position << std::endl;
		//std::cout << "currentLength: " << currentSpring.currentLength << " newLength: " << newLengthTemp << std::endl;
		// Calculate force and acceleration at t
		Vec3 currentForce = calculateInternalForce(currentSpring);
		Vec3 currentAcceleration = calculateAcceleration(currentForce);
		//std::cout << "currentForce: " << currentForce << " currentAcceleration: " << currentAcceleration << std::endl;
		// Calculate velocity at t + h / 2
		Vec3 tmpVel1, tmpVel2;
		tmpVel1 = calculateNewVelocity(p1, currentAcceleration, timestep / 2);
		tmpVel2 = calculateNewVelocity(p2, -currentAcceleration, timestep / 2);
		p1temp.velocity = tmpVel1;
		p2temp.velocity = tmpVel2;
		// Calculate new positions at t + h
		Vec3 newPos1, newPos2;
		newPos1 = p1.position + timestep * p1temp.velocity;
		newPos2 = p2.position + timestep * p2temp.velocity;
		// Calculate current spring length at t + h / 2
		Vec3 diff = p1temp.position - p2temp.position;
		float newLength = sqrtf(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
		currentSpring.currentLength = newLength;
		// Calculate midpoint force and acceleration for the velocity at t + h
		currentForce = calculateInternalForce(currentSpring);
		currentAcceleration = calculateAcceleration(currentForce);
		//std::cout << "currentForce: " << currentForce << " currentAcceleration: " << currentAcceleration << std::endl;
		// Calculate velocity at t + h
		Vec3 newVel1, newVel2;
		newVel1 = calculateNewVelocity(p1, currentAcceleration, timestep);
		newVel2 = calculateNewVelocity(p2, -currentAcceleration, timestep);
		// Calculate current length
		diff = newPos1 - newPos2;
		newLength = sqrtf(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
		// Save new values
		p1.position = newPos1;
		p2.position = newPos2;
		p1.velocity = newVel1;
		p2.velocity = newVel2;
		points[currentSpring.point1] = p1;
		points[currentSpring.point2] = p2;
		currentSpring.currentLength = newLength;
		springs[i] = currentSpring;
	}
}

Vec3 MassSpringSystemSimulator::calculateInternalForce(Spring spring)
{
	Point p1 = points[spring.point1];
	Point p2 = points[spring.point2];
	Vec3 result = -m_fStiffness * (spring.currentLength - spring.initialLength) * ((p1.position - p2.position) / spring.currentLength);
	return result;
}

Vec3 MassSpringSystemSimulator::calculateAcceleration(Vec3 force)
{
	return force / m_fMass;
}

Vec3 MassSpringSystemSimulator::calculateNewVelocity(Point point, Vec3 acceleration, float timestep)
{
	return point.velocity + acceleration * timestep;
}

