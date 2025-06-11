#include "Results.h"
#include <fstream>
#include <limits>

//Load results vector and score from designated file.
Results Results::loadResults(const std::string& filename)
{
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0)
	{
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultStates>(result));
	}
	if (!results_file.eof())
	{
		results_file >> results.score;
	}
	results_file.close();
	return results;
}

//Save data from results vector to designated file.
void Results::saveResults(const std::string& filename) const
{
	std::ofstream results_file(filename);
	results_file << res.size();
	for (const auto& result : res) 
	{
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file << '\n' << score;
	results_file.close();
}

//Function that checks if we didn't passed next strike event from result file. And if so, return false.
//Also, it will return false if next event is finishing event, means that there isn't any strike events left.
bool Results::IsPassedNextStrikeIteration(int iteration) const
{
	if (!res.empty() && ((res.front().second == Strike && iteration <= res.front().first) || (res.front().second == Finished)))
	{
		return false;
	}
	return true;
}
