#ifndef _ATM_MACHINE_
#define _ATM_MACHINE_

#include "bank_server.h"

class AtmMachine {
private:
    BankServer* bankServer_;

public:
    AtmMachine(BankServer* bankServer) :
        bankServer_(bankServer)  {}

    bool Withdraw(int account_num, int value) {
        bool result = false;

        bankServer_->Connect();

        auto available_balance = bankServer_->GetBalance(account_num);

        if (available_balance >= value) {
            bankServer_->Debit(account_num, value);
            result = true;
        }

        bankServer_->Disconnect();
        return result;
    }
    
    int GetVal() {
        return bankServer_->GetBalance(6);
    }
        // bool result = false;

        // bankServer_
    
};

#endif