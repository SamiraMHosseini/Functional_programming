#include <vector>
#include <iostream>

// Simple demo of fucntional programming in C++

// First-class and higher-order functions

template <typename Func>
// The filter function takes a function func as a parameter
// which is an example of a higher-order function.
void filter(Func func, const std::vector<int>& arr)
{
	for (const auto& item : arr)
	{
		if (func(item))
		{
			std::cout << item << '\n';
		}
	}
}

int main()
{
	std::vector<int> arr{ -1,-2,3,-4,-5,6 };
	//Lambda function
	auto f = [](int x) -> bool {return x % 2 == 0 && x > 2; };
	// Pass a lmabda as a parameter
	filter([](int x)->bool {return x <= 0; }, arr);
	filter(f, arr);
}

