#include "physics/world.hpp"
#include "physics/ball.hpp"
#include "physics/vec2.hpp"
#include <chrono>
#include <iostream>

int main()
{
    int test_list[] = {100, 500, 1000, 2000};
    for (auto num_of_balls : test_list)
    {
        World test_world;
        test_world.set_size(3000, 3000);
        test_world.add_random_Balls(num_of_balls, {-200, -200}, {200, 200}, 1, 5, 8, 15);

        auto start = std::chrono::high_resolution_clock::now();
        test_world.simulate(300);

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "=== " << num_of_balls << " test ===" << std::endl;
        std::cout << ms << " ms" << std::endl;
    }

    int larger_test_list[] = {5000, 10000};
    for (auto num_of_balls : larger_test_list)
    {
        World test_world;
        test_world.set_size(8000, 8000);
        test_world.add_random_Balls(num_of_balls, {-200, -200}, {200, 200}, 1, 5, 8, 15);

        auto start = std::chrono::high_resolution_clock::now();
        test_world.simulate(300);

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "=== " << num_of_balls << " test ===" << std::endl;
        std::cout << ms << " ms" << std::endl;
    }
}