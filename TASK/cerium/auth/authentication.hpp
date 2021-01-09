#pragma once

#include <iostream>
#include <fstream>

#define LOGURU_WITH_STREAMS 1
#include "../external/loguru.hpp"
#include "../utils/hashutils.hpp"

namespace cerium{

// an enum to represent authentication
enum AUTH_CODE {
    AUTH_FAILED,
    AUTH_SUCCESS
};

/**
 * authenticate_user: authenticates a user given username
 * and password
 * 
 * Args:
 *      Void
 * Returns:
 *  AUTH_CODE: either of AUTH_FAILED | AUTH_SUCCESS
 * **/
auto authenticate_user() -> AUTH_CODE {
    std::string username, password;

    std::cout << "enter username: ";

    std::cin >> username;

    std::cout << "enter password: ";
    std::cin >> password;

    // open the shadowers file
    std::ifstream shadow_file;

    shadow_file.open("shadow", std::ifstream::in);

    if (shadow_file.is_open()) {

        std::string line;
        while(shadow_file >> line) {
            auto split_pivot = line.find_first_of(":");
            auto user = line.substr(0, split_pivot);

            if (user != username) // not this username, continue
                continue;

            // found username
            auto password_hashed = line.substr(split_pivot+1);

            auto input_pass_hashed = cerium::get_SHA3_256(password);

            if (input_pass_hashed == password_hashed) {
                LOG_S(INFO) << username << " authenticated!";

                shadow_file.close();
                return AUTH_SUCCESS;
            }
        }

        LOG_S(ERROR) << "username or password wrong!";

    } else { // cannot open the shadow file
        LOG_S(ERROR) << "error authenticating!";
    }

    shadow_file.close();

    return AUTH_FAILED;
}

// username cannot contain ":"
// BUG: will allow duplicates
// FEATURE: multiple passwords for same username is allowed
auto create_user(std::string username, std::string password) -> int {
    std::ofstream shadow_file;

    shadow_file.exceptions(std::ios::failbit | std::ios::badbit);
    shadow_file.open("shadow", std::ofstream::app | std::ofstream::out);

    if (shadow_file.is_open()) {

        std::string hashed_password = cerium::get_SHA3_256(password);

        std::string username_hashpass = username + ":" + hashed_password;

        shadow_file << username_hashpass << '\n';

        LOG_S(INFO) << "user " << username << " created successfully";

        shadow_file.close();

        return 0;
    } else {
        LOG_S(ERROR) << "error creating user";
     }

    return -1;
}

}
