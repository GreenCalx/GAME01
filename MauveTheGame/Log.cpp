#include "Log.h"



Log::Log() : _FILENAME_("Log.txt"), timeStampEnable(true)
{
	timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
	_FILE_.open(_FILENAME_);
	_FILE_.clear();
	_FILE_.close();
}

Log::Log(const char* fileName) : _FILENAME_(fileName), timeStampEnable(true)
{
	timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
	_FILE_.open(_FILENAME_);
	_FILE_.clear();
	_FILE_.close();
}

Log::Log(const char* fileName, bool timeStampEnabler) : _FILENAME_(fileName), timeStampEnable(timeStampEnabler)
{
	timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
	_FILE_.open(_FILENAME_);
	_FILE_.clear();
	_FILE_.close();
}

Log::~Log()
{
	if ( _FILE_.is_open() ) _FILE_.close();
}


int Log::logInt(const int value, const char* attributeName ) {
	if (!_FILE_.is_open()) {
		timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
		_FILE_.open(_FILENAME_, std::ios::app);
		if (!_FILE_.is_open()) return -1;
		_FILE_ << timeStamp.count();
		_FILE_ << "  |  ";
		_FILE_ << attributeName;
		_FILE_ << " : ";
		_FILE_ << value;
		_FILE_ << '\n';

		_FILE_.close();
	}
	return 1; // Success
}

int Log::logString(const char* str) {

	if (!_FILE_.is_open()) {
		timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
		_FILE_.open(_FILENAME_, std::ios::app);
		if (!_FILE_.is_open()) return -1;
		_FILE_ << timeStamp.count();
		_FILE_ << "  |  ";
		_FILE_ << str;
		_FILE_ << '\n';

		_FILE_.close();
	}
	return 1; // Success
}

int Log::logActor(Actor &actor) {
	

	if (!_FILE_.is_open()) {
		timeStamp = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
		_FILE_.open(_FILENAME_, std::ios::app);
		if (!_FILE_.is_open()) return -1;

		_FILE_ << timeStamp.count();
		_FILE_ << "  |  ";
		if ( NULL==&actor )
			_FILE_ << " OBJECT HAS BEEN DELETED." << '\n';
		else {
			
			_FILE_ << actor.getNAME();
			_FILE_ << "::";
			_FILE_ << actor.getID();
			_FILE_ << "  -  ";
			_FILE_ << actor.toString();

			_FILE_ << '\n';
		}
		_FILE_.close();
	}
	return 1; // Success
}