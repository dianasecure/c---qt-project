#pragma once
#include <exception>
#include <string>
using namespace std;

class Exceptions : public exception {
private:
    string _msg;
public:
    Exceptions(string  msg);
    const string& get_msg() const;
};
