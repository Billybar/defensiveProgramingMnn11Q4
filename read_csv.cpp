

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype> // for std::isdigit



bool isNumeric(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;

    // Check for optional leading sign
    if (str[0] == '+' || str[0] == '-') {
        start++;
    }

    bool hasDigits = false;
    bool hasDot = false;

    for (size_t i = start; i < str.length(); ++i) {
        if (std::isdigit(str[i])) {
            hasDigits = true; // Found a digit
        } else if (str[i] == '.') {
            if (hasDot) {
                return false; // Only one dot is allowed
            }
            hasDot = true; // Found a dot
        } else {
            return false; // Invalid character found
        }
    }

    return hasDigits; // Must have at least one digit
}

double parseToDouble(const std::string& str) {
    if (isNumeric(str)) {
        return std::stod(str);  // Convert string to double
    } else {
        throw std::invalid_argument("The string is not a valid double");
    }
}


int main() {
    std::string filename = "example.csv";  // Path to your CSV file
    std::ifstream file(filename);       // Open the CSV file

    if (!file.is_open()) {
        std::cerr << "Could not open the file " << filename << std::endl;
        return 1;
    }

    // Check for BOM at the beginning
    char bom[3];
    file.read(bom, 3);
    if (!(bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF')) {
        // If no BOM, seek back to the start
        file.seekg(0);
    }

    std::string line;
    std::vector<std::vector<std::string>> data;  // To store CSV data

    // Read the file line by line
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // Split the line by commas
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);  // Add the row to the data vector
    }

    file.close();

    // Display the data (optional)
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    // Print sum cell nums for each row
    for (const auto& row : data) {

        double row_sum = 0;
        for (auto& cell : row) {
            if(isNumeric(cell)){
                row_sum += parseToDouble(cell);
            }
        }
        std::cout << "Total of line:" << row_sum << std::endl; // print each line
    }

    // Print rows totals
    for (const auto& row : data) {

        double row_sum = 0;
        for (auto& cell : row) {
            if(isNumeric(cell)){
                row_sum += parseToDouble(cell);
            }
        }
        std::cout << "Total of line:" << row_sum << std::endl; // print each line
    }

    std::vector<double> columnSums;  // Vector to hold sums for each column

    // Iterate over each row in the data
    for (const auto& row : data) {
        for (size_t col = 0; col < row.size(); ++col) {
            // Resize columnSums to accommodate new columns
            if (col >= columnSums.size()) {
                columnSums.resize(col + 1, 0.0);
            }
            if (isNumeric(row[col])) {
                columnSums[col] += parseToDouble(row[col]);
            }
        }
    }

    // Print column totals
    for (size_t col = 0; col < columnSums.size(); ++col) {
        std::cout << "Total of column " << col << ": " << columnSums[col] << std::endl;
    }

    return 0;
}

