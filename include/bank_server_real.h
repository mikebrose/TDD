#ifndef _BANKSERVER_REAL_
#define _BANKSERVER_REAL_

#include "bank_server.h"

class BankServerReal : public BankServer {
public: 
    BankServerReal(){};
    virtual ~BankServerReal() {}
    virtual void Connect() {}
    virtual void Disconnect() {}
    virtual void Credit(int account_num, int value) {}
    virtual void Debit(int account_num, int value) {}
    virtual bool DoubleTransaction(int account_num, 
        int val1, int val2) {return true;} 
    virtual int GetBalance(int account_num) {return 2;}
    // virtual int GetBalance(int account_num) {return 1;}
};



#endif