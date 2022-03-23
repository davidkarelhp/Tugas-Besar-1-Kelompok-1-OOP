#ifndef __TRIPLET_HPP__
#define __TRIPLET_HPP__

#include <iostream>

template <class T1, class T2, class T3>
class Triplet {
    private:
        T1 first;
        T2 second;
        T3 third;
    public:
        Triplet() {}
        Triplet(T1 first, T2 second, T3 third) {
            this->first = first;
            this->second = second;
            this->third = third;
        }
        T1 getFirst() {
            return this->first;
        }
        T2 getSecond() {
            return this->second;
        }
        T3 getThird() {
            return this->third;
        }

        void setFirst(T1 first) {
            this->first = first;
        }
        void setSecond(T2 second) {
            this->second = second;
        }
        void setThird(T3 third) {
            this->third = third;
        }
};

#endif