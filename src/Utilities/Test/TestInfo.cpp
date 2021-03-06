/**
 * @file TestInfo.cpp
 * @date Oct 2, 2018
 * @author Mirco Theile, mirco.theile@tum.de
 * @brief
 */
#include <cpsCore/Logging/CPSLogger.h>
#include "cpsCore/Utilities/Test/TestInfo.h"

void
TestInfo::initialize(int argc, char** argv)
{
	char cwd[1024];
	if (!getcwd(cwd, sizeof(cwd)))
	{
		CPSLOG_ERROR << "Cannot determine cwd";
	}

	std::string str(argv[0]);

	std::size_t found = str.rfind('.');
	if (found == std::string::npos)
	{
		found = str.rfind('/');
		testDir = str.substr(0, found) + "/";
		return;
	}

	found = str.rfind('/');
	if (found == std::string::npos)
		testDir = cwd;
	else
		testDir = std::string(cwd) + "/" + str.substr(0, found) + "/";
}

namespace test_info
{
std::string
test_dir()
{
	return TestInfo::getInstance().testDir;
}
}



