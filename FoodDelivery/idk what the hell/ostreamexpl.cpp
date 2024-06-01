#include <iostream>
#include <fstream>

void writeToStream(std::ostream& os) {
    os << "Hello, ";
    os << "world!";
}

int main() {
    // Using std::cout
    writeToStream(std::cout);
    std::cout << std::endl;

    // Using std::cerr
    writeToStream(std::cerr);
    std::cerr << std::endl;

    // Using std::ofstream to write to a file
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        writeToStream(outFile);
        outFile << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    return 0;
}
