#include <string>
#include <sstream>

class Card
{
	private:
		int credit_limit;
		int gage;
	public:
		Card(int credit_limit, int gage);
		std::string print();
};
