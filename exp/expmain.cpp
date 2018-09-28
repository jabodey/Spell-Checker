#include <string>
#include "BSTSet.hpp"
#include "HashSet.hpp"
#include <iostream>
using namespace std;

/*
    namespace
        {
                template <typename T>
                            unsigned int zeroHash(const T& t)
                                            {
                                                                    return 0;
                                                                                                }
                                                                                                                            }

*/
// expmain.cpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.


int main()
{
/*
   {
       HashSet<int> s1{zeroHash<int>};
           Set<int>& ss1 = s1;
               int sz1 = ss1.size();
                   sz1 = 0;

                       HashSet<std::string> s2{zeroHash<std::string>};
                           Set<std::string>& ss2 = s2;
                               int sz2 = ss2.size();
                                   sz2 = 0;
                                   }



    BSTSet<int> s1;
    //Set<int>& ss1 = s1;
    //int sz1 = ss1.size();
    //sz1 =
    0;
    

    
    BSTSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
    */
    /*
    string bob = "Bob";
    string carl = "Carl";
    string bob2 = "Bob";
    cout << (bob > carl) << endl;;
    cout << bob.compare(carl) << endl;
    if (bob > carl)
        cout << "BOB IS GREATER THAN CARL" << endl;
    if (bob < carl)
        cout << "BOB IS LESS THAN CARL" << endl;
    if (bob == bob2)
        cout << "BOB IS EQUAL TO BOB2" << endl;
    */
    BSTSet<std::string> s2;
    BSTSet<std::string> s1;
    bool b2 = s2.contains("Boo");
    
    s2.add("Boo");
    s2.add("Blah");
    s2.add("Bleh");
    s1.add("Boo");
    s2.contains("Boo");
    cout << s2.contains("Boo") << endl;
    cout << b2 << endl;
    return 0;
}

