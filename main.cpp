#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

size_t lcg()
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

int checkIsInt()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
}

int checkMenu()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n') || number > 5 || number < 1)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
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

		stat.time += duration.count();
	}
	std::cout << "Quick Sort for random array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds"
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

	std::cout << "Quick Sort for sorted array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds"
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

	std::cout << "Quick Sort for reverse sorted array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds" <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;
}

stats testSelectionSortRandom(int count)
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
		stat += selectionSort(vec.begin(), vec.end());
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		stat.time += duration.count();
	}
	std::cout << "Selection Sort for random array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds"
			  <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;
}

stats testSelectionSortSorted(int count)
{
	stats stat;
	std::vector<int> vec;
	for (int i = 0; i < count; i++)
	{
		vec.push_back(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	stat += selectionSort(vec.begin(), vec.end());
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	stat.time += duration.count();

	std::cout << "Selection Sort for sorted array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds"
			  <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;

}

stats testSelectionSortReverseSorted(int count)
{
	stats stat;
	std::vector<int> vec;
	for (int i = count; i > 0; i--)
	{
		vec.push_back(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	stat += selectionSort(vec.begin(), vec.end());
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	stat.time += duration.count();

	std::cout << "Selection Sort for reverse sorted array with " << count << " numbers" <<
			  "\n\tTime: " << (double)stat.time / 100
			  << " microseconds" <<
			  "\n\tComparisonCount : " << stat.comparisonCount / 100 <<
			  "\n\tCopyCount : " << stat.copyCount / 100 << std::endl;
	return stat;
}

void printMenu()
{
	std::cout << "\n1. Quick sort\n";
	std::cout << "2. Selection sort\n";
	std::cout << "3. Merge sort\n";
	std::cout << "4. Print stats\n\n";
	std::cout << "Input number: ";
}

int main()
{
	int choice;
	bool exit = false;
	while (!exit)
	{
		printMenu();
		choice = checkMenu();
		if (choice == 1)
		{
			int n, i = 0, k;
			std::vector<int> test;
			std::cout << "Enter the amount of numbers: ";
			n = checkIsInt();
			std::cout << std::endl;
			std::cout << "Input numbers: ";
			while (i < n)
			{
				k = checkIsInt();
				test.push_back(k);
				i++;
			}
			stats tmp = quickSort(test.begin(), test.end());
			std::cout << "comparisonCount: " << tmp.comparisonCount << " " << "copyCount: " << tmp.copyCount
					  << std::endl;
			printVector(test.begin(), test.end());
		}
		if (choice == 2)
		{
			int n, i = 0, k;
			std::vector<int> test;
			std::cout << "Input the amount of numbers: ";
			n = checkIsInt();
			std::cout << std::endl;
			std::cout << "Input numbers: ";
			while (i < n)
			{
				k = checkIsInt();
				test.push_back(k);
				i++;
			}
			stats tmp = selectionSort(test.begin(), test.end());
			std::cout << "comparisonCount: " << tmp.comparisonCount << " " << "copyCount: " << tmp.copyCount
					  << std::endl;
			printVector(test.begin(), test.end());
		}
		if (choice == 3)
		{
		}
		if (choice == 4)
		{
			std::vector<int> numbs = { 1000, 2000, 3000, 4000, 5000, 10000 };

			std::ofstream file1, file2, file3;
			stats tmp1, tmp2, tmp3;
			file1.open("/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/comparisonCountQuickSort.txt");
			file2.open("/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/copyCountQuickSort.txt");
			file3.open("/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/timeQuickSort.txt");
			for (auto i : numbs)
			{
				tmp1 = testQuickSortRandom(i);
				tmp2 = testQuickSortSorted(i);
				tmp3 = testQuickSortReverseSorted(i);
				file1 << i << " " << tmp1.comparisonCount << " " << tmp2.comparisonCount << " "
					  << tmp3.comparisonCount << "\n";
				file2 << i << " " << tmp1.copyCount << " " << tmp2.copyCount << " " << tmp3.copyCount << "\n";
				file3 << i << " " << tmp1.time << " " << tmp2.time << " " << tmp3.time << "\n";
			}
			file1.close();
			file2.close();
			file3.close();
			file1.open(
				"/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/comparisonCountSelectionSort.txt");
			file2.open(
				"/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/comparisonCountSelectionSort.txt");
			file3.open("/Users/aleksandragorbuncova/CLionProjects/salnyed/lab2-cpp-4sem/timeSelectionSort.txt");
			for (auto i : numbs)
			{
				tmp1 = testSelectionSortRandom(i);
				tmp2 = testSelectionSortSorted(i);
				tmp3 = testSelectionSortReverseSorted(i);
				file1 << i << " " << tmp1.comparisonCount << " " << tmp2.comparisonCount << " "
					  << tmp3.comparisonCount << "\n";
				file2 << i << " " << tmp1.copyCount << " " << tmp2.copyCount << " " << tmp3.copyCount << "\n";
				file3 << i << " " << tmp1.time << " " << tmp2.time << " " << tmp3.time << "\n";
			}
			file1.close();
			file2.close();
			file3.close();
		}
		if (choice == 5)
		{
			exit = true;
		}
	}
}