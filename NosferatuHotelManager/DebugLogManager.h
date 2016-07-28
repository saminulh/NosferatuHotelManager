#pragma once

//This singleton class is responsible for creating debug log files.

class DebugLogManager
{
	std::ofstream	file;
	std::string		fileName;
public:
	DebugLogManager();
	~DebugLogManager();

	bool ClearLogFile();
	void Start();

	/*
	0 - Info
	1 - Note
	2 - Warning
	3 - Error
	*/
	bool Log(int _priority, std::string _message);
};