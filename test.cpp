#include<memory>

struct dummy
{
	int value;
	dummy(int value) : value(value) {}
};

void func(std::shared_ptr<dummy> &d)
{
	d = std::make_shared<dummy>(2);
}

int _main()
{
	std::shared_ptr<dummy> d = std::make_shared<dummy>(1);
	std::shared_ptr<dummy> d2 = d;
	func(d);
	return 0;
}