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
	minPriority = 0;


	file.open(fileName);
	file << "[START]:\t\tProgram started!" << std::endl;
	file << "[PRIORITY]:\t\tMinimum priority set to 0!" << std::endl;
}

bool DebugLogManager::Log(int _priority, std::string _message)
{
	std::string		finalMessage = "";

	//Ensure file is open
	if (file.is_open())
	{
		//Format log message
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

		//Check if the message's priority is high enough to be logged
		if (_priority >= minPriority)
		{
			if (file << finalMessage)
				return true;
		}		
	}
	return false;
}

void DebugLogManager::SetPriority(int _newPriority)
{
	minPriority = _newPriority;
	if (file.is_open())
	{
		file << "[PRIORITY]:\t\tMinimum priority has been updated to " << _newPriority << "!" << std::endl;
	}
}

int DebugLogManager::GetPriority()
{
	return minPriority;
}
