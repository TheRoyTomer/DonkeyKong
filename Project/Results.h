#pragma once
#include <string>
#include <vector>
class Results
{
public:
	enum ResultStates { Strike = 0, Finished, NoResult };
private:
	std::vector<std::pair<size_t, ResultStates>> res; // pair: iteration, res
	int score = 0;
public:
	//Prototypes
	//Load results vector and score from designated file.
	static Results loadResults(const std::string& filename);
	//Save data from results vector to designated file.
	void saveResults(const std::string& filename) const;
	//Function that checks if we didn't passed next strike event from result file. And if so, return false.
    //Also, it will return false if next event is finishing event, means that there isn't any strike events left.
	bool IsPassedNextStrikeIteration(int iteration) const;

	//Add new result to vector.
	void addResult(size_t iteration, ResultStates result)
	{
		res.push_back({ iteration, result });
	}

	//Pop first element in vector and return this element.
	std::pair<size_t, ResultStates> popResult()
	{
		if (res.empty())
		{
			return { 0, Results::NoResult };
		}
		auto result = res.front();
		res.erase(res.begin());
		return result;
	}

	//Compare if finished element iteration is the same as the parameter.
	bool CompareFinishIterations(size_t iteration) const
	{
		return !res.empty() && res.back().second == Finished && res.back().first == iteration;
	}

	//Checks if the iteration parameter we got is greater then the iteration in the finish element in vector.
	bool isFinishedBy(size_t iteration) const
	{
		return res.empty() || res.back().first < iteration;
	}

	int getScore() const
	{
		return score;
	}
	void setScore(int _score)
	{
		score = _score;
	}

	bool isLastEventIsFinished()
	{
		bool temp1 = !res.empty();
		bool temp2 = res.back().second == Finished;
		return (!res.empty() && res.back().second == Finished);
	}
};

