#include <string>
#include <iostream>

class Descriptor{
private:
    std::string id_ = "";
    size_t ta_ = 0;
    size_t ts_ = 0;
public:
    Descriptor() = default;
    Descriptor(const std::string&, size_t, size_t);
    const std::string& getId() const;
    size_t getTa() const;
    size_t getTs() const;
    friend std::istream& operator>>(std::istream&, Descriptor&);
};