#include <iostream>
#include <vector>

struct stats
{
	size_t comparisonCount = 0, copyCount = 0, time = 0;
	void operator+=(const stats& rhs)
	{
		comparisonCount += rhs.comparisonCount;
		copyCount += rhs.copyCount;
		time += rhs.time;
	}
};

stats quickSort(std::vector<int>::iterator firstIter, std::vector<int>::iterator secondIter)
{
	stats res;
	if (secondIter <= firstIter)
		return res;
	auto pivot = firstIter, middle = firstIter + 1;
	for (auto i = firstIter + 1; i < secondIter; i++)
	{
		res.comparisonCount++;
		if (*i < *pivot)
		{
			res.copyCount++;
			std::iter_swap(i, middle);
			middle++;
		}
	}
	res.copyCount++;
	std::iter_swap(firstIter, middle - 1);
	res += quickSort(firstIter, middle - 1);
	res += quickSort(middle, secondIter);

	return res;
}
stats selSort(std::vector<int>::iterator firstIter, std::vector<int>::iterator secondIter)
{
	stats res;
	if (secondIter <= firstIter)
		return res;

	res.copyCount++;
	auto tmp = firstIter;
	while (tmp <= secondIter)
	{
		res.comparisonCount += 2;
		res.copyCount++;
		auto small_ = tmp;
		if (tmp != secondIter)
		{
			res.copyCount++;
			auto it = tmp + 1;
			while (it <= secondIter)
			{
				res.comparisonCount += 2;
				if (*it < *small_)
				{
					res.copyCount++;
					small_ = it;
				}
				it++;
			}
			res.comparisonCount++;
		}
		std::swap(*(tmp), *(small_));
		res.copyCount += 3;
		tmp++;
	}
	res.comparisonCount++;
	return res;
}

int main()
{
	std::vector<int> a;
	for (int i = 10000; i > 0; --i)
	{
		a.push_back(i);
	}
	selSort(a.begin(), a.end());
	for (auto i = a.begin(); i < a.end(); ++i)
	{
		std::cout << *i << " ";
	}
	return 0;
}