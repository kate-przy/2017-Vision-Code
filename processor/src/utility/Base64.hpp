//
// Created by cameronearle on 4/12/17.
//

#ifndef PROJECT_BASE64_HPP
#define PROJECT_BASE64_HPP

#include <string>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>

struct Base64 {
static std::string decode(const std::string &val);
static std::string encode(const std::string &val);
};


#endif //PROJECT_BASE64_HPP
