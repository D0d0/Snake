#pragma once
#include <stdio.h>
#include <vector>
#include "glew.h"
using namespace std;

class worldObject
{
public:
	worldObject();
	void loadFromFile(const char* path);
	~worldObject();
};