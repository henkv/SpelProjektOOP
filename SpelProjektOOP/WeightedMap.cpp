#include "WeightedMap.h"

#include <sstream>


WeightedMap::WeightedMap(int width, int height)
{
	this->width = width;
	this->height = height;

	map = new float*[width];
	for (int x = 0, y; x < width; x++)
	{
		map[x] = new float[height];

		for (y = 0; y < height; y++)
		{
			map[x][y] = 0.0f;
		}
	}
}


WeightedMap::~WeightedMap()
{}




void WeightedMap::getCenterOfMass(float& x, float& y) const
{
	float totalMass  = 0.0f;
	float totalXMass = 0.0f;
	float totalYMass = 0.0f;

	for (int y = 0, x; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			totalMass  += (map[x][y]);
			totalXMass += (map[x][y]) * x;
			totalYMass += (map[x][y]) * y;
		}
	}

	x = (totalXMass / totalMass) - 0;
	y = (totalYMass / totalMass) - 0;
}


void WeightedMap::addMass(float mass, int x, int y)
{
	map[x][y] += mass;
}



string WeightedMap::toString() const
{
	stringstream stream;

	for (int y = 0, x; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			stream << (map[x][y] == 0.0f ? "." : "X");
		}

		stream << endl;
	}

	return stream.str();
}

