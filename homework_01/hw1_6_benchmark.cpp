// hw1_q6_batch.cpp
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <cstdint>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // sizes to test (user requested)
    const std::vector<std::size_t> sizes = {
        100'000'000ULL,
         10'000'000ULL,
          1'000'000ULL,
            100'000ULL,
             10'000ULL,
              1'000ULL
    };

    const int trials = 20; // number of lookups to average per size

    // RNG for choosing random lookup target
    std::mt19937_64 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());

    // Accumulators for overall averages (only include sizes where list was built)
    double overall_vector_sum_ms = 0.0;
    double overall_list_sum_ms = 0.0;
    std::size_t overall_vector_counts = 0;
    std::size_t overall_list_counts = 0;

    for (std::size_t max_size : sizes) {
        std::cout << "====================\n";
        std::cout << "Testing max_size = " << max_size << "\n";

        // Estimate memory used by a std::list node: int + two pointers
        // (this is an approximation; real node size depends on implementation)
        std::uint64_t approx_node_bytes = sizeof(int) + 2 * sizeof(void*);
        long double estimated_list_bytes = (long double)approx_node_bytes * (long double)max_size;
        long double estimated_list_mb = estimated_list_bytes / (1024.0L * 1024.0L);

        std::cout << "Estimated list memory (approx): " << estimated_list_mb << " MB\n";

        // Heuristic safety threshold: skip building list if estimated > 2048 MB (2 GB)
        const long double LIST_MEMORY_THRESHOLD_MB = 2048.0L;

        bool build_list = (estimated_list_mb <= LIST_MEMORY_THRESHOLD_MB);
        if (!build_list) {
            std::cout << "WARNING: estimated list memory > " << LIST_MEMORY_THRESHOLD_MB << " MB. ";
            std::cout << "Skipping construction of std::list for this size to avoid OOM.\n";
        }

        // Containers
        std::vector<int> integers_vector;
        std::list<int> integers_list;

        integers_vector.reserve(max_size); // avoid reallocation noise for vector

        std::cout << "Filling containers...\n";
        for (std::size_t i = 0; i < max_size; ++i) {
            integers_vector.push_back(static_cast<int>(i));
            if (build_list) integers_list.push_back(static_cast<int>(i));
        }

        // prepare random distribution for lookups in [0, max_size-1]
        std::uniform_int_distribution<std::size_t> dist(0, max_size - 1);

        // store trial timings
        std::vector<double> vector_times_ms;
        std::vector<double> list_times_ms;
        vector_times_ms.reserve(trials);
        if (build_list) list_times_ms.reserve(trials);

        std::cout << "Running " << trials << " lookup trials...\n";
        for (int t = 0; t < trials; ++t) {
            std::size_t target = dist(rng);

            // measure vector find
            auto sv = std::chrono::high_resolution_clock::now();
            auto itv = std::find(integers_vector.begin(), integers_vector.end(), static_cast<int>(target));
            auto ev = std::chrono::high_resolution_clock::now();
            double v_ms = std::chrono::duration<double, std::milli>(ev - sv).count();
            vector_times_ms.push_back(v_ms);
            bool found_in_vector = (itv != integers_vector.end()); // use result

            // measure list find if built
            if (build_list) {
                auto sl = std::chrono::high_resolution_clock::now();
                auto itl = std::find(integers_list.begin(), integers_list.end(), static_cast<int>(target));
                auto el = std::chrono::high_resolution_clock::now();
                double l_ms = std::chrono::duration<double, std::milli>(el - sl).count();
                list_times_ms.push_back(l_ms);
                bool found_in_list = (itl != integers_list.end());

                if (!found_in_vector || !found_in_list) {
                    std::cerr << "ERROR: element not found in one of the containers (this should not happen)\n";
                }
            } else {
                // still sanity-check vector only
                if (!found_in_vector) {
                    std::cerr << "ERROR: element not found in vector (this should not happen)\n";
                }
            }
        } // end trials

        // compute per-size averages
        double avg_v = std::accumulate(vector_times_ms.begin(), vector_times_ms.end(), 0.0) / vector_times_ms.size();
        std::cout << "Average vector find time over " << vector_times_ms.size() << " trials: " << avg_v << " ms\n";

        overall_vector_sum_ms += avg_v;
        overall_vector_counts++;

        if (build_list) {
            double avg_l = std::accumulate(list_times_ms.begin(), list_times_ms.end(), 0.0) / list_times_ms.size();
            std::cout << "Average list find time over " << list_times_ms.size() << " trials:   " << avg_l << " ms\n";
            overall_list_sum_ms += avg_l;
            overall_list_counts++;
        } else {
            std::cout << "List timings skipped for this size.\n";
        }

        // free memory before next iteration
        integers_vector.clear();
        integers_vector.shrink_to_fit();
        if (build_list) {
            integers_list.clear();
        }

        std::cout << "Done with size " << max_size << "\n\n";
    } // end sizes loop

    // print overall averages (across sizes that were tested)
    if (overall_vector_counts > 0) {
        std::cout << "=== Overall average across " << overall_vector_counts << " sizes (vector) ===\n";
        std::cout << (overall_vector_sum_ms / (double)overall_vector_counts) << " ms\n";
    }
    if (overall_list_counts > 0) {
        std::cout << "=== Overall average across " << overall_list_counts << " sizes (list) ===\n";
        std::cout << (overall_list_sum_ms / (double)overall_list_counts) << " ms\n";
    } else {
        std::cout << "No list timings were produced (list was skipped for very large sizes).\n";
    }

    return 0;
}
