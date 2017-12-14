#include "SphereSystemSimulator.h"

std::function<float(float)> SphereSystemSimulator::m_Kernels[5] = {
	[](float x) {return 1.0f; },              // Constant, m_iKernel = 0
	[](float x) {return 1.0f - x; },          // Linear, m_iKernel = 1, as given in the exercise Sheet, x = d/2r
	[](float x) {return (1.0f - x)*(1.0f - x); }, // Quadratic, m_iKernel = 2
	[](float x) {return 1.0f / (x)-1.0f; },     // Weak Electric Charge, m_iKernel = 3
	[](float x) {return 1.0f / (x*x) - 1.0f; },   // Electric Charge, m_iKernel = 4
};

// SphereSystemSimulator member functions

SphereSystemSimulator::SphereSystemSimulator()
{
	m_iTestCase = 0;
}

const char * SphereSystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3";
}

void SphereSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
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

void SphereSystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void SphereSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	switch (m_iTestCase) {
	case 0: {
		SphereSystem s = m_pSphereSystem[0];
		drawSphere(s.getPosition(0),s.getRadius());
		drawSphere(s.getPosition(1),s.getRadius());
	}
		break;
	case 1: break;
	case 2: break;
	default:
		cout << "Empty Test!\n";
		break;

	}
}

void SphereSystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	switch (m_iTestCase) {
	case 0: {
		SphereSystem sphereSystem = SphereSystem();
		sphereSystem.setDamping(0.01f);
		sphereSystem.setGravity(Vec3(0, -9.81, 0));
		sphereSystem.setMass(0.1f);
		sphereSystem.setRadius(0.05);
		sphereSystem.setScalingFactor(100.0f);
		sphereSystem.AddPoint(Vec3(0, 0.3, 0), Vec3());
		sphereSystem.AddPoint(Vec3(0, 0.15, 0), Vec3());
		m_pSphereSystem.clear();
		m_pSphereSystem.push_back(sphereSystem);
	}
			break;
	case 1:break;
	case 2:break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

void SphereSystemSimulator::externalForcesCalculations(float timeElapsed)
{
	Vec3 pullforce(0, 0, 0);
	Point2D mouseDiff;
	mouseDiff.x = m_trackmouse.x - m_oldtrackmouse.x;
	mouseDiff.y = m_trackmouse.y - m_oldtrackmouse.y;
	if (mouseDiff.x != 0 || mouseDiff.y != 0)
	{
		Mat4 worldViewInv = Mat4(DUC->g_camera.GetWorldMatrix() * DUC->g_camera.GetViewMatrix());
		worldViewInv = worldViewInv.inverse();
		Vec3 forceView = Vec3((float)mouseDiff.x, (float)-mouseDiff.y, 0);
		Vec3 forceWorld = worldViewInv.transformVectorNormal(forceView);
		float forceScale = 0.03f;
		pullforce = pullforce + (forceWorld * forceScale);
	}
	//pullforce -=  pullforce * 5.0f * timeElapsed;
	// Gravity
	Vec3 gravity = Vec3(0, -9.81f, 0);
	m_externalForce = gravity + pullforce;
}

void SphereSystemSimulator::simulateTimestep(float timeStep)
{
	switch (m_iTestCase) {
	case 0: {
		m_pSphereSystem[0].naive(timeStep);
		m_pSphereSystem[0].BoundingBoxCheck();
	}
		break;
	case 1: break;
	case 2: break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

void SphereSystemSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void SphereSystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void SphereSystemSimulator::drawSphere(Vec3 position, Vec3 s)
{
	Vec3 emissiveColor, specularColor, diffuseColor;
	float specularPower;
	emissiveColor = Vec3();
	specularColor = 0.4 * Vec3(1, 1, 1);
	specularPower = 100;
	diffuseColor = 0.6 * Vec3(1, 1, 1);
	DUC->setUpLighting(emissiveColor, specularColor, specularPower, diffuseColor);
	Vec3 scale = s * Vec3(1, 1, 1);
	DUC->drawSphere(position, scale);
}