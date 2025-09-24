#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <chrono>
int main()
{
    // Empty vector and doubly-linked list
    std::vector<int> integers_vector;
    std::list<int> integers_list;

    // Max # of elements
    size_t max_size = 1000;

    std::cout << "inserting values into vector and list..." << std::endl;
    for (size_t i = 0; i < max_size; i++)
    {
        integers_vector.push_back(i);
        integers_list.push_back(i);
    }

    // Choose a random number
    size_t random_number = rand() % max_size + 1;
    std::cout << "random number to find in vector and list is: " << random_number << std::endl;
    
    // Time the search on the vector
    std::cout << "searching in vector..." << std::endl;
    auto start_vector = std::chrono::high_resolution_clock::now();
    std::find(integers_vector.begin(), integers_vector.end(), random_number);
    auto end_vector = std::chrono::high_resolution_clock::now();

    // Time search on the list
    std::cout << "searching in list..." << std::endl;
    auto start_list = std::chrono::high_resolution_clock::now();
    std::find(integers_list.begin(), integers_list.end(), random_number);
    auto end_list = std::chrono::high_resolution_clock::now();

    // Durations in milliseconds
    std::chrono::duration<double, std::milli> vector_time = end_vector - start_vector;
    std::chrono::duration<double, std::milli> list_time = end_list - start_list;

    // Results
    std::cout << "Time took searching " << random_number << " in vector: " << vector_time.count() << "ms" << std::endl;
    std::cout << "Time took searching " << random_number << " in list: " << list_time.count() << "ms" << std::endl;
    
    return 0;
}
