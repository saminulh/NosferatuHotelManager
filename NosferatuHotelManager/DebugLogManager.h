#pragma once

//This singleton class is responsible for creating debug log files.

class DebugLogManager
{
	std::fstream	file;
	std::string		fileName;
public:
	DebugLogManager();
	~DebugLogManager();

	bool ClearLogFile();

	/*
	0 - Info
	1 - Note
	2 - Warning
	3 - Error
	*/
	bool Log(int _priority, std::string _message);
};