#include "extractData.h"

void writeDataToFile(const std::string& fileName, const std::string& data) {
    // Open the file in append mode
    std::ofstream outFile(fileName, std::ios::app);

    // Check if the file is open
    if (!outFile) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    // Write data to the file
    outFile << data << std::endl;

    // Close the file
    outFile.close();
}
