#ifndef MASSSPRINGSYSTEMSIMULATOR_h
#define MASSSPRINGSYSTEMSIMULATOR_h
#include "Simulator.h"

// Do Not Change
#define EULER 0
#define LEAPFROG 1
#define MIDPOINT 2
// Do Not Change

#include <vector>

struct Point {
	Vec3 position;
	Vec3 velocity;
	Vec3 force;
	bool isFixed;
};

struct Spring {
	int point1;
	int point2;
	float initialLength;
	float currentLength;
};

class MassSpringSystemSimulator:public Simulator{
public:
	// Construtors
	MassSpringSystemSimulator();
	
	// UI Functions
	const char * getTestCasesStr();
	void initUI(DrawingUtilitiesClass * DUC);
	void reset();
	void drawFrame(ID3D11DeviceContext* pd3dImmediateContext);
	void notifyCaseChanged(int testCase);
	void externalForcesCalculations(float timeElapsed);
	void simulateTimestep(float timeStep);
	void onClick(int x, int y);
	void onMouse(int x, int y);

	// Specific Functions
	void setMass(float mass);
	void setStiffness(float stiffness);
	void setDampingFactor(float damping);
	void setGravity(float gravity);
	int addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed);
	void addSpring(int masspoint1, int masspoint2, float initialLength);
	int getNumberOfMassPoints();
	int getNumberOfSprings();
	Vec3 getPositionOfMassPoint(int index);
	Vec3 getVelocityOfMassPoint(int index);
	void applyExternalForce(Vec3 force);
	void EulerStep(float timestep);
	void MidpointStep(float timestep);
	Vec3 calculateInternalForce(Spring spring);
	Vec3 calculateAcceleration(Vec3 force);
	Vec3 calculateNewVelocity(Point point, Vec3 acceleration, float timestep);
	void drawSphere(Vec3 position);
	void drawLine(Vec3 position1, Vec3 position2);
	
	// Do Not Change
	void setIntegrator(int integrator) {
		m_iIntegrator = integrator;
	}

private:
	// Data Attributes
	float m_fMass;
	float m_fStiffness;
	float m_fDamping;
	int m_iIntegrator;
	Vec3 m_fGravity;
	float sphereSize;

	// UI Attributes
	Vec3 m_externalForce;
	Point2D m_mouse;
	Point2D m_trackmouse;
	Point2D m_oldtrackmouse;
	bool useEuler;
	bool useGravity;
	bool mouseInput;

	// Storage
	vector<Point> points;
	vector<Spring> springs;
};
#endif