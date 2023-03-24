// ProjectEuler8 - Largest Product in a Series.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

/**
ORIGINAL PROBLEM

The four adjacent digits in the 1000-digit number that have the greatest product are 
9 × 9 × 8 × 9 = 5832.

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

string NumGenerator(int givenNumSize)
{
    srand(time(0));
    string generatedNumber;
    for (int i = 0; i < givenNumSize; i++)
        generatedNumber = generatedNumber + to_string(rand() % 10);

    return generatedNumber;
}

int* FindGreatestProduct(string givenNum, int numOfAdjacents)
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
                maxIndex = i - numOfAdjacents + 1;
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

string FindMultipliers(string givenNum, int numOfAdjacents, int maxIndex)
{
    string multipliers = "";
    
    for (int i = maxIndex; i < maxIndex + numOfAdjacents; i++)
    {
        if (multipliers == "") { multipliers = givenNum[i]; }
        else { multipliers = multipliers + " x " + givenNum[i]; }
    }

    return multipliers;
}

void NumWithSolution(string givenNum, int numOfAdjacents, int maxIndex)
{
    string numBeforeSolution = "";
    for (int i = 0; i <= maxIndex - 1; i++) 
    {
        if (i % 50 == 0) numBeforeSolution = numBeforeSolution + "\n";
        numBeforeSolution = numBeforeSolution + givenNum[i];
    }
    
    string multipliers = "";
    for (int i = maxIndex; i < maxIndex + numOfAdjacents; i++)
    {
        if (i % 50 == 0) multipliers = multipliers + "\n";
        multipliers = multipliers + givenNum[i];
    }
        
    string numAfterSolution = "";
    for (int i = maxIndex + numOfAdjacents; i < givenNum.length(); i++)
    {
        if (i % 50 == 0) numAfterSolution = numAfterSolution + "\n";
        numAfterSolution = numAfterSolution + givenNum[i];
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
    cout << numBeforeSolution;
    SetConsoleTextAttribute(h, 4);
    cout << multipliers;
    SetConsoleTextAttribute(h, 15);
    cout << numAfterSolution;
}

int main() 
{
    bool programRunning = true;
    int choice;

    cout << "WELCOME TO MY SOLUTION TO PROJECT EULER PROBLEM #8!\n" << endl;
    cout << "Problem details...\n" << endl;
    cout << "Within the given number, find the adjacent digits that have the greatest product." << endl;
    cout << "The output should include the adjacent digits, and the value of the product." << endl;
    cout << "The given number can vary in length up to 1000 digits," << endl;
    cout << "and the amount of calculated adjacent digits can vary up to 13 digits." << endl;
    cout << "Do this in C++ or Java with a O(n) processing time." << endl;
    cout << "\n_________________________________________________________________________________" << endl;


    //MAIN MENU
    while (programRunning)
    {
        cout << "ACTIONS MENU\n" << endl;

        cout << "\t1) Original parameters  : Given original 1000 digits, find greatest product of 13 adjacent." << endl;
        cout << "\t2) Custom parameters    : Randomly generate x digits, find greatest product of x adjacent digits." << endl;
        cout << "\t3) Filed parameters     : Get digits from file, find greatest product of x adjacent digits." << endl;
        cout << "\t0) Exit Program!" << endl;

        cout << "\nPlease enter a number to select an option...";
        cin >> choice;
        cout << "\n-------------------------------------------------------------------------------------------------" << endl;

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
                
                cout << "Within the given number below, find 13 adjacent digits with the greatest product!" << endl;

                string numFromFile = NumFromFile("original.txt");
                int greatestProduct = FindGreatestProduct(numFromFile, 13)[0];
                int greatestProductIndex = FindGreatestProduct(numFromFile, 13)[1];
                string multipliers = FindMultipliers(numFromFile, 13, greatestProductIndex);

                cout << "\nResults...\n" << endl;
                NumWithSolution(numFromFile, 13, greatestProductIndex);
                cout << "\n\n" << multipliers << " =\n\n" << greatestProduct << endl;

                cout << "\n-------------------------------------------------------------------------------------------------" << endl;
                
                break;
            }
            case 2:
            {
                //Custom parameters : Randomly generate x digits, find greatest product of x adjacent digits
                                
                int givenNumSize;
                int numOfAdjacents;

                cout << "To generate the number, please enter the desired amount of digits: ";
                cin >> givenNumSize;
                
                cout << "Please enter the number of adjacent digits to find: ";
                cin >> numOfAdjacents;

                cout << "\nWithin the given number below, find " << numOfAdjacents << " adjacent digits with the greatest product!" << endl;
                
                string givenNum = NumGenerator(givenNumSize);
                int greatestProduct = FindGreatestProduct(givenNum, numOfAdjacents)[0];
                int greatestProductIndex = FindGreatestProduct(givenNum, numOfAdjacents)[1];
                string multipliers = FindMultipliers(givenNum, numOfAdjacents, greatestProductIndex);

                cout << "\nResults...\n" << endl;
                NumWithSolution(givenNum, numOfAdjacents, greatestProductIndex);
                cout << "\n\n" << multipliers << " =\n\n" << greatestProduct << endl;

                cout << "\n-------------------------------------------------------------------------------------------------" << endl;
                
                break;
            }
            case 3:
            {
                //Filed parameters : Get digits from file, find greatest product of x adjacent digits.
                
                string fileName;
                int numOfAdjacents;
            
                cout << "To get the number from a file, please enter the file name (w/ .txt): ";
                cin >> fileName;

                cout << "Please enter the number of adjacent digits to find: ";
                cin >> numOfAdjacents;

                cout << "\nWithin the given number below, find " << numOfAdjacents << " adjacent digits with the greatest product!" << endl;

                string numFromFile = NumFromFile(fileName);
                int greatestProduct = FindGreatestProduct(numFromFile, numOfAdjacents)[0];
                int greatestProductIndex = FindGreatestProduct(numFromFile, numOfAdjacents)[1];
                string multipliers = FindMultipliers(numFromFile, numOfAdjacents, greatestProductIndex);

                cout << "\nResults...\n" << endl;
                NumWithSolution(numFromFile, numOfAdjacents, greatestProductIndex);
                cout << "\n\n" << multipliers << "\n\n" << greatestProduct << endl;
            
                cout << "\n-------------------------------------------------------------------------------------------------" << endl;
                
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
