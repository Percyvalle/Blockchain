#pragma once

#include <string>
#include <sstream>

#include "utils.hpp"

class Transaction final {
private:
    std::string m_hash;
    std::string m_in;
    std::string m_out;
    std::string m_amount;
public:
    Transaction() = default;
    Transaction(const std::string _amount, const std::string _in, const std::string _out)
        :   m_amount(_amount),
            m_in(_in), m_out(_out) { m_hash = calculateHash(); };

    inline const std::string getHash() const { return m_hash; }
private:
    inline std::string calculateHash(){return Utils::sha256(m_amount + m_in + m_out);};
};