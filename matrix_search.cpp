/**
 * @file matrix_search.cpp
 * @brief
 * @version 1.0
 * @date 02/16/2017 07:34:30 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <vector>
#include <iostream>
#include <stdlib.h>

void print_v(const std::vector<int> &v, const size_t r) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (r == i) {
            std::cout << "\033[32m";
        }
        std::cout << v[i] << " ";
        if (r == i) {
            std::cout << "\033[0m";
        }
    }
    std::cout << std::endl;
}

int nearlest_le_fixed_x(const std::vector<std::vector<int> > &matrix, 
    const int x, const int low, const int high, const int target) {
    int l = low, h = high, m;

    while (l <= h) {
        m  = (l + h) / 2;
        if (matrix[x][m] == target) {
            return m;
        } else if (matrix[x][m] < target) {
            l = m + 1;
        } else {
            h = m - 1;
        }
    }

    return h;
}

int nearlest_le_fixed_y(const std::vector<std::vector<int> > &matrix, 
    const int y, const int low, const int high, const int target) {
    int l = low, h = high, m;

    while (l <= h) {
        m  = (l + h) / 2;
        if (matrix[m][y] == target) {
            return m;
        } else if (matrix[m][y] < target) {
            l = m + 1;
        } else {
            h = m - 1;
        }
    }

    return h;
}

bool matrix_search(const std::vector<std::vector<int> > &matrix,
    const int target) {
    int row = 0, col = matrix[0].size() - 1;

    while (row < static_cast<int>(matrix.size()) && col >= 0) {
        if (matrix[row][col] == target) {
            std::cout << row << '\t' << col << std::endl;
            return true;  
        }  
        else if(matrix[row][col] > target) {
            col--;  
        }  
        else {
            row++;  
        }  
    }  

    return false;  
}

int main(int argc, char **argv) {
    const int N = 10;
    std::vector<std::vector<int> > matrix;

    if (2 != argc) {
        std::cout << "usage: " << argv[0] << " digital" << std::endl;
        std::cout << "\t0 ~ " << N * N - 1 << " can be found" << std::endl;
        return -1;
    }

    for (int i = 0; i < N; ++i) {
        matrix.push_back(std::vector<int>());
        std::vector<int> &line = matrix.back();

        for (int j = 0; j < N; j++) {
            line.push_back(i * N + j);
        }
    }

    std::cout << matrix_search(matrix, atoi(argv[1])) << std::endl;

    return 0;
}

