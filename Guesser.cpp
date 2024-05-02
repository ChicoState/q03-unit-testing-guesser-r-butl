#include "Guesser.h"
#include <string>
#include <algorithm>

using std::string;

/*
  Returns a whole number representing the distance between the guess,
  provided as an argument, and the secret. 
  
  The distance represents the number of characters that would have to be changed at the same location to match the other string.
  
  When the two strings are identical, the distance is 0,

  but for each letter different, the distance increases by 1. 
  
  When the strings are different lengths, each of the extra characters in the longer string also counts as an increase in 1 to the distance, up to the length of the secret; in other words, if m_secret has a 10 characters and the guess has 100, the distance is 10.
*/
unsigned int Guesser::distance(string guess){

  string secret = m_secret;

  // input: ""
  // secret: "1ljkdf"
  // increase difference up to the length of the secret
  if( guess.length() == 0){
    return secret.length();
  }

  // Determine which string is shorter
  string* shorter = secret.length() > guess.length() ? &guess : &secret;
  string* longer = secret.length() > guess.length() ? &secret : &guess;

  // Count the differences
  int change_count = 0;
  int i = 0;
  while ( i < shorter->length()){

    if (secret[i] != guess[i]){
      change_count++;
    }
    i++;
  }

  // If there is a difference in length, add the difference up to the length of the secret
  int difference_length = longer->length() - shorter->length();

  change_count += difference_length;

  return change_count > secret.length() ? secret.length() : change_count;
}

unsigned int Guesser::call_distance(string guess){
  return distance(guess);
}

/*
  Constructor requires that the secret phrase is provided its value as
  an argument. This secret will not change for the lifespan of an instance
  of any Guesser object and must have a length of 32 characters or less,
  otherwise, it will be truncated at that length.
*/
Guesser::Guesser(string secret){

  int size = secret.length() > 32 ? 32 : secret.length();
  m_secret = secret.substr(0, size);
  m_remaining = 3; // start with 3 guesses

}

/*
  Determines and returns whether the provided guess matches the secret
  phrase. However, the function also returns false if the secret is locked,
  which happens if either (or both): 
    (A) there are no remaining guesses allowed
    (B) the function detects brute force, as indicated by a guess that has a
        distance greater than 2 from the secret
  See the remaining() and distance() functions for specifications regarding
  determining how many guesses are remaining and the distance between a guess
  and the secret.
*/
bool Guesser::match(string guess){

  int d = distance(guess);

  if(m_remaining == 0 || d > 2){  // No guesses left or brute force
    m_remaining = 0;  // Set this to 0 in the case that d > 2
    return false;

  }else  if (d == 0) { // Match
    m_remaining = 3;
    return true;

  }else{    // Decrement remaining

    m_remaining--;
    return false;

  }
}

/*
  Returns the number of guesses remaining. A Guesser object allows up to
  three (3) consecutive guesses without a match. If three guesses are made
  without any being a true match, the secret is locked. However, whenever
  an unlocked secret is guessed with a true match, the guesses remaining
  reset to three (3).
*/
unsigned int Guesser::remaining(){

  return m_remaining;
}

