/*
Name:Diego lacambacal, NSHE: 5005247606, Section: 302-1001/1003, Assignment 1
Description: Cocktail Shaker DLL
Input: File
Output: File organized by Cocktail Sort Method
*/
#include <iostream>
#include <fstream>
#include "LL.h"
using namespace std;

int main()
{

    // filename
    string fName;
    ifstream iFile;

    cout << "Enter filename: ";
    cin >> fName;

    // Checks validity of input
    iFile.open(fName);
    while (!iFile.is_open())
    {
        cout << "Enter filename: ";
        cin >> fName;
        iFile.open(fName);
    }

    // reads in txt file into LL
    LL<int> mainLL;
    int getter;
    while (iFile >> getter)
    {
        mainLL.tailInsert(getter);
    }

    /*
    //tester to see if it read in
    LL<int>::Iterator it, nil, begin, end;
    begin = mainLL.begin();
    begin++;
    begin++;
    end = mainLL.begin();
    end++;
    end++;
    end++;

    cout << *begin << endl << *end << endl;
    mainLL.swapNodes(begin,end);
    cout << *begin << endl << *end << endl << endl << endl << endl;

    for (it = mainLL.begin(); it != nil; it++)
        std::cout << *it << "\n";
    OR
    while(i !=NULL) {
     cout << i->data<<"\n"
     i = i->next;
    }
    */

    // NEW COCKTAIL ATTEMPT
    // try and simplify things, less is more
    bool swapped = true;
    LL<int>::Iterator x, y, it;
    LL<int>::Iterator xplus1, yminus1;
    LL<int>::Iterator begin, end;
    LL<int>::Iterator nil(nullptr);
    int counter = 0;

    // runs while something is getting swapped
    while (swapped)
    {
        // does this, or else will seg fault in beginning
        if (counter == 0)
        {
            begin = mainLL.begin();
            end = mainLL.end();
        }

        swapped = false;

        // left to right
        for (x = begin; x != end; x++)
        {
            // cout << "starting left to right at " << *x << endl;
            xplus1 = x;
            xplus1++;
            if (xplus1 == nullptr)
            {
                break;
            }

            // cout << "checking " << *x << " and " << *xplus1 << endl;
            //  checks if left is greater than right
            if (*x > *xplus1)
            {
                mainLL.swapNodes(x, xplus1);
                swapped = true;
            }
        }

        //checks if an element was swapped
        if (!swapped)
        {
            break;
        }
        //increases counter to set end/beginning points
        else
        {
            counter++;
        }

        //decrements the end point
        end = mainLL.end();
        for (unsigned int i = 0; i < counter; i++)
        {
            end--;
        }

        swapped = false;
        
        // right to left
        for (y = end; y != begin; y--)
        {
            // cout << "starting right to left at " << *y << endl;
            yminus1 = y;
            yminus1--;
            if (yminus1 == nullptr)
            {
                break;
            }

            // cout << "checking " << *y << " and " << *yminus1 << endl;
            //  checks if left is greater than right
            if (*y < *yminus1)
            {
                mainLL.swapNodes(yminus1, y);
                swapped = true;
            }
        }
        //checks if something was swapped
        if (!swapped)
        {
            break;
        }

        //increments beginning point
        begin = mainLL.begin();
        for (unsigned int i = 0; i < counter; i++)
        {
            begin++;
        }
    }

    //prints out
    for (it = mainLL.begin(); it != nil; it++)
        std::cout << *it << "\n";

    return 0;
}
