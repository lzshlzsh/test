//
// Created by lzs on 10/18/20.
//

#include <iostream>

inline bool wildcardMatch(const std::string &s, const std::string &p) {
    size_t idxs = 0UL, idxp = 0UL, idxstar = ~0UL, idxmatch = 0UL;
    while (idxs < s.length()) {
        if (idxp < p.length() && (s[idxs] == p[idxp] || p[idxp] == '?')) {
            idxp++;
            idxs++;
        } else if (idxp < p.length() && p[idxp] == '*') {
            idxstar = idxp;
            idxp++;
            idxmatch = idxs;
        } else if (idxstar != ~0UL) {
            idxp = idxstar + 1;
            idxmatch++;
            idxs = idxmatch;
        } else {
            return false;
        }
    }
    while (idxp < p.length() && p[idxp] == '*') {
        idxp++;
    }
    return idxp == p.length();
}

struct TestCase {
    const char *path;
    const char *rule;
};

int main(int argc, char **argv) {
    TestCase test_cases[] = {
            {"/data/logs/test/aa.log", "/data/logs/**test/aa.log"},
            {"/data/logs/test/aa.log", "/data/logs/*test/aa.log"},
            {"/data/logs/test/aa.log", "/data/logs/**/aa.log"},
            {"/data/logs/test/aa.log", "/data/logs/**/aa.log"},
    };

    for (unsigned int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        std::cout << test_cases[i].path << " | " << test_cases[i].rule << " => "
                  << wildcardMatch(std::string(test_cases[i].path), std::string(test_cases[i].rule)) << std::endl;
    }

    return 0;
}