#include "SphereSystem.h"

std::function<float(float)> SphereSystem::m_Kernels[5] = {
	[](float x) {return 1.0f; },              // Constant, m_iKernel = 0
	[](float x) {return 1.0f - x; },          // Linear, m_iKernel = 1, as given in the exercise Sheet, x = d/2r
	[](float x) {return (1.0f - x)*(1.0f - x); }, // Quadratic, m_iKernel = 2
	[](float x) {return 1.0f / (x)-1.0f; },     // Weak Electric Charge, m_iKernel = 3
	[](float x) {return 1.0f / (x*x) - 1.0f; },   // Electric Charge, m_iKernel = 4
};

void SphereSystem::AddPoint(Vec3 p, Vec3 v)
{
	Point tmp;
	tmp.pos = p;
	tmp.vel = v;
	s_points.push_back(tmp);
}

float SphereSystem::compute_repulsionForce(float d, int kernel)
{
	if (d < 2 * s_radius) {
		return scalingFactor * (m_Kernels[kernel](d / (2 * s_radius))); //(d / (2 * s_radius))
	}
	else {
		return 0.0f;
	}
}

float SphereSystem::compute_distance(Point p1, Point p2)
{
	Vec3 tmp;
	tmp = p2.pos - p1.pos;
	return vec_to_length(tmp);
}

