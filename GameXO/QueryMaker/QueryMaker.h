/*template<typename T>
class QueryMaker {
	T& 
};*/
#include <iostream>
#include <vector>
#include <string>

namespace query {
	std::string makeHello(std::string name);

	std::string makeTurn(int x, int y);

	std::string makeTurn(int x, int y, char ch);

	std::vector<std::string> get(std::string& q);
	//std::string make
}