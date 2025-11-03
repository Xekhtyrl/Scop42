/*
"v"
"vn"
"f"
"#"
"usemtl"
"mtlib"
"g"
"s"
*/
#include <iostream>
#include <fstream>
void readFile(std::ifstream file) {
	std::string tmp;
	while(getline(file, tmp)) {
		if (tmp.find('#') == 0)
			continue;
		if (tmp.find("vn") == 0)
			
	}
}