float SphereSystem::vec_to_length(Vec3 v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

void SphereSystem::naive(float timestep, int kernel)
{
	for (int i = 0; i < s_points.size(); i++) {
		for (int j = i + 1; j < s_points.size(); j++) {
			MidPoint(i, j, timestep, kernel);
			/*cout << "p1: " << s_points[i].pos << " p2: " << s_points[j].pos << "\n";
			cout << "v1: " << s_points[i].vel << " v2: " << s_points[j].vel << "\n";*/
		}
	}

}

std::vector<Vec3> SphereSystem::updateForces(Point p1, Point p2, int kernel)
{
	std::vector<Vec3> forces;
	Vec3 result = compute_repulsionForce(compute_distance(p1, p2), kernel) * ((p1.pos - p2.pos) / compute_distance(p1, p2));
	//cout << "repulsion: " << result << "\n";
	forces.push_back(result + p1.vel * -s_damping);
	forces.push_back(-result + p2.vel * -s_damping);
	//cout << "f1: " << forces[0] << " f2:" << forces[1] << "\n";
	return forces;
}

Vec3 SphereSystem::updateAcceleration(Vec3 force)
{
	return  force / s_mass;
}

Vec3 SphereSystem::updateVelocity(Point point, Vec3 acceleration, float timestep)
{
	//cout << "a in upV: " << acceleration << "\n";
	Vec3 result = point.vel + acceleration * timestep;
	//cout << "res: " << result << "\n";
	return result;
}




void SphereSystem::MidPoint(int i, int j, float timestep, int kernel)
{
	Point p1 = s_points[i];
	Point p2 = s_points[j];
	// Calculate midpoint positions at t + h / 2
	Point p1temp, p2temp;
	p1temp = p1;
	p2temp = p2;
	Vec3 tmpPos1, tmpPos2;
	tmpPos1 = p1.pos + (timestep / 2) * p1.vel;
	tmpPos2 = p2.pos + (timestep / 2) * p2.vel;
	p1temp.pos = tmpPos1;
	p2temp.pos = tmpPos2;
	// Calculate force and acceleration at t
	//Vec3 currentForce = updateForces(p1, p2);
	std::vector<Vec3> forces;
	Vec3 acceleration1, acceleration2;
	Vec3 tmpVel1, tmpVel2;
	forces = updateForces(p1, p2, kernel);
	acceleration1 = updateAcceleration(forces[0]);
	acceleration2 = updateAcceleration(forces[1]);
	//cout << "at1: " << acceleration1 << " at2: " << acceleration2 << "\n";
	tmpVel1 = updateVelocity(p1, acceleration1, timestep / 2);
	tmpVel2 = updateVelocity(p2, acceleration2, timestep / 2);
	// Apply gravity
	tmpVel1 += s_fGravity * timestep / 2;
	tmpVel2 += s_fGravity * timestep / 2;
	//cout << "tvm1: " << tmpVel1 << " tvm2: " << tmpVel2 << "\n";
	p1temp.vel = tmpVel1;
	p2temp.vel = tmpVel2;
	// Calculate new positions at t + h
	Vec3 newPos1, newPos2;
	newPos1 = p1.pos + timestep * p1temp.vel;
	newPos2 = p2.pos + timestep * p2temp.vel;
	// Calculate midpoint force and acceleration for the velocity at t + h
	Vec3 newVel1, newVel2;
	forces = updateForces(p1temp, p2temp, kernel);
	acceleration1 = updateAcceleration(forces[0]);
	acceleration2 = updateAcceleration(forces[1]);
	//cout << "a1: " << acceleration1 << " a2: " << acceleration2 << "\n";
	// Calculate velocity at t + h
	newVel1 = updateVelocity(p1, acceleration1, timestep);
	newVel2 = updateVelocity(p2, acceleration2, timestep);
	// Apply gravity
	//cout << "vm1: " << newVel1 << " vm2: " << newVel2 << "\n";
	newVel1 += s_fGravity * timestep;
	newVel2 += s_fGravity * timestep;
	//Save Values
	p1.pos = newPos1;
	p2.pos = newPos2;
	p1.vel = newVel1;
	p2.vel = newVel2;
	s_points[i] = p1;
	s_points[j] = p2;
}

void SphereSystem::MidPointLinear(int i, float timestep)
{
	Point p1 = s_points[i];
	Point p1temp;
	p1temp = p1;
	Vec3 tmpPos1;
	tmpPos1 = p1.pos + (timestep / 2) * p1.vel;
	p1temp.pos = tmpPos1;
	Vec3 tmpVel1;
	// Apply gravity
	Vec3 forces = Vec3() + p1.vel * -s_damping;
	Vec3 acc = updateAcceleration(forces);
	tmpVel1 = updateVelocity(p1, acc, timestep / 2);
	tmpVel1 += s_fGravity * timestep / 2;
	p1temp.vel = tmpVel1;
	// Calculate new positions at t + h
	Vec3 newPos1;
	newPos1 = p1.pos + timestep * p1temp.vel;
	// Calculate midpoint force and acceleration for the velocity at t + h
	Vec3 newVel1;
	newVel1 = updateVelocity(p1, acc, timestep);
	// Apply gravity
	newVel1 += s_fGravity * timestep / 2;
	//Save Values
	p1.pos = newPos1;
	p1.vel = newVel1;
	s_points[i] = p1;
}

void SphereSystem::BoundingBoxCheck(float times)
{
	for (size_t i = 0; i < s_points.size(); i++)
	{
		Vec3 pos = s_points[i].pos;
		Vec3 vel = s_points[i].vel;

		for (int f = 0; f < 6; f++)
		{
			float sign = (f % 2 == 0) ? -1.0f : 1.0f;
			if (sign * pos.value[f / 2] < -0.5f * times)
			{
				pos.value[f / 2] = sign * -0.5f * times;
				vel.value[f / 2] = 0;
			}
		}

		s_points[i].pos = pos;
		s_points[i].vel = vel;
	}
}

// MARK (pointer and reference)
void SphereSystem::setInGrid(int i, int *gSlots, int *gCounter, std::vector<int> * gHelper)
{
	bool helpBool = false;
	// float gridSize = 2 * s_radius;
	// int numberGridsPerAxis = 1 / gridSize;
	int ballSlots = 10; // Hardcoded ball slots value
	Point p = s_points[i];
	int gridX =  (p.pos.x + 0.5f) / m_GridSize;
	int gridY = (p.pos.y + 0.5f) / m_GridSize;
	int gridZ = (p.pos.z + 0.5f) / m_GridSize;
	int index = (pow(m_numGridsPerAxis, 2) * gridY + gridZ * m_numGridsPerAxis + gridX) * ballSlots;
	int gridIndex = index / ballSlots;
	if (isBallAlreadyInGrid(i, gridIndex))
		return;
	while (gSlots[index] != -1) {
		index++;
		helpBool = true;
	}
	gSlots[index] = i;
	resetOldIndex(i, gSlots, gCounter, gHelper, ballSlots);
	s_points[i].gridIndex = gridIndex;
	gCounter[gridIndex]++;
	if (!helpBool)
		gHelper -> push_back(gridIndex);
}

bool SphereSystem::isBallAlreadyInGrid(int ballID, int gridIndex)
{
	return s_points[ballID].gridIndex == gridIndex;
}


void SphereSystem::initializeGrid()
{
	m_GridSize = 2 * s_radius;
	m_numGridsPerAxis = 1 / m_GridSize;
	int numberGrids = pow(m_numGridsPerAxis, 3);
	int ballSlots = 10; // Hardcoded ball slots value
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

void SphereSystem::uniformGrid(float timeStep, int kernel)
{
	for (int i = 0; i < getSizePointVector(); i++) {
		setInGrid(i, gridSlots, gridCounter, &gridHelper);
	}
	// TODO (simulate) 
	for (std::vector<int>::iterator it = gridHelper.begin(); it != gridHelper.end(); ++it) {
		// Add number of balls in 3*3 neigbour grids
		// (x, y, z) -> it
		// (x + 1, y, z) -> it + 1
		// (x, y, z + 1) -> it + numberGridsPerAxis
		// (x, y + 1, z) -> it + numberGridsPerAxis^2
		int numberOfBallsInNeighbouringGrids = 0;
		for (int y = -1; y <= 1; y++) {
			for (int z = -1; z <= 1; z++) {
				for (int x = -1; x <= 1; x++) {
					int tmpIndex = pow(m_numGridsPerAxis, 2.f) * y + m_numGridsPerAxis * z + x + *it;
					if (tmpIndex < 0 || tmpIndex >= pow(m_numGridsPerAxis, 3))
						continue;
					numberOfBallsInNeighbouringGrids += gridCounter[tmpIndex];
				}
			}
		}
		//int numberOfBallsInGrid = gridCounter[*it];
		if (numberOfBallsInNeighbouringGrids == 1) {
			// MidPointLinear()
			int ballID = -1;
			int ballSlots = 10;
			for (int i = *it * ballSlots; i < *it * ballSlots + ballSlots; i++) {
				if (gridSlots[i] != -1) {
					ballID = gridSlots[i];
				}
			}
			MidPointLinear(ballID, timeStep);
		}
		else if (numberOfBallsInNeighbouringGrids > 1) {
			// MidPoint()
			int ballID1, ballID2;
			int ballSlots = 10;
			ballID1 = ballID2 = -1;
			for (int i = *it * ballSlots; i < *it * ballSlots + ballSlots; i++) {
				if (gridSlots[i] != -1) {
					ballID1 = gridSlots[i];
					// Same grid
					for (int j = i + 1; j < *it * ballSlots + ballSlots; j++) {
						if (gridSlots[j] != -1) {
							ballID2 = gridSlots[j];
							MidPoint(ballID1, ballID2, timeStep, kernel);
						}
					}
					// Neighbour grids
					for (int y = -1; y <= 1; y++) {
						for (int z = -1; z <= 1; z++) {
							for (int x = -1; x <= 1; x++) {
								if (x == 0 && y == 0 && z == 0)
									continue;
								int tmpIndex = pow(m_numGridsPerAxis, 2.f) * y + m_numGridsPerAxis * z + x + *it;
								// Check if tmpIndex is valid
								if (tmpIndex < 0 || tmpIndex >= pow(m_numGridsPerAxis, 3))
									continue;
								for (int i = tmpIndex * ballSlots; i < tmpIndex * ballSlots + ballSlots; i++) {
									if (gridSlots[i] != -1) {
										ballID2 = gridSlots[i];
										MidPoint(ballID1, ballID2, timeStep, kernel);
									}
								}
							}
						}
					}
				}
			}
		}
	} // MARK

}

void SphereSystem::resetOldIndex(int ballID, int * gSlots, int * gCounter, std::vector<int> * gHelper, int ballSlots)
{
	int gridIndex = s_points[ballID].gridIndex;
	if (gridIndex == -1)
		return;
	for (int i = gridIndex * ballSlots; i < gridIndex * ballSlots + ballSlots; i++) {
		if (gSlots[i] == ballID) {
			gSlots[i] = -1;
			gCounter[gridIndex]--;
			if (gCounter[gridIndex] == 0) {
				// Remove grid index from gHelper
				std::vector<int>::iterator it;
				it = find(gHelper -> begin(), gHelper -> end(), gridIndex);
				if (it != gHelper -> end())
				{
					gHelper -> erase(it);
				}
			}
		}
	}
}


