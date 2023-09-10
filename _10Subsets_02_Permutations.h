#include <vector>
#include <string>
#include <iostream>

namespace EducativeGrokkingCodingPatterns
{
	class _10Subsets_02_Permutations
	{
		/*
		* 
		*	Statement
            Given an input string, return all possible permutations of the string.

            Note: The order of permutations does not matter. 
            All characters in the input string are unique.

            1 ≤ word.length ≤ 6


			This algorithm for permutations will apply a top down approach and then a bottom up approach
			First it keeps removing a letter when it does a substring and it keeps doing that until there is only
			1 character left, then it reaches the base case and returns the single character.
			
			PermuteWord(abcd)
			                    a + PermuteWord(bcd)
									b + PermuteWord(cd)
							              c + PermuteWord(d) -> now it returns d and it creates cd in the for loop
										  d + PermuteWord(c) -> now it returns c and it creates dc in the for loop					    

			Lets look at this for loop			
			char c = word[i];				
			std::string smaller = word.substr(0, i) + word.substr(i + 1);
			So everytime through the for loop when it runs the first time, word.substr(0, i) it return an empty string	
			Example for the loop
			
			//word = abcd
			char c = word[i];	i = 0, c = 'a'
			word.substr(0, i) + word.substr(i + 1); = "" + "bcd"	-> PermuteWord("bcd")

			//word = bcd
			char c = word[i];	i = 0, c = 'b'
			word.substr(0, i) + word.substr(i + 1); = "" + "cd"		-> PermuteWord("cd")

			//word = cd
			char c = word[i];	i = 0, c = 'c'
			word.substr(0, i) + word.substr(i + 1); = "" + "d"		-> PermuteWord("d") and returns {"d"}
			permutations.push_back(c + permut); // cd
			char c = word[i];	i = 1, c = 'd'
			word.substr(0, i) + word.substr(i + 1); = "c" + ""		-> PermuteWord("c") and returns {"c"}
			permutations.push_back(c + permut); // dc
			returns permutations = {"cd", "dc"}

			//Since we return we pop the stack and return to this state
			//word = bcd
			char c = word[i];	i = 0, c = 'b'
			word.substr(0, i) + word.substr(i + 1); = "" + "cd"		-> PermuteWord("cd") and returns {"cd", "dc"}
			permutations.push_back(c + permut); // bcd
			permutations.push_back(c + permut); // bdc

			char c = word[i];	i = 1, c = 'c'
			word.substr(0, i) + word.substr(i + 1); = "b" + "d"		-> PermuteWord("bd") and returns {"bd","db"}
			permutations.push_back(c + permut); // cbd
			permutations.push_back(c + permut); // cdb

			char c = word[i];	i = 2, c = 'd'
			word.substr(0, i) + word.substr(i + 1); = "bc" + ""		-> PermuteWord("bc") and returns {"bc","cb"}
			permutations.push_back(c + permut); // dbc
			permutations.push_back(c + permut); // dcb

			return {bcd,bdc,cbd,cdb,dbc,dcb}

			//Since we return we pop the stack and return to this state
			//word = abcd
			char c = word[i];	i = 0, c = 'a'
			word.substr(0, i) + word.substr(i + 1); = "" + "bcd"	-> PermuteWord("bcd") -> return  {"bcd","bdc","cbd","cdb","dbc","dcb"}
			permutations.push_back(c + permut); // abcd
			permutations.push_back(c + permut); // abdc
			permutations.push_back(c + permut); // acbd
			permutations.push_back(c + permut); // acdb
			permutations.push_back(c + permut); // adbc
			permutations.push_back(c + permut); // adcb

			char c = word[i];	i = 1, c = 'b'
			word.substr(0, i) + word.substr(i + 1); = "a" + "cd"	-> PermuteWord("acd") -> return  {"acd","adc","cad","cda","dac","dca"}
			permutations.push_back(c + permut); // bacd
			permutations.push_back(c + permut); // badc
			permutations.push_back(c + permut); // bcad
			permutations.push_back(c + permut); // bcda
			permutations.push_back(c + permut); // bdac
			permutations.push_back(c + permut); // bdca

			char c = word[i];	i = 2, c = 'c'
			word.substr(0, i) + word.substr(i + 1); = "ab" + "d"	-> PermuteWord("abd") -> return  {"abd","adb","bad","bda","dab","dba"}
			permutations.push_back(c + permut); // cabd
			permutations.push_back(c + permut); // cadb
			permutations.push_back(c + permut); // cbad
			permutations.push_back(c + permut); // cbda
			permutations.push_back(c + permut); // cdab
			permutations.push_back(c + permut); // cdba

			//skipped last element, you get the idea
		*/

		/* A recursive function that generates all permutation of the word */
		static std::vector<std::string> PermuteWord(const std::string& word)
		{
			if (word.size() == 1)
				return std::vector<std::string>{word};

			std::vector<std::string> permutations;

			for (int i = 0; i < word.size(); ++i)
			{
				char c = word[i];
				std::string smaller = word.substr(0, i) + word.substr(i + 1);
				std::vector<std::string> permuted = PermuteWord(smaller);
				for (std::string permut : permuted)
					permutations.push_back(c + permut);
			}
			return permutations;
		}

	public:
		static void Compute()
		{
			std::vector<std::string> inputWords = { "ab", "abc", "abcd" };

			for (int index = 0; index < inputWords.size(); ++index)
			{
				std::vector<std::string> permutedWords = PermuteWord(inputWords[index]);
				std::cout << (index + 1) << ".\t Input string'" << inputWords[index] << "'" << std::endl;
				std::cout << "\t All possible permutations are: " << std::endl;
				for (const auto& permutedWord : permutedWords)
				{
					std::cout << permutedWord << ", ";
				}
				std::cout << std::endl << std::string(100, '-') << std::endl;
			}

		}
	};
}