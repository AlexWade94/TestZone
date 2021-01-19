#include "MyFrameWork.h"
#include <stdlib.h> 
#include <regex>
#include <Windows.h>

std::vector<std::string> splitreg(const std::string& input, const std::regex regex) {
	// passing -1 as the submatch index parameter performs splitting
	std::sregex_token_iterator
		first{ input.begin(), input.end(), regex, -1 },
		last;
	return { first, last };
}

int main(int argc, char* argv[])
{
#ifdef NDEBUG
	FreeConsole();
#endif // DEBUG

	int SCREEN_WIDTH  = 0;
	int SCREEN_HEIGHT = 0;
	int MAP_WIDTH     = 0;
	int MAP_HEIGHT    = 0;
	int NUM_ENEMIES   = 0;
	int NUM_AMMO      = 0;
	
	std::vector <std::string> size;
	
	std::regex match   ("(\\d+)x(\\d+)");
	std::regex regular ("(\\D)");

	for (int i = 1; i < argc; i++)
	{
		
		if ((std::string)argv[i] == "-window")
		{
			//if param match regex, proceed
			if (std::regex_match((std::string)argv[i+1], match))
			{
				//split param into 2 strings and cat it to int
				size = splitreg(argv[i+1], regular);
				SCREEN_WIDTH = std::atoi(size[0].c_str());
				SCREEN_HEIGHT = std::atoi(size[1].c_str());
			}
			else
			{
				std::cout << "Window size: invalid format\n";
				SCREEN_WIDTH = 840;
				SCREEN_HEIGHT = 480;
			}

		}
		if((std::string)argv[i] == "-map")
		{
			//if param match regex, proceed
			if (std::regex_match((std::string)argv[i+1], match))
			{
				//split param into 2 strings and cat it to int
				size = splitreg(argv[i+1], regular);
				MAP_WIDTH = std::atoi(size[0].c_str());
				MAP_HEIGHT = std::atoi(size[1].c_str());
			}
			else
			{
				std::cout << "Map size: invalid format\n";
				MAP_WIDTH = 1240;
				MAP_HEIGHT = 720;
			}
			}

		if ((std::string)argv[i] == "-num_enemies")
		{
			NUM_ENEMIES = std::stoi(argv[i+1]);
		}
		if ((std::string)argv[i] == "-num_ammo")
		{
			NUM_AMMO = std::stoi(argv[i+1]);
		}

	}

	MyFramework frame(SCREEN_WIDTH, SCREEN_HEIGHT, MAP_WIDTH, MAP_HEIGHT, NUM_ENEMIES, NUM_AMMO);
	run(&frame);
	
	return 0;

}
