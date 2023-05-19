
using namespace std;



class Client {

    int fd;
    int port;
    string ip;
    string session_cookie;



public:
    void run_client();
    void register_command();
    void login_command();

};