#pragma once
#include <stdio.h>
#include <fstream>
#include <chrono>

#include "Actor.h"

using namespace std::chrono;

class Log
{

public:
	Log();
	Log(const char* fileName);
	Log(const char* fileName, bool timeStampEnabler);
	~Log();

public:
	int logInt		(const int value, const char* attributeName = "");
	int logString	(const char* str);
	int logActor	(Actor &actor);


private:
	std::ofstream				_FILE_			;
	const char*					_FILENAME_		;
	std::chrono::milliseconds	timeStamp		;
	bool						timeStampEnable	;
};

