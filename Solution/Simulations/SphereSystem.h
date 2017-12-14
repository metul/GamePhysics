#include <vector>
#include "util\vectorbase.h"
#include <iostream>
using namespace GamePhysics;
using std::cout;

class SphereSystem {
public:
	struct Point {
		Vec3 pos;
		Vec3 vel;
	};
	void AddPoint(Vec3 p, Vec3 v);
	float compute_repulsionForce(float d); //compute repulsion force with distance d, radius r, scalingFactor(lambda) s
	float compute_distance(Point p1,Point p2); //distance between to points
	float vec_to_length(Vec3 v); //Vec3 length
	void naive(float timestep); //collisiondetection 
	std::vector<Vec3> updateForces(Point p1, Point p2); //caluclate forces depending on gravity and repulsion force
	Vec3 updateAcceleration(Vec3 force); //calculate new acceleration depending on mass and forces
	Vec3 updateVelocity(Point point, Vec3 acceleration, float timestep); //caluclate new velocity depending on acceleration and old velocity
	void MidPoint(int i, int j, float timestep);
	void BoundingBoxCheck(float times = 1.0f);

	void setScalingFactor(float s) { scalingFactor = s; }
	void setDamping(float d) { s_damping = d; }
	void setMass(float m) { s_mass = m; }
	void setRadius(float r) { s_radius = r; }
	void setGravity(Vec3 g) { s_fGravity = g; }
	float getScalingFactor() { return scalingFactor; }
	float getDamping() { return s_damping; }
	float getMass() { return s_mass; }
	float getRadius() { return s_radius; }
	Vec3 getGravity() { return s_fGravity; }

	Vec3 getPosition(int i) { return s_points[i].pos; }


private:
	std::vector<Point>  s_points;
	float scalingFactor;
	float s_damping;
	float s_mass;
	float s_radius;
	Vec3 s_fGravity;
};