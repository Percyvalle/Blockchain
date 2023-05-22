#pragma once

#include <vector>

#include "block.hpp"
#include "utils.hpp"

class Blockchain{
public:
    enum StateBlockchain{
        UNDEFINED = 0,
        GENESIS = 1,
        JOIN = 2
    };

private:
    std::vector<Block> blockchain;

public:
    Blockchain() = default;
    ~Blockchain() = default;

    void printBlockchain(){ for(Block i : blockchain){i.printBlock();} }

    void initBlockchain(StateBlockchain _state = StateBlockchain::UNDEFINED){
        if(_state == StateBlockchain::JOIN){ 
            spdlog::info("Blockchain initialized"); 
            spdlog::info("Welcome to dplatfrom");
        }
        else if(_state == StateBlockchain::GENESIS){
            spdlog::info("Genesis block generation");
            std::string currenttime = Utils::getTime();
            std::pair<std::string, std::string> genesis = Utils::miningHash(5, 1, std::string(std::string(63, '0') + '1'), currenttime, {"Genesis"});
            blockchain.push_back(Block(5, 1, genesis.second, std::string(std::string(63, '0') + '1'), genesis.first, currenttime, Utils::merkleRootHash({"Genesis"})));
            spdlog::info("Blockchain has been created");
        }
        else{ spdlog::error("Something went wrong during blockchain creation"); }
    }

    bool addBlock(int _difficulty, int _count, std::string _hash, std::string _prevhash, std::string _timecreation, std::string _nonce, std::vector<std::string>& _data){
        
        std::string headerHash = Utils::sha256(_prevhash + _timecreation + _nonce + Utils::merkleRootHash(_data).to_string());
        if((headerHash == _hash) && (_hash.substr(0, _difficulty) == std::string(_difficulty, '0'))){
            blockchain.push_back(Block(_difficulty, _count, _hash, _prevhash, _nonce, _timecreation, Utils::merkleRootHash(_data)));
            return true;
        }

        return false;
    }

    bool isValid(){
        for(int i = 1; i < blockchain.size(); i++){
            if(blockchain[i].getPrevhash() != blockchain[i - 1].getHash()){ return false;}
        }

        return true;
    }
};