#include <iostream>
#include <vector>
#include <chrono>

size_t lcg()
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

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

stats quickSort(std::vector<int>::iterator iter1, std::vector<int>::iterator iter2)
{
	stats stat;
	if (iter2 <= iter1)
		return stat;
	auto pivot = iter1, middle = iter1 + 1;
	for (auto i = iter1 + 1; i < iter2; i++)
	{
		stat.comparisonCount++;
		if (*i < *pivot)
		{
			stat.copyCount++;
			std::iter_swap(i, middle);
			middle++;
		}
	}
	stat.copyCount++;
	std::iter_swap(iter1, middle - 1);
	stat += quickSort(iter1, middle - 1);
	stat += quickSort(middle, iter2);

	return stat;
}

stats selectionSort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	stats stat;

	for (auto it = begin; it != end - 1; it++)
	{
		auto min_it = it;

		for (auto jt = it + 1; jt != end; jt++)
		{
			stat.comparisonCount++;
			if (*jt < *min_it)
			{
				min_it = jt;
			}
		}

		stat.copyCount += 3;
		std::swap(*min_it, *it);
	}

	return stat;
}

stats testQuickSortRandom(int count)
{
	stats stat;
	for (int j = 0; j < 100; j++)
	{
		std::vector<int> vec;
		for (int i = 0; i < count; i++)
		{
			vec.push_back(lcg());
		}

		auto start = std::chrono::high_resolution_clock::now();
		stat += quickSort(vec.begin(), vec.end());
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		//stat += duration.count();
		stat.time += duration.count();
	}
	std::cout << "Quick Sort for random array with " << count << " numbers"
																 "\n\tTime: " << (double)stat.time / 100 << " microseconds"
			  <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;
}

stats testQuickSortSorted(int count)
{
	stats stat;
	std::vector<int> vec;
	for (int i = 0; i < count; i++)
	{
		vec.push_back(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	stat += quickSort(vec.begin(), vec.end());
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	stat.time += duration.count();

	std::cout << "Quick Sort for sorted array with " << count << " numbers"
																 "\n\tTime: " << (double)stat.time / 100 << " microseconds"
			  <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;

}

stats testQuickSortReverseSorted(int count)
{
	stats stat;
	std::vector<int> vec;
	for (int i = count; i > 0; i--)
	{
		vec.push_back(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	stat += quickSort(vec.begin(), vec.end());
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	stat.time += duration.count();

	std::cout << "Quick Sort for reverse sorted array with " << count << " numbers"
																		 "\n\tTime: " << (double)stat.time / 100
			  << " microseconds" <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;
}

int main()
{
	testQuickSortRandom(10);
	testQuickSortSorted(10);
	testQuickSortReverseSorted(10);

	return 0;
}