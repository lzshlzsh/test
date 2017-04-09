#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[0], std::ifstream::in | std::ifstream::binary);

    if (!ifs) {
        std::cout << "cannot open " << argv[0] << std::endl;
        return -1;
    }
    return 0;
}
