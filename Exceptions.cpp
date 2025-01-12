#include "Exceptions.h"

#include <utility>
using namespace std;

Exceptions::Exceptions(string msg) : exception(), _msg{ move(msg) } {}

const string& Exceptions::get_msg() const {
    return this->_msg;
}