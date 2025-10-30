#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
// #include <iostream>

std::string floatToStr(float value) {
	std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << value << 'f';
    return oss.str();
}

void strTrim(std::string& str, std::string arr = " \t\r\n") {
	size_t start = str.find_first_not_of(arr);
	if (start > str.length()) {
		str = "";
		return;
	}
	size_t end = str.find_last_not_of(arr);
	str = str.substr(start, end - start + 1);	
}

std::string fileToStr(std::string filePath) {
	std::string fileStr;
	std::string tmp;
	std::ifstream file;
	
	file.open(filePath.c_str(), std::ios::in);
	if (!file)
		throw std::runtime_error("Could not open File: " + filePath);
	while(getline(file, tmp))
		fileStr.append(tmp + "\n");
	file.close();
	strTrim(fileStr);
	return fileStr;
}
