#ifndef TESTING_MODULE_HPP
#define TESTING_MODULE_HPP

#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>
#include <type_traits>

#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-err58-cpp"

namespace util {

    struct __random {

        __random() = delete;

        inline static std::default_random_engine e{static_cast<unsigned int>(time(nullptr))};
    };

    template<typename _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type* = nullptr>
    _Tp random(const _Tp __min, const _Tp __max) {
        return std::uniform_int_distribution<_Tp>{__min, __max}(__random::e);
    }

    template<typename Dur>
    class timer {

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> start_point, end_point;
        bool running = false;

    public:

        template<typename std::enable_if<std::chrono::__is_duration<Dur>::value, Dur>::type* = nullptr>
        timer();

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> now() const;

        void start();

        void stop();

        int get_measured_time();
    };

    template<typename Dur>
    template<typename std::enable_if<std::chrono::__is_duration<Dur>::value, Dur>::type*>
    timer<Dur>::timer() {
        start_point = std::chrono::high_resolution_clock::now();
        end_point = std::chrono::high_resolution_clock::now();
        running = false;
    }

    template<typename Dur>
    inline std::chrono::time_point<std::chrono::high_resolution_clock, Dur> timer<Dur>::now() const {
        return std::chrono::high_resolution_clock::now();
    }

    template<typename Dur>
    inline void timer<Dur>::start() {
        if (!running) {
            running = true;
            start_point = now();
        } else throw std::runtime_error("Illegal timer state: timer is already running");
    }

    template<typename Dur>
    inline void timer<Dur>::stop() {
        if (running) {
            end_point = now();
            running = false;
        } else throw std::runtime_error("Illegal timer state: timer is not running");
    }

    template<typename Dur>
    inline int timer<Dur>::get_measured_time() {
        Dur time = std::chrono::duration_cast<Dur>(end_point - start_point);
        return time.count();
    }

    typedef std::chrono::duration<double, std::nano> precision_ns;
    typedef std::chrono::duration<double, std::micro> precision_us;
    typedef std::chrono::duration<double, std::milli> precision_ms;
    typedef std::chrono::duration<double, std::ratio<1, 1>> precision_s;

    void generate_random_numbers(int size) {
        std::ofstream data_file("random.txt");
        for (int i = 0; i < size; i++) data_file << random<int>(0, 1000) << " ";
        data_file.close();
    }

    void generate_partially_sorted_numbers_1(int size) {
        std::ofstream data_file("partially_sorted_1.txt");
        const int parts_count = 10;
        const int part_size = size / parts_count;
        const int remainder = size % parts_count;
        for (int i = 0; i < 10; i++) {
            const int l_bound = random(0, 200);
            const int r_bound = random(800, 1000);
            const int this_part_size = part_size + (i == parts_count - 1 ? remainder : 0);
            const double step_size = 1.0 * (r_bound - l_bound) / this_part_size;
            for (int j = 0; j < this_part_size; j++) data_file << l_bound + (int) (j * step_size) << " ";
        }
        data_file.close();
    }

    void generate_partially_sorted_numbers_2(int size) {
        std::ofstream data_file("partially_sorted_2.txt");
        const int part_size = 10;
        const int parts_count = size / part_size;
        const int remainder = size % part_size;
        for (int i = 0; i < parts_count; i++) {
            const int l_bound = random(0, 200);
            const int r_bound = random(800, 1000);
            const int this_part_size = part_size + (i == parts_count - 1 ? remainder : 0);
            const double step_size = 1.0 * (r_bound - l_bound) / this_part_size;
            for (int j = 0; j < this_part_size; j++) data_file << l_bound + (int) (j * step_size) << " ";
        }
        data_file.close();
    }

    int* random_array(int size) {
        std::ifstream data_file("random.txt");
        int* array = new int[size];
        for (int i = 0; i < size; i++) data_file >> array[i];
        data_file.close();
        return array;
    }

    int* partially_sorted_array_1(int size) {
        std::ifstream data_file("partially_sorted_1.txt");
        int* array = new int[size];
        for (int i = 0; i < size; i++) data_file >> array[i];
        data_file.close();
        return array;
    }

    int* partially_sorted_array_2(int size) {
        std::ifstream data_file("partially_sorted_2.txt");
        int* array = new int[size];
        for (int i = 0; i < size; i++) data_file >> array[i];
        data_file.close();
        return array;
    }

    int* ascending_array(int size) {
        int* array = new int[size];
        for (int i = 0; i < size; i++) array[i] = i;
        return array;
    }

    int* descending_array(int size) {
        int* array = new int[size];
        for (int i = 0; i < size; i++) array[i] = size - i - 1;
        return array;
    }

    std::string resolve_prefix(const intmax_t denominator) {
        if (denominator == 1) return "s";
        else if (denominator == 1000) return "m";
        else if (denominator == 1000000) return "u";
        else if (denominator == 1000000000) return "n";
        return "?";
    }
}

namespace test {

    template<template<typename> typename _List, typename _Tp>
    _List<_Tp> initial_data() {
        _List<_Tp> list;
        list.add_at_begin(util::random<int>(0, 10000));
        return list;
    }

    template<typename _Dur>
    void test_run(auto function, util::timer<_Dur> timer) {
        int time = 0;
        for (int j = 0; j < 10; j++) {
            timer.start();
            for (int i = 0; i < 100; i++) function();
            timer.stop();
            time += timer.get_measured_time();
        }
        std::cout << "Took approximately " << time / 10.0 << "us";
    }
}

#endif //TESTING_MODULE_HPP
