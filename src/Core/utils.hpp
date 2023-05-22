#pragma once

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <spdlog/spdlog.h>
#include <merklecpp.h>

namespace Utils {
    std::string getTime(){
        std::time_t time = std::time(nullptr);
        std::tm* now = std::localtime(&time);
    
        char buffer[128];
        strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
        return buffer;
    }

    std::string sha256(std::string _str){
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, _str.c_str(), _str.size());
        SHA256_Final(hash, &sha256);
        std::stringstream strstream;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            strstream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return strstream.str();
    }

    merkle::Tree::Hash merkleRootHash(const std::vector<std::string>& _data){
            merkle::Tree root;
            for(std::string i : _data){ root.insert(sha256(i)); }
            return root.root();   
    }

    std::pair<std::string, std::string> miningHash(int _difficulty, int _counter, std::string _prevhash, std::string _timecreation, std::vector<std::string> _data){
        std::string hash;
        std::string header = std::to_string(_difficulty) + std::to_string(_counter) + _prevhash + _timecreation + merkleRootHash(_data).to_string();
        for(int i = 0; i < INT_MAX; i++){
            hash = sha256(header + std::to_string(i));
            spdlog::info("Mining... {}", hash);
            if(hash.substr(0, _difficulty) == std::string(_difficulty, '0')){
                return std::make_pair(std::to_string(i), hash);
            }
        }

        return std::make_pair("", "");
    }
}