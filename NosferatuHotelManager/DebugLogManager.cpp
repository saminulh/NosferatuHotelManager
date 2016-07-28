#include "stdafx.h"
#include "DebugLogManager.h"

DebugLogManager::DebugLogManager()
{
}

DebugLogManager::~DebugLogManager()
{
	if (file.is_open())
	{
		file << "[END]:\t\t\tProgram terminated successfully!" << std::endl;
		file.close();
	}
}

bool DebugLogManager::ClearLogFile()
{
	file.open(fileName);
	file.clear();
	return true;
}

void DebugLogManager::Start()
{
	fileName = "debug.log";

	file.open(fileName);
	file << "[START]:\t\tProgram started!" << std::endl;
}

bool DebugLogManager::Log(int _priority, std::string _message)
{
	std::string finalMessage = "";

	if (file.is_open())
	{
		switch (_priority)
		{
		case 0:
		{
			finalMessage += "[INFO]:\t\t\t";
			finalMessage += _message;
			finalMessage += "\n";
			break;
		}
		case 1:
		{
			finalMessage += "[NOTE]:\t\t\t";
			finalMessage += _message;
			finalMessage += "\n";
			break;
		}
		case 2:
		{
			finalMessage += "[WARNING]:\t\t";
			finalMessage += _message;
			finalMessage += "\n";
			break;
		}
		case 3:
		{
			finalMessage += "[ERROR]:\t\t";
			finalMessage += _message;
			finalMessage += "\n";
			break;
		}
		default:
		{
			finalMessage += "[UNHANDLED SEVERITY]:\t";
			finalMessage += _message;
			finalMessage += "\n";
			break;
		}
		}


		if (file << finalMessage)
			return true;
	}
	return false;
}
