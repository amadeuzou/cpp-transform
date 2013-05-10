
#include "transform.h"

int main() {

	//array to vector
	int a[] = { 12, 23, 34 };
	std::vector<int> v = array_to_vector(a);
	std::cout << v[1] << std::endl;

	//array to map
	const std::string b[][2] = {
		{"one", "check 1"},
		{"two", "check 2"}
	};

	std::map<std::string, std::string> m = array_to_map<std::string, 2>(b);
	std::cout << m["two"] << std::endl;

	std::vector<std::pair<std::string, std::string> > vp = array_to_vector(b);
	std::cout << vp.at(1).first<<" "<<vp.at(1).second<<std::endl;
	
	//array to map
	const std::string x[2] = {
		"one", 
		"two"
	};
	const int y[2] = {
		1, 2
	};

	std::map<std::string, int> p = array_to_map(x, y);
	std::cout << p["two"] << std::endl;
	
	std::vector<std::pair<std::string, int> > vpr = array_to_vector(x, y);
	std::cout << vpr.at(1).first<<" "<<vpr.at(1).second<<std::endl;

	
	return 0;
}
