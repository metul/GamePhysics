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
}

const char * SphereSystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3";
}

void SphereSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
}

void SphereSystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void SphereSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
}

void SphereSystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
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
