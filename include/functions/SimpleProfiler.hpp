#ifndef __SIMPLE_PROFILER_HPP___
#define __SIMPLE_PROFILER_HPP___

#include <chrono>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <functions/functions.h>
#include <functional>
#include <iostream>

namespace functions {

class SimpleProfiler {
    public:
        SimpleProfiler(const std::string &file);

        template <typename T> T profileFunction(std::function<T()> func);

        std::string displayStats() const;

        ~SimpleProfiler();

        inline void reset() {
            total_time_ = 0L; 
            times_.clear();
            ofs_.close();
            ofs_.open(filename_);
        }

    protected:
        std::ofstream ofs_;
        std::vector<long> times_;
        long total_time_;
        std::string filename_;
};

SimpleProfiler::SimpleProfiler(const std::string &file_):ofs_(file_),total_time_(0L) {
    
}

SimpleProfiler::~SimpleProfiler() {
    std::cout << "Profiling stats: " << displayStats() << std::endl;
    ofs_.close();
}

template <typename T>  T SimpleProfiler::profileFunction(std::function<T()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    T res;

    res = func();

    auto stop = std::chrono::high_resolution_clock::now();

    times_.push_back((stop - start).count());
    ofs_ << (stop - start).count() << " ";

    return res;
}

template <> void SimpleProfiler::profileFunction<void>(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();

    auto stop = std::chrono::high_resolution_clock::now();

    times_.push_back((stop - start).count());
    ofs_ << (stop - start).count() << " ";
}

std::string SimpleProfiler::displayStats() const {
    std::ostringstream os;

    os << "Total time = " << mean(times_) << "\n";
    os << "N calls: " << times_.size() << "\n";
    if (times_.size() > 0) {
        os << "Mean result = " << mean(times_) << "\n";
    }


    return os.str();
}

} // namespace functions

#endif