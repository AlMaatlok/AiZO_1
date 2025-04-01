#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <random>
#include <limits>
#include <type_traits>  // for is_integral

using namespace std;
template <typename T>
class NumberGenerator {
public:
    NumberGenerator();
    T generate();
private:
    mt19937 gen;        //random number generator
};

// Implementation of template
template <typename T>
NumberGenerator<T>::NumberGenerator() {
    random_device rd;
    gen = mt19937(rd());
}

template <typename T>
T NumberGenerator<T>::generate() {
    if constexpr (is_integral_v<T>) {
        // if T is int
        T lower_bound = numeric_limits<T>::lowest();
        T upper_bound = numeric_limits<T>::max();

        uniform_int_distribution<T> dis(lower_bound, upper_bound);  // generating

        return dis(gen);
    } else {
        // if T is float or double
        // to avoid infinity using limits
        T lower_bound = numeric_limits<T>::min();
        T upper_bound = numeric_limits<T>::max();

        uniform_real_distribution<T> dis(lower_bound, upper_bound);  //generating

        T result = dis(gen);

        //making sure value is not infinity
        if (result == numeric_limits<T>::infinity() || result == -numeric_limits<T>::infinity()) {
            return numeric_limits<T>::max();
        }

        return result;
    }
}

#endif // NUMBERGENERATOR_H
