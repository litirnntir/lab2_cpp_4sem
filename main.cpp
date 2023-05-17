#include <iostream>
#include <vector>
#include <chrono>


void printVector(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	auto t = iter1;
	while (t < iter2)
	{
		std::cout << *t << " ";
		t++;
	}
	std::cout << std::endl;
}

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

stats quickSort(std::vector<int>& arr, std::vector<int>::iterator begin, std::vector<int>::iterator end)
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
	res += quickSort(arr, begin, middle - 1);
	res += quickSort(arr, middle, end);

	return res;
}


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}


stats selectionSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	stats s;

	for (auto it = begin; it != end - 1; it++) {
		auto min_it = it;

		for (auto jt = it + 1; jt != end; jt++) {
			s.comparisonCount++;
			if (*jt < *min_it) {
				min_it = jt;
			}
		}

		s.copyCount += 3;
		std::swap(*min_it, *it);
	}

	return s;
}



int main()
{
	std::vector<int> a;
	stats s;

	for (int i = 10; i >= 1; i--)
	{
		a.push_back(i);
	}

	printVector(a.begin(), a.end());


	selectionSort(a.begin(), a.end());

	printVector(a.begin(), a.end());

	quickSort(a, a.begin(), a.end());

	printVector(a.begin(), a.end());

	return 0;
}