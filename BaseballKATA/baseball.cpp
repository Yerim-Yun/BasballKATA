#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question){ }

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return (guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2]);
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9')  continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	bool isMatchedChar(char a, char b) {
		return (a == b);
	}

	

	GuessResult guess(const string& guessNumber)
	{
		int qIdx, gIdx;
		GuessResult res;

		res.solved = false;
		res.strikes = 0;
		res.balls = 0;

		assertIllegalArgument(guessNumber);

		for (qIdx = 0; qIdx < 3; qIdx++) {
			for (gIdx = 0; gIdx < 3; gIdx++) {
				if (!isMatchedChar(question[qIdx], guessNumber[gIdx])) continue;
				if (qIdx == gIdx)
					res.strikes++;
				else
					res.balls++;
			}
		}

		if (res.strikes == 3)
			res.solved = true;

		return res;
	}

private:
	string question;
};