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

int* findGreatestProduct(string givenNum, int numOfAdjacents)
{
    int digitsInQueue = 0;
    int product = 1;

    int maxProduct = 0;
    int maxIndex = 0;
    int maxProductAndIndex[2];

    for (int i = 0; i < givenNum.length(); i++)
    {
        //start with index i as the next digit to be mult
        string next(1, givenNum[i]);
        
        if (digitsInQueue != numOfAdjacents) {
            product = product * stoi(next);
            if (product > maxProduct) { maxProduct = product; }

            digitsInQueue++;
        }
        else if (stoi(next) != 0) {
            string lastDigit(1, givenNum[i - 1]);
            string firstDigit(1, givenNum[i - numOfAdjacents]);
            
            if (stoi(firstDigit) == 0) { product = product * stoi(next); }
            else { product = (product / stoi(firstDigit)) * stoi(next); }
            
            if (product > maxProduct) 
            { 
                maxProduct = product; 
                //i need the index not the value of the first digit!!!!!
                maxIndex = i - numOfAdjacents;
            }
        }
        else { //if stoi(next) = 0
            digitsInQueue = 0;
            product = 1;
        }
    }

    maxProductAndIndex[0] = maxProduct;
    maxProductAndIndex[1] = maxIndex;
    
    return maxProductAndIndex;
}

string findMultipliers(string givenNum, int numOfAdjacents, int maxIndex)
{
    string multipliers = "";
    
    for (int i = maxIndex; i < maxIndex + numOfAdjacents; i++)
    {
        if (multipliers == "") { multipliers = givenNum[i]; }
        else { multipliers = multipliers + " x " + givenNum[i]; }
    }

    return multipliers;
}

string NumFromFile(string filename)
{
    fstream myFile;
    myFile.open(filename);

    string outputInt = "";

    string fileLine;
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

    cout << "WELCOME TO MY SOLUTION TO PROJECT EULER PROBLEM #8!" << endl;
    
    //MAIN MENU
    while (programRunning)
    {
        cout << "\n_________________________________________________________________________________" << endl;
        cout << "Problem details...\n" << endl;

        cout << "Within the given number, find the adjacent digits that have the greatest product." << endl;
        cout << "The output should include the adjacent digits, and the value of the product." << endl;
        cout << "The given number can vary in length up to 1000 digits," << endl;
        cout << "and the amount of calculated adjacent digits can vary up to 13 digits." << endl;
        cout << "Do this in C++ or Java with a O(n) processing time.\n" << endl;

        cout << "---------------------------------------------------" << endl;
        cout << "ACTIONS MENU\n" << endl;

        cout << "\t1) Original parameters  : Given original 1000 digits, find greatest product of 13 adjacent." << endl;
        //cout << "\t2) Custom parameters    : Randomly generate x digits, find greatest product of x adjacent digits." << endl;
        cout << "\t3) Filed parameters     : Get digits from file, find greatest product of x adjacent digits." << endl;
        cout << "\t0) Exit Program!" << endl;

        cout << "\nPlease enter a number to select an option...";
        cin >> choice;

        switch (choice)
        {
        case 0:
        {
            cout << "\nEnding program ... Goodbye!" << endl;
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
            int greatestProduct = findGreatestProduct(numFromFile, 13)[0];
            int greatestProductIndex = findGreatestProduct(numFromFile, 13)[1];
            string multipliers = findMultipliers(numFromFile, 13, greatestProductIndex);


            cout << numFromFile << "\n\n"<< multipliers << "\n\n" << greatestProduct;

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
            string fileName;
            int numOfAdjacents;
            
            //ask for filename
            cout << "File name:" << endl;
            cin >> fileName;

            //ask for numOfAdjacents
            cout << "Number of adjacents:" << endl;
            cin >> numOfAdjacents;

            //run findGreatestProduct on numFromFile(filename) and numOfAdjacents
            string numFromFile = NumFromFile(fileName);
            int greatestProduct = findGreatestProduct(numFromFile, numOfAdjacents)[0];
            int greatestProductIndex = findGreatestProduct(numFromFile, numOfAdjacents)[1];
            string multipliers = findMultipliers(numFromFile, numOfAdjacents, greatestProductIndex);

            cout << numFromFile << "\n\n" << multipliers << "\n\n" << greatestProduct;

            break;
        }
        default:
        {
            cout << "\nPlease try again." << std::endl;

            break;
        }
        }
    }
    exit(0);
}

