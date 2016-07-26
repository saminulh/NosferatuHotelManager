#include "stdafx.h"
#include "DebugLogManager.h"

DebugLogManager::DebugLogManager()
{
	fileName = "debug.log";

	file.open(fileName);
	file << "[START] - Program started!" << std::endl;
}

DebugLogManager::~DebugLogManager()
{
	if (file.is_open())
	{
		file << "[END] - Program terminated successfully!" << std::endl;
		file.close();
	}
}

bool DebugLogManager::ClearLogFile()
{
	file.open(fileName);
	file.clear();
	return true;
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
			finalMessage += "[INFO] - ";
			finalMessage += _message;
			break;
		}
		case 1:
		{
			finalMessage += "[NOTE] - ";
			finalMessage += _message;
			break;
		}
		case 2:
		{
			finalMessage += "[WARNING] - ";
			finalMessage += _message;
			break;
		}
		case 3:
		{
			finalMessage += "[ERROR] - ";
			finalMessage += _message;
			break;
		}
		default:
		{
			finalMessage += "[UNHANDLED SEVERITY] - ";
			finalMessage += _message;
			break;
		}
		}

		if (file << finalMessage)
			return true;
	}
	return false;
}
