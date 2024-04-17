#ifndef LAB1_UTILITY_INCLUDE_UTILITY_H
#define LAB1_UTILITY_INCLUDE_UTILITY_H
#include <iostream>
#include <limits>
#include <vector>
#include <utility>
#include <functional>

template<typename T>
T getValue(std::istream& In, std::ostream& Out, std::function<bool(T)> Pred = [](T val){return true;}) {
    T a;
    while(true) {
        In >> a;
        if(In.good() && Pred(a))
            return a;
        else if(In.bad())
            throw std::runtime_error("something gets wrong");
        else if(In.eof())
            throw std::runtime_error("end of file");
        else if(In.fail() || !Pred(a)){
            In.clear();
            In.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Out << "repeat please\n";
        }
    }
}
#endif
