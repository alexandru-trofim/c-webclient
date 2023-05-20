
using namespace std;



class Client {

public:
    int fd;
    string ip;
    string session_cookie;
    string jwt;

public:
    void run_client();
    void register_command();
    void login_command();
    void get_acces_lib_command();
    void get_all_books();
    void add_book();
    void get_book();
    void delete_book();
    void logout();
    char* send_req_recv_res(string &req);

};