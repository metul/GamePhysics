﻿#include "SphereSystemSimulator.h"

//std::function<float(float)> SphereSystemSimulator::m_Kernels[5] = {
//	[](float x) {return 1.0f; },              // Constant, m_iKernel = 0
//	[](float x) {return 1.0f - x; },          // Linear, m_iKernel = 1, as given in the exercise Sheet, x = d/2r
//	[](float x) {return (1.0f - x)*(1.0f - x); }, // Quadratic, m_iKernel = 2
//	[](float x) {return 1.0f / (x)-1.0f; },     // Weak Electric Charge, m_iKernel = 3
//	[](float x) {return 1.0f / (x*x) - 1.0f; },   // Electric Charge, m_iKernel = 4
//};

// SphereSystemSimulator member functions

SphereSystemSimulator::SphereSystemSimulator()
{
	m_iTestCase = 0;
	m_iNumSpheres = 45;
	m_fDamping = 0.7f;
	m_fForceScaling = 10.f;
	m_fMass = 0.1f;
	m_fRadius = 0.1f;
	m_fGravity = 0.1f;
	m_iKernel = 1;
	isVisuell = true;
	m_GridSize = 2 * m_fRadius;
	m_numGridsPerAxis = 1 / m_GridSize;
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
	case 0: {
		TwAddVarRW(DUC->g_pTweakBar, "Visuell", TW_TYPE_BOOL8, &isVisuell, "");
		TwAddVarRW(DUC->g_pTweakBar, "Mass", TW_TYPE_FLOAT, &m_fMass, "");
		TwAddVarRW(DUC->g_pTweakBar, "Radius", TW_TYPE_FLOAT, &m_fRadius, "");
		TwAddVarRW(DUC->g_pTweakBar, "ForceScaling", TW_TYPE_FLOAT, &m_fForceScaling, "");
		TwAddVarRW(DUC->g_pTweakBar, "Damping", TW_TYPE_FLOAT, &m_fDamping, "");
		TwAddVarRW(DUC->g_pTweakBar, "# of Spheres",TW_TYPE_INT32, &m_iNumSpheres, "");
		TwAddVarRW(DUC->g_pTweakBar, "Kernel", TW_TYPE_INT32, &m_iKernel, "");
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_FLOAT, &m_fGravity, "");
	}
		break;
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
		if (isVisuell) {
			for (int i = 0; i < m_pSphereSystem[0].getSizePointVector(); i++) {
				drawSphere(m_pSphereSystem[0].getPosition(i), m_pSphereSystem[0].getRadius());
			}
		}
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
		m_pSphereSystem.clear();
		switch (m_iTestCase) {
		case 0: {
			SphereSystem sphereSystem = SphereSystem();
			sphereSystem.setDamping(m_fDamping);
			sphereSystem.setGravity(Vec3(0, -m_fGravity, 0));
			sphereSystem.setMass(m_fMass);
			sphereSystem.setRadius(m_fRadius);
			sphereSystem.setScalingFactor(m_fForceScaling);
			float distance = m_fRadius + (6 * m_fRadius / 5);
			float boxSize = 1;
			int numSpheresPerAxis = boxSize / distance;
			int remainingSpheres = m_iNumSpheres;
			float posX, posY, posZ;
			// Box boundary
			float offset = 0.5f - m_fRadius;
			for (int y = 0; y < numSpheresPerAxis; y++) {
				float offsetX = (y % 2 == 0) ? 0.f : -(2 * m_fRadius / 5);
				float offsetZ = (y % 2 == 0) ? 0.f : -(2 * m_fRadius / 5);
				if (remainingSpheres < 1)
					break;
				for (int z = 0; z < numSpheresPerAxis; z++) {
					if (remainingSpheres < 1)
						break;
					for (int x = 0; x < numSpheresPerAxis; x++) {
						// Initialize position
						posX = offset - x * distance + offsetX;
						posY = offset - y * distance;
						posZ = offset - z * distance + offsetZ;
						sphereSystem.AddPoint(Vec3(posX, posY, posZ), Vec3());
						// Check remaining spheres
						remainingSpheres--;
						if (remainingSpheres < 1)
							break;
					}
				}
			}
			m_pSphereSystem.push_back(sphereSystem);
			initializeGrid();
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
		Vec3 gravity = Vec3(0, -m_fGravity, 0);
		m_externalForce = gravity + pullforce;
	}

	void SphereSystemSimulator::simulateTimestep(float timeStep)
	{
		switch (m_iTestCase) {
		case 0: {
			m_pSphereSystem[0].setGravity(m_externalForce);
			m_pSphereSystem[0].naive(timeStep, m_iKernel);
			m_pSphereSystem[0].BoundingBoxCheck();
			for (int i = 0; i < m_pSphereSystem[0].getSizePointVector(); i++) {
				m_pSphereSystem[0].setInGrid(i, gridSlots, gridCounter, gridHelper);
			}
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

	void SphereSystemSimulator::initializeGrid()
	{
		m_GridSize = 2 * m_fRadius;
		m_numGridsPerAxis = 1 / m_GridSize;
		int numberGrids = pow(m_numGridsPerAxis, 3);
		int ballSlots = 10; // MARK
		numberOfGridCells = ballSlots * numberGrids;
		gridSlots = new int[numberOfGridCells];
		gridCounter = new int[numberGrids];
		// Fill all slots with -1 // MARK
		for (int i = 0; i < numberOfGridCells; i++) {
			gridSlots[i] = -1;
		}
		// Fill grid ball numbers with 0 // MARK
		for (int i = 0; i < numberGrids; i++) {
			gridCounter[i] = 0;
		}
	}
