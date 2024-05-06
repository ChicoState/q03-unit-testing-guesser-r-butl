/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

///////////////////////////////////////// distance test

TEST(GuesserTest, secret_over_32){
	Guesser guesser("qqqqqwwwwweeeeerrrrrtttttyyyyyuuuuu");
	int length = guesser.distance("qqqqqwwwwweeeeerrrrrtttttyyyyyuu");

	ASSERT_EQ( 0, length);
}

TEST(GuesserTest, equal_length_same_string)
{
	Guesser guesser("string");
	int length = guesser.distance("string");

	ASSERT_EQ( 0, length);
}

TEST(GuesserTest, empty_secret)
{
	Guesser guesser("");
	int length = guesser.distance("string");

	ASSERT_EQ( 0, length);
}

TEST(GuesserTest, empty_guess)
{
	Guesser guesser("string");
	int length = guesser.distance("");

	ASSERT_EQ( 6, length);
}

TEST(GuesserTest, equal_length_different_string)
{
	Guesser guesser("string");
	int distance = guesser.distance("secret");

	ASSERT_EQ( 5 , distance);
}

TEST(GuesserTest, longer_guess_correct_string)
{
	Guesser guesser("string");
	int distance = guesser.distance("stringkkd");

	ASSERT_EQ( 3 , distance);
}

TEST(GuesserTest, longer_secret_correct_string)
{
	Guesser guesser("stringlkj");
	int distance = guesser.distance("string");

	ASSERT_EQ( 3 , distance);
}

TEST(GuesserTest, longer_guess_correct_string_passed_secret_length)
{
	Guesser guesser("string");
	int distance = guesser.distance("stringstringlkjs");

	ASSERT_EQ( 6, distance);
}

////////////////////////////////////	Test remaining

TEST(GuesserTest, remaining_test)
{		// we really only need to test the constructor, the Match Test test suite will do more thorough checks
	Guesser guesser("string");
	int remaining = guesser.remaining();

	ASSERT_EQ( remaining, 3);
}

////////////////////////////////////	Match Test

TEST(GuesserTest, match_first_try){

	Guesser guesser("string");

	bool match = guesser.match("string");
	ASSERT_EQ(match, true);

	int remaining = guesser.remaining();
	ASSERT_EQ(remaining, 3);
}

TEST(GuesserTest, match_second_try){

	Guesser guesser("string");

	bool match = guesser.match("strin");
	ASSERT_EQ(match, false);

	int remaining = guesser.remaining();
	ASSERT_EQ(remaining, 2);

	match = guesser.match("string");
	ASSERT_EQ(match, true);

	remaining = guesser.remaining();
	ASSERT_EQ(remaining, 3);
}

TEST(GuesserTest, match_third_try){

	Guesser guesser("string");

	bool match = guesser.match("strin");
	ASSERT_EQ(match, false);

	int remaining = guesser.remaining();
	ASSERT_EQ(remaining, 2);

	match = guesser.match("strin");
	ASSERT_EQ(match, false);

	remaining = guesser.remaining();
	ASSERT_EQ(remaining, 1);

	match = guesser.match("string");
	ASSERT_EQ(match, true);

	remaining = guesser.remaining();
	ASSERT_EQ(remaining, 3);
}

TEST(GuesserTest, no_matches){

	Guesser guesser("string");

	bool match = guesser.match("strin");
	ASSERT_EQ(match, false);

	int remaining = guesser.remaining();
	ASSERT_EQ(remaining, 2);

	match = guesser.match("strin");
	ASSERT_EQ(match, false);

	remaining = guesser.remaining();
	ASSERT_EQ(remaining, 1);

	match = guesser.match("strin");
	ASSERT_EQ(match, false);

	remaining = guesser.remaining();
	ASSERT_EQ(remaining, 0);

	// Try to run again with the correct string
	match = guesser.match("string");
	ASSERT_EQ(match, false);
}

TEST(GuesserTest, check_brute_force){

	Guesser guesser("string");
	
	bool match = guesser.match("stringgggg");

	int remaining = guesser.remaining();
	ASSERT_EQ(remaining, 0);
}