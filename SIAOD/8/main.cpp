#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>
#include <fstream>

typedef unsigned long long ull;

struct sorting_data
{
    ull comparisons;
    ull moves;
    sorting_data();
    sorting_data(ull comparisons, ull moves);
};

sorting_data::sorting_data()
{
    comparisons = 0;
    moves = 0;
}

sorting_data::sorting_data(ull comparisons, ull moves)
{
    this->comparisons = comparisons;
    this->moves = moves;
}

sorting_data selection_sort(std::vector<int>& vec)
{
    sorting_data data;

    for (int i = 0; i < vec.size(); i++)
    {
        int min_index = i;
        for (int j = i + 1; j < vec.size(); j++)
        {
            data.comparisons++;
            if (vec[j] < vec[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            data.moves++;
            std::swap(vec[i], vec[min_index]);
        }
    }

    return data;
}

sorting_data heapify(std::vector<int>& vec, int head, int N = -1)
{
    sorting_data data;
    
    if (N == -1)
    {
        N = vec.size();
    }

    int largest = head;
    int left = 2 * head + 1;
    int right = 2 * head + 2;

    data.comparisons++;
    if (left >= 0 && left < N && vec[left] > vec[largest])
    {
        largest = left;
    }

    data.comparisons++;
    if (right >= 0 && right < N && vec[right] > vec[largest])
    {
        largest = right;
    }

    if (largest != head)
    {
        data.moves++;
        std::swap(vec[head], vec[largest]);
        sorting_data returned = heapify(vec, largest, N);
        return sorting_data(data.comparisons + returned.comparisons, 
                            data.moves + returned.moves);
    }

    return data;
}

sorting_data heap_sort(std::vector<int>& vec)
{
    sorting_data data;

    for (int i = vec.size() / 2 - 1; i >= 0; i--)
    {
        sorting_data returned = heapify(vec, i);
        data.comparisons += returned.comparisons;
        data.moves += returned.moves;
    }

    for (int i = vec.size() - 1; i > 0; i--)
    {
        data.moves++;
        std::swap(vec[i], vec[0]);
        sorting_data returned = heapify(vec, 0, i);
        data.comparisons += returned.comparisons;
        data.moves += returned.moves;
    }

    return data;
}

sorting_data merge_sort_with_borders(std::vector<int>& vec, int left, int right)
{
    sorting_data data;

    if (left  <= -1 || left  >= vec.size() ||
        right <= -1 || right >= vec.size() ||
        left == right)
    {
        return data;
    }

    int middle = left + (right - left) / 2;
    sorting_data returned_left  = merge_sort_with_borders(vec, left, middle);
    sorting_data returned_right = merge_sort_with_borders(vec, middle + 1, right);
    data.comparisons += returned_left.comparisons + returned_right.comparisons;
    data.moves += returned_left.moves + returned_right.moves;

    std::vector<int> tmp(right - left + 1);
    int curr_left = left;
    int curr_right = middle + 1;
    for (int i = 0; i < tmp.size(); i++)
    {
        if (curr_left <= middle && curr_right <= right)
        {
            data.comparisons++;
            if (vec[curr_left] < vec[curr_right])
            {
                tmp[i] = vec[curr_left];
                curr_left++;
            }
            else
            {
                tmp[i] = vec[curr_right];
                curr_right++;
            }
        }
        else if (curr_left <= middle)
        {
            tmp[i] = vec[curr_left];
            curr_left++;
        }
        else if (curr_right <= right)
        {
            tmp[i] = vec[curr_right];
            curr_right++;
        }
    }

    for (int i = left; i <= right; i++)
    {
        vec[i] = tmp[i - left];
    }
    data.moves += right - left + 1; 

    return data;
}

sorting_data merge_sort(std::vector<int>& vec)
{
    return merge_sort_with_borders(vec, 0, vec.size() - 1);
}

bool is_sorted(const std::vector<int>& vec)
{
    for (int i = 0; i < vec.size() - 1; i++)
    {
        if (vec[i] > vec[i + 1])
        {
            return false;
        }
    }
    return true;
}

std::vector<int> random_unsorted_vector(int size)
{
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++)
    {
        vec[i] = std::rand();
    }
    return vec;
}

std::vector<int> random_sorted_vector(int size)
{
    std::vector<int> vec = random_unsorted_vector(size);
    std::sort(vec.begin(), vec.end());
    return vec;
}

std::vector<int> random_reversed_sorted_vector(int size)
{
    std::vector<int> vec = random_unsorted_vector(size);
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    return vec;
}

void test_sort(sorting_data (*sort)(std::vector<int>&),
               std::vector<int> (*generate_vector)(int),
               std::string output_file_name, int min_size, int max_size, int step)
{
    std::ofstream file(output_file_name);
    for (int size = min_size; size <= max_size; size += step)
    {
        std::vector<int> vec = generate_vector(size);
        auto start = std::chrono::high_resolution_clock::now();
        sorting_data data = sort(vec);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast
                        <std::chrono::milliseconds>(stop - start);

        if (!is_sorted(vec))
        {
            file << "ERROR: ouput vector is not sorted\n";
        }
        else
        {
            file << size << ' ' << duration.count() << ' ' 
                 << data.comparisons << ' ' << data.moves << '\n';
        }
    }
    file.close();
}

int main()
{
    std::srand(std::time(nullptr));
    const int max_size = 100000;
    const int min_size = 10000;
    const int step = 10000;

    std::cout << "Testing selection sort on sorted arrays...\n";
    test_sort(selection_sort, random_sorted_vector,
              "selection_sort_sorted_results.txt", 
              min_size, max_size, step);
    std::cout << "Testing selection sort on reversed sorted arrays...\n";
    test_sort(selection_sort, random_reversed_sorted_vector,
              "selection_sort_reversed_sorted_results.txt",
              min_size, max_size, step);
    std::cout << "Testing selection sort on unsorted arrays...\n";
    test_sort(selection_sort, random_unsorted_vector,
              "selection_sort_unsorted_results.txt",
              min_size, max_size, step);
              
    std::cout << "Testing heap sort on sorted arrays...\n";
    test_sort(heap_sort, random_sorted_vector,
              "heap_sort_sorted_results.txt", 
              min_size, max_size, step);
    std::cout << "Testing heap sort on reversed sorted arrays...\n";
    test_sort(heap_sort, random_reversed_sorted_vector,
              "heap_sort_reversed_sorted_results.txt",
              min_size, max_size, step);
    std::cout << "Testing heap sort on unsorted arrays...\n";
    test_sort(heap_sort, random_unsorted_vector,
              "heap_sort_unsorted_results.txt",
              min_size, max_size, step);

    std::cout << "Testing merge sort on sorted arrays...\n";
    test_sort(merge_sort, random_sorted_vector,
              "merge_sort_sorted_results.txt", 
              min_size, max_size, step);
     std::cout << "Testing merge sort on reversed sorted arrays...\n";
    test_sort(merge_sort, random_reversed_sorted_vector,
              "merge_sort_reversed_sorted_results.txt",
              min_size, max_size, step);
    std::cout << "Testing merge sort on unsorted arrays...\n";
    test_sort(merge_sort, random_unsorted_vector,
              "merge_sort_unsorted_results.txt",
              min_size, max_size, step);


    std::cout << "Done.\n";
    return 0;
}