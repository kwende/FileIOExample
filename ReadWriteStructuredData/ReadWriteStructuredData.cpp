
#include "stdafx.h"

// First things, first, include the proper header files for file i/o
#include <fstream>
// this is for simple printing. 
#include <iostream>

//  his could/should be laid out better if we were being C++ purists, but I'm 
// just trying to get my point across. So here is a data structure that
// is probably relevant to what you're doing... 
struct Point3D
{
    int X; 
    int Y; 
    int Z; 
};

int main()
{
    // variable placeholder. 
    const int NumberOfPoints = 640*480; 

    // so now we're going to allocate a ton of these things and set them to values. 
    Point3D* pointArray = new Point3D[NumberOfPoints];
    for (int y = 0, i=0; y < 480; y++)
    {
        for (int x = 0; x < 640; x++, i++)
        {
            // set to something we can easily verify later. 
            pointArray[i].X = x; 
            pointArray[i].Y = y; 
            pointArray[i].Z = i; 
        }
    }

    // open up a new file called output.dat in binary mode, and set
    // it so that every write APPENDS to the file end. 
    std::ofstream fout("output.dat", std::ios::binary | std::ios::app); 
    // write out the buffer
    fout.write((char*)pointArray, sizeof(Point3D) * NumberOfPoints); 

    // flush and close (probably redundant, close should flush
    fout.flush(); 
    fout.close(); 

    // okay, so now let's open. again, let's open as a binary file. 
    //(fyi, the difference between binary and ASCII mode is that with 
    // binary what you write/read is precisely what gets saved/read, in text mode,
    // sometimes the operating system may do special encoding (useful 
    // for text files, not for binary files)
    std::ifstream fin("output.dat", std::ios::binary); 

    Point3D* readArray = new Point3D[NumberOfPoints];
    fin.read((char*)readArray, sizeof(Point3D) * NumberOfPoints); 

    // verify

    int numberGood = 0, numberRead = 0; 
    for (int c = 0; c < NumberOfPoints; c++)
    {
        if (pointArray[c].X == readArray[c].X &&
            pointArray[c].Y == readArray[c].Y &&
            pointArray[c].Z == readArray[c].Z)
        {
            numberGood++; 
        }
        numberRead++; 
    }

    std::cout << "Number read: " << numberRead << " number good " << numberGood << std::endl; 
    getchar(); // wait for return

    return 0;
}

