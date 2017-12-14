#include "SphereSystem.h"

void SphereSystem::AddPoint(Vec3 p, Vec3 v)
{
	Point tmp;
	tmp.pos = p;
	tmp.vel = v;
	s_points.push_back(tmp);
}

float SphereSystem::compute_repulsionForce(float d)
{
	if (d < 2 * s_radius) {
		return scalingFactor *(1 - (d / (2 * s_radius)));
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

void SphereSystem::naive(float timestep)
{
	for (int i = 0; i < s_points.size(); i++) {
		for (int j = i + 1; j < s_points.size(); j++) {
			MidPoint(i, j, timestep);
		}
	}
}

Vec3 SphereSystem::updateForces(Point p1, Point p2)
{
	Vec3 result = compute_repulsionForce(compute_distance(p1,p2)) * (p1.pos - p2.pos);
	result += p1.vel * -s_damping;
	return result;
}

Vec3 SphereSystem::updateAcceleration(Vec3 force)
{
	return  force / s_mass;
}

Vec3 SphereSystem::updateVelocity(Point point, Vec3 acceleration, float timestep)
{
	return point.vel + acceleration * timestep;
}

std::vector<Vec3> SphereSystem::computeForce() {
	std::vector<Vec3> result;
	return result;
}

void SphereSystem::MidPoint(int i, int j, float timestep)
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
	p1temp.pos= tmpPos1;
	p2temp.pos = tmpPos2;
	// Calculate force and acceleration at t
	//Vec3 currentForce = updateForces(p1, p2);
	std::vector<Vec3> forces = computeForce();
	//Vec3 currentAcceleration = updateAcceleration(currentForce);
	Vec3 acceleration1, acceleration2;
	acceleration1 = updateAcceleration(forces[0]);
	acceleration2 = updateAcceleration(forces[1]);
	// Calculate velocity at t + h / 2
	Vec3 tmpVel1, tmpVel2;
	//tmpVel1 = updateVelocity(p1, currentAcceleration, timestep / 2);
	//tmpVel2 = updateVelocity(p2, -currentAcceleration, timestep / 2);
	tmpVel1 = updateVelocity(p1, acceleration1, timestep / 2);
	tmpVel2 = updateVelocity(p2, acceleration2, timestep / 2);
	// Apply gravity
	tmpVel1 += s_fGravity * timestep / 2;
	tmpVel2 += s_fGravity * timestep / 2;
	p1temp.vel = tmpVel1;
	p2temp.vel = tmpVel2;
	// Calculate new positions at t + h
	Vec3 newPos1, newPos2;
	newPos1 = p1.pos + timestep * p1temp.vel;
	newPos2 = p2.pos + timestep * p2temp.vel;
	// Calculate midpoint force and acceleration for the velocity at t + h
	//currentForce = updateForces(p1temp, p2temp);
	forces = computeForce();
	//currentAcceleration = updateAcceleration(currentForce);
	acceleration1 = updateAcceleration(forces[0]);
	acceleration2 = updateAcceleration(forces[1]);
	// Calculate velocity at t + h
	Vec3 newVel1, newVel2;
	//newVel1 = updateVelocity(p1, currentAcceleration, timestep);
	//newVel2 = updateVelocity(p2, -currentAcceleration, timestep);
	newVel1 = updateVelocity(p1, acceleration1, timestep);
	newVel2 = updateVelocity(p2, acceleration2, timestep);
	// Apply gravity
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
