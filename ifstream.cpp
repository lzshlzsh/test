/*
 * =====================================================================================
 *
 *       Filename:  ifstream.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/11/2013 05:03:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

// read a file into memory
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

int main (int argc, char **argv) {
  std::ifstream is (argv[1], std::ifstream::binary | std::ifstream::in);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];

    // read data as a block:
    is.read (buffer,length);

    is.close();

    delete[] buffer;
  }

  return 0;
}
