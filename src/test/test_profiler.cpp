#include <functions/SimpleProfiler.hpp>
#include <cmath>
#include <iostream>

using namespace functions;
using namespace std;

double f(double angle_in) {

    return std::cos(angle_in);
}

int main(int argc, char **argv) {
    unsigned int n_calls = 1000;

    if (argc > 2) {
        n_calls = atoi(argv[2]);
    }
    double angle = 0.0;

    std::string file("profile.txt");
    if (argc > 1) {
        file = argv[1];
    }
    cout << "Exporting file "<< file << ". Number of calls: " << n_calls << endl;

    SimpleProfiler pro(file);

    for (unsigned int i = 0;i < n_calls; i++, angle += 0.01) {
        // std::function<double()> f = std::bind(f, angle);
        auto f_ = std::bind(f, angle);
        double a = pro.profileFunction<double>(f_);
        cout << "Call " << i << ". Input = " << angle << " result: " << a << "\n";
    }

    cout << pro.displayStats() << endl;

}