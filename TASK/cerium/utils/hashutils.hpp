#pragma once

#include <string>

#include "../external/digestpp/digestpp.hpp"

namespace cerium {

auto get_SHA3_256(std::string password) -> std::string {

    return digestpp::sha3(256).absorb(password).hexdigest();

}

}