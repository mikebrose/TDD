#ifndef _BANKSERVER_
#define _BANKSERVER_

class BankServer {
public: 
    virtual ~BankServer() {};
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;
    virtual void Credit(int account_num, int value) = 0;
    virtual void Debit(int account_num, int value) = 0;
    virtual bool DoubleTransaction(int account_num, 
        int val1, int val2) = 0;
    virtual int GetBalance(int account_num) = 0;

};



#endif