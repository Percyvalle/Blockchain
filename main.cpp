#include <iostream>
#include "src/Core/ledger.hpp"

int main(int, char**) {
    Blockchain blockchain;
    blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);
    blockchain.printBlockchain();
    spdlog::info("Valid: {}", blockchain.isValid());
    return 0;
}
