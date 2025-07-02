#include "gmock/gmock.h"
#include "baseball.cpp"

using namespace testing;

class BaseballFixture : public testing::Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(guessNumber);
			FAIL();
		}
		catch (exception e) {
			//PASS
		}
	}
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber)
{
	GuessResult result = game.guess("123");
	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnResultIf2S0B)
{
	GuessResult result = game.guess("124");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(2, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnResultIf1S2B)
{
	GuessResult result = game.guess("321");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(2, result.balls);
}

TEST_F(BaseballFixture, ReturnResultIf1B)
{
	GuessResult result = game.guess("981");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(0, result.strikes);
	EXPECT_EQ(1, result.balls);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();

}