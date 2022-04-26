#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

struct image;
struct groupOfImages;
enum ORIENTATION
{
	NORTH_OR,
	EAST_OR,
	SOUTH_OR,
	WEST_OR
};

struct image
{
	bool image[10][10];
	int orientation;
	int i_borders[4];

};

struct groupOfImages
{
	std::unordered_map<int, image> um_i_images;
};
