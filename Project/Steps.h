#pragma once
#include <vector>
#include <string>

class Steps
{
	long randomSeed = 0;
	std::vector<std::pair<size_t, std::string>> steps; // pair: iteration, step
public:
	//Prototypes
	//Load steps vector and random seed from designated file.
	static Steps loadSteps(const std::string& filename);
    //Save data from steps vector to designated file.
	void saveSteps(const std::string& filename) const;
	//Pop first element in vector and return the string in this element.
	std::string popStep();

	long getRandomSeed() const
	{
		return randomSeed;
	}
	void setRandomSeed(long seed)
	{
		randomSeed = seed;
	}

	//Add new step to vector.
	void addStep(size_t iteration, std::string step)
	{
		steps.push_back({ iteration, step });
	}
	//Check if next iteration have input in file.
	bool isNextStepOnIteration(size_t iteration) const
	{
		return !steps.empty() && steps.front().first == iteration;
	}
};

