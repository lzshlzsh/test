/*
 * =====================================================================================
 *
 *       Filename:  strstream.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/19/2015 05:40:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

// example on extraction
#include <iostream>     // std::cin, std::cout, std::hex
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#define CHECK_SS_RETURN(__ss, __err_msg) \
    if (__ss.rdstate() & (stringstream::eofbit | stringstream::failbit | stringstream::badbit)) { \
        cerr << "<ERR>" <<  __err_msg << endl; \
        return -1; \
    }
#define CHECK_SS_ERROR_RETURN(__ss, __err_msg) \
        if (__ss.rdstate() & (stringstream::failbit | stringstream::badbit)) { \
            cerr << "<ERR>" <<  __err_msg << endl; \
            return -1; \
        }

int main (int argc, char **argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input>" << endl;
		return -1;
	}

	ifstream ifs(argv[1]);
	string line;
	stringstream ss;
	int x;
	
	while (getline(ifs, line)) {
		ss.str(line);

		ss >> x;
		CHECK_SS_RETURN(ss, "resolve x");
		cout << x << endl;

		ss >> x;
		CHECK_SS_RETURN(ss, "resolve y");
		cout << x << endl;
		for (int i = 0; i < 400; i++) {
			ss >> x;
			CHECK_SS_ERROR_RETURN(ss, "resolve i1");
			cout << x << endl;
		}
		if (ss.rdstate() & stringstream::eofbit) {
			cout << "endline" << endl;
		} else {
			cout << "not endline" << endl;
		}
		break;
	}

	return 0;
}
