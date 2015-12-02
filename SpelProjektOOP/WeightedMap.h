#pragma once
#include <string>
using namespace std;

class WeightedMap
{
	private:
	float** map;
	int width;
	int height;

	public:
	WeightedMap(int width, int height);
	virtual ~WeightedMap();

	void getCenterOfMass(float& x, float& y) const;
	void addMass(float mass, int x, int y);
		
	string toString() const;
};

