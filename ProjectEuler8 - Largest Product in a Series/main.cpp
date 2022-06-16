// ProjectEuler8 - Largest Product in a Series.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
ORIGINAL PROBLEM

The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.

73167176531330624919225119674426574742355349194934
96983520312774506326239578318016984801869478851843
85861560789112949495459501737958331952853208805511
12540698747158523863050715693290963295227443043557
66896648950445244523161731856403098711121722383113
62229893423380308135336276614282806444486645238749
30358907296290491560440772390713810515859307960866
70172427121883998797908792274921901699720888093776
65727333001053367881220235421809751254540594752243
52584907711670556013604839586446706324415722155397
53697817977846174064955149290862569321978468622482
83972241375657056057490261407972968652414535100474
82166370484403199890008895243450658541227588666881
16427171479924442928230863465674813919123162824586
17866458359124566529476545682848912883142607690042
24219022671055626321111109370544217506941658960408
07198403850962455444362981230987879927244284909188
84580156166097919133875499200524063689912560717606
05886116467109405077541002256983155200055935729725
71636269561882670428252483600823257530420752963450

Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. 
What is the value of this product?
**/

/*
* my notes
* 
* O(n) processing time. (i.e. one loop, not a nested loop)
* 1000 digits (20*50)
* 
* Submit code with a picture of the output together in a pdf, or seperatley in a txt file.
* 
* 
* Overall parameters:
* numOfAdjacents - number of adjacent digits to calc (up to 13)
* givenNum - string or matrix up to 1000 digits
* givenNumSize - 
* 
* 1,000,000,000,000
* 1,000,000,000,000
* 
* numFromFile(filename) 
    - method to read .txt file and return a string of ints or matrix of ints
* findGreatestProduct(givenNum, numOfAdjacents) 
    - method to solve euler and returns value of product, and the index of the first adjacent int
*/

//int findGreatestProduct(string givenNum, int numOfAdjacents)
//{
//    int max = 0;
//    int product = 1;
//
//    for (int i = 0; i < numOfAdjacents; i++)
//    {
//        string current(1, givenNum[i]);
//        product = product * stoi(current);
//    }
//    
//    max = product;
//
//    for (int i = numOfAdjacents; i < givenNum.length(); i++)
//    {
//        string current(1, givenNum[i]);
//        string first(1, givenNum[i - numOfAdjacents]);
//
//        if (stoi(first) != 0)
//        {
//            product = (product / (stoi(first) * pow(10, numOfAdjacents - 1))) * stoi(current);
//
//            if (product > max) { max = product; }
//        }
//        else 
//        {
//            product = product * stoi(current);
//        }
//    }
//
//    return max;
//}

int findGreatestProduct(string givenNum, int numOfAdjacents)
{
    int max = 0;
    int numOfDigitsInQueue = 0;
    int product = 1;

    for (int i = 0; i < givenNum.length(); i++)
    {
        //start with index i as the next digit to be mult
        string next(1, givenNum[i]);
        
        if (numOfDigitsInQueue != numOfAdjacents) {
            string current(1, givenNum[i]);

            product = product * stoi(current);
            if (product > max) { max = product; }
            numOfDigitsInQueue++;
        }
        else if (stoi(next) != 0) {
            string lastDigit(1, givenNum[i - 1]);
            string firstDigit(1, givenNum[i - numOfAdjacents]);

            product = stoi(next) * (product / (stoi(firstDigit) * pow(10, numOfAdjacents - 1)));
            if (product > max) { max = product; }
        }
        else { //if stoi(next) = 0
            numOfDigitsInQueue = 0;
            product = 1;
        }
    }

    return max;
}

string NumFromFile(string filename)
{
    std::fstream myFile;
    myFile.open(filename);

    std::string outputInt = "";

    std::string fileLine;
    while (getline(myFile, fileLine))
    {
        outputInt = outputInt + fileLine;
    }

    return outputInt;
}

int main() 
{
    bool programRunning = true;
    int choice;

    std::cout << "WELCOME TO MY SOLUTION TO PROJECT EULER PROBLEM #8!" << std::endl;
    
    //MAIN MENU
    while (programRunning)
    {
        std::cout << "\n_________________________________________________________________________________" << std::endl;
        std::cout << "Problem details...\n" << std::endl;

        std::cout << "Within the given number, find the adjacent digits that have the greatest product." << std::endl;
        std::cout << "The output should include the adjacent digits, and the value of the product." << std::endl;
        std::cout << "The given number can vary in length up to 1000 digits," << std::endl;
        std::cout << "and the amount of calculated adjacent digits can vary up to 13 digits." << std::endl;
        std::cout << "Do this in C++ or Java with a O(n) processing time.\n" << std::endl;

        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "ACTIONS MENU\n" << std::endl;

        std::cout << "\t1) Original parameters  : Given original 1000 digits, find greatest product of 13 adjacent." << std::endl;
        std::cout << "\t2) Custom parameters    : Randomly generate x digits, find greatest product of x adjacent digits." << std::endl;
        std::cout << "\t3) Filed parameters     : Get digits from file, find greatest product of x adjacent digits." << std::endl;
        std::cout << "\t0) Exit Program!" << std::endl;

        std::cout << "\nPlease enter a number to select an option...";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
        {
            std::cout << "\nEnding program ... Goodbye!" << std::endl;
            programRunning = false;

            break;
        }
        case 1:
        {
            //Run with original parameters : Given original 1000 digits, find greatest product of 13 adjacent.
                       
            //run numFromFile to find the original given number
            //run findGreatestProduct on the numFromFile and 13 adjacents
            
            //write file
            string numFromFile = NumFromFile("original.txt");

            std::cout << numFromFile << "\n\n" << findGreatestProduct(numFromFile, 13);

            break;
        }
        case 2:
        {
            //Custom parameters : Randomly generate x digits, find greatest product of x adjacent digits

            //ask for givenNumSize, generate givenNum
            //ask for numOfAdjacents

            //run findGreatestProduct on givenNum and numOfAdjacents
            
            //write file

            break;
        }
        case 3:
        {
            //Filed parameters : Get digits from file, find greatest product of x adjacent digits.

            

            //ask for filename
            //ask for numOfAdjacents

            //run findGreatestProduct on numFromFile(filename) and numOfAdjacents


            break;
        }
        default:
        {
            std::cout << "\nPlease try again." << std::endl;

            break;
        }
        }
    }
    exit(0);
}

