#pragma once

#include <string.h>
#include <fort.hpp>
#include <merklecpp.h>

#include "transaction.hpp"

class Block final{
private:
    int m_counter = 0;
    int m_difficulty = 0;
    merkle::Tree m_merkleroot;
    std::string m_hash;
    std::string m_prevhash;
    std::string m_nonce;
    std::string m_timecreation;

    std::vector<Transaction> m_transactions;
public:
    Block() = default;
    ~Block() = default;

    Block(int _difficulty, int _counter, std::string _hash, std::string _prevhash, std::string _nonce, std::string _timecreation, merkle::Tree _merkly)
        :   m_difficulty(_difficulty),
            m_counter(_counter),
            m_hash(_hash),
            m_prevhash(_prevhash),
            m_nonce(_nonce),
            m_merkleroot(_merkly),
            m_timecreation(_timecreation) {};

    inline const std::string getPrevhash() const { return m_prevhash; }
    inline const std::string getHash() const { return m_hash; }
    
    
    inline void printBlock(){
        fort::table blocktable;
        blocktable << fort::header << "BlockNumber: " << m_counter << fort::endr
                   << "Time" << m_timecreation << fort::endr 
                   << "Hash: " << m_hash << fort::endr
                   << "PrevHash: " << m_prevhash << fort::endr
                   << "Difficulty: " << m_difficulty << fort::endr
                   << "Nonce: " << m_nonce << fort::endr;
        std::cout << blocktable.to_string() << std::endl;
    }
};