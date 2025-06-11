#include "Steps.h"
#include <fstream>

//Load steps vector and random seed from designated file.
Steps Steps::loadSteps(const std::string& filename) 
{
	Steps steps;
	std::ifstream steps_file(filename);
	steps_file >> steps.randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		std::string step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

//Save data from steps vector to  designated file.
void Steps::saveSteps(const std::string& filename) const
{
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}

//Pop first element in vector and return the string in this element.
std::string Steps::popStep()
{
	if (!steps.empty())
	{
		std::string step = steps.front().second;
		steps.erase(steps.begin());
		return step;
	}
	else
	{
		return "";
	}
}