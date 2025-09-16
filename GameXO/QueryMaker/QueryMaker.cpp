#include "QueryMaker.h"
#include <string_view>

std::string query::makeHello(std::string name) {
	return "hello:" + name;
}

std::string query::makeTurn(int x, int y) {
	//std::string ans = "turn";
	return "turn:" + std::to_string(x) + ':' + std::to_string(y);
}

std::string query::makeTurn(int x, int y, char ch) {
	//std::string ans = "turn";
	return "turn:" + std::to_string(x) + ':' + std::to_string(y) + ':' + ch;
}

std::vector<std::string> query::get(std::string& q) {
	std::vector<std::string> v;
	std::string_view sw = q;
	int counter = 0;
	while (sw.find(':') != std::string::npos) {
		//std::cout << sw << '\n';
		v.push_back((std::string)sw.substr(0, sw.find(':')));
		sw.remove_prefix(sw.find(':') + 1);
		//std::cout << sw << '\n';
		counter++;
		if (counter==10) {
			exit(1);
		}
	}

	v.push_back(sw.data());

	return v;
}