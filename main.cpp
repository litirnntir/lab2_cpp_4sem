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

stats quickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	stats res;
	if (end <= begin)
		return res;
	auto pivot = begin, middle = begin + 1;
	for (auto i = begin + 1; i < end; i++)
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
	std::iter_swap(begin, middle - 1);
	res += quickSort(begin, middle - 1);
	res += quickSort(middle, end);

	return res;
}
stats selSort(std::vector<int>::iterator firstIter, std::vector<int>::iterator secondIter)
{
	stats flag;
	flag.copyCount++;
	auto tmp = firstIter;
	while (tmp <= secondIter)
	{
		flag.comparisonCount += 2;
		flag.copyCount++;
		auto small_ = tmp;
		if (tmp != secondIter)
		{
			flag.copyCount++;
			auto iter_ = tmp + 1;
			while (iter_ <= secondIter)
			{
				flag.comparisonCount += 2;
				if (*iter_ < *small_)
				{
					flag.copyCount++;
					small_ = iter_;
				}
				iter_++;
			}
			flag.comparisonCount++;
		}
		std::swap(*(tmp), *(small_));
		flag.copyCount += 3;
		tmp++;
	}
	flag.comparisonCount++;
	return flag;
}

int main()
{
	std::vector<int> a;
	a.push_back(111);
	a.push_back(1);
	a.push_back(0);
	a.push_back(40);
	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	quickSort(a.begin(), a.end());
	for (auto i = a.begin(); i < a.end(); ++i)
	{
		std::cout << *i << "  ";
	}
	return 0;
}