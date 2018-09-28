// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iostream>
#include <string>
#include <sstream>

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{

}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> suggestions;
    //swapping adjacent characters
    for(int i = 0; i < word.size(); ++i)
    {
    std::string temp = word;
    std::string temp2 = word;
    std::swap(temp[i], temp[i+1]);
    std::swap(temp2[i], temp2[i-1]);
    if (wordExists(temp))
        suggestions.push_back(temp);
    if (wordExists(temp2))
        suggestions.push_back(temp2);
    }
    
    //deleting a character
    for(int i = 0; i < word.size(); ++i)
    {
    std::string temp = word;
    temp.erase(i, 1);
    if (wordExists(temp))
        suggestions.push_back(temp);
    }
   
    //replacing each character with letter from a-z
    for(int i = 0; i < word.size(); ++i)
        for(int x = 0; x < letters.size(); ++x)
        {
        std::string temp = word;
        temp[i] = letters[x];
        if (wordExists(temp))
            suggestions.push_back(temp);

        }

     //adding letter from a-z between each adjacent pair of characters
     for(int i = 1; i < word.size(); ++i)
        for (int x = 0; x < letters.size(); ++x)
        {
        std::string temp = word;
        temp.insert(i, 1, letters[x]);
        if (wordExists(temp))
            suggestions.push_back(temp);
        }
     
     //splitting into pair of words by adding space between adjacent pair of characters
     for(int i = 1; i < word.size(); ++i)
        {
        std::string temp = word;
        std::string buf;
        temp.insert(i, " ");
        std::stringstream ss(temp);
        while (ss >> buf)
            if(wordExists(buf))
                suggestions.push_back(temp);
        }

    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(unique(suggestions.begin(), suggestions.end()), suggestions.end());
    //return std::vector<std::string>{};
    return suggestions;
}

