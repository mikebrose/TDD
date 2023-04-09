#ifndef _BANKSERVER_STUB_
#define _BANKSERVER_STUB_

#include "bank_server.h"

class BankServerStub : public BankServer {
public: 
    BankServerStub(){};
    virtual ~BankServerStub() {}
    virtual void Connect() {}
    virtual void Disconnect() {}
    virtual void Credit(int account_num, int value) {}
    virtual void Debit(int account_num, int value) {}
    virtual bool DoubleTransaction(int account_num, 
        int val1, int val2) {return true;} 
    virtual int GetBalance(int account_num) {return 3;}
};



#endif