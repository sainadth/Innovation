class client
{
private:
    /* data */
    bool publicKeyExchanged = false;
public:
    client();
    ~client();
    void exchangeKey();
    void sendMsg();
    void readMsg();
};