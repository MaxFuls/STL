#include "Descriptor/Descriptor.h"
#include <iostream>
#include <limits>
#include <string>

std::istream& operator>>(std::istream& stream, Descriptor& desc) {
    Descriptor tmpDesc;
    std::string line;
    while(stream.good()){
        std::getline(stream, line, ' ');
        auto last = line.begin();
        for(; *last != '/'; ++last);
        tmpDesc.id_ = std::string(line.begin(), last);
        auto first = ++last;
        for(; *last != '/'; ++last);
        try{
            tmpDesc.ta_ = std::stoi(std::string(first, last));
            tmpDesc.ts_ = std::stoi(std::string(++last, line.end()));
        } catch(...) {
            stream.setstate(std::ios::failbit);
        }
        if(tmpDesc.ta_ != 0 && tmpDesc.ts_ != 0){
            desc = std::move(tmpDesc);
            return stream;
        }
    }
    return stream;
}

const std::string& Descriptor::getId() const { return id_;}

size_t Descriptor::getTa() const { return ta_;}

size_t Descriptor::getTs() const { return ts_;}