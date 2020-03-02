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

// TODO: develop it!!
#define PROFILE_METHOD_1(out_file, class_name, function_, type_, arg1) static functions::SimpleProfiler pro(out_file);\
      auto f_ = std::bind(&class_name::function_, this, arg1);\
      pro.profileFunction<type_>(f_);

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
        std::vector<long> stamps_;
        long total_time_;
        std::string filename_;
};

SimpleProfiler::SimpleProfiler(const std::string &file_):ofs_(file_),total_time_(0L) {
    times_.reserve(1000000);
    stamps_.reserve(1000000);
}

SimpleProfiler::~SimpleProfiler() {
    std::cout << "Profiling stats: " << displayStats() << std::endl;
    ofs_.close();
}

template <typename T>  T SimpleProfiler::profileFunction(std::function<T()> func) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    T res = func();

    auto stop = high_resolution_clock::now();

    auto dtn = start.time_since_epoch();

    long d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    times_.push_back(d);

    ofs_ << dtn.count() << " " << d << "\n";

    total_time_ += d;

    return res;
}

template <> void SimpleProfiler::profileFunction<void>(std::function<void()> func) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    func();

    auto stop = high_resolution_clock::now();

    auto dtn = start.time_since_epoch();
    long d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    times_.push_back(d);
    stamps_.push_back(dtn.count());
    ofs_ << dtn.count() << " " << d << "\n";
    total_time_ += d;
}

std::string SimpleProfiler::displayStats() const {
    std::ostringstream os;

    os << "Total time = " << total_time_ << "\n";
    os << "N calls: " << times_.size() << "\n";
    if (times_.size() > 0) {
        os << "Mean result = " << mean(times_) << "\n";
    }

    return os.str();
}

} // namespace functions

#endif