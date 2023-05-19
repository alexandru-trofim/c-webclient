
using namespace std;

class PostRequest {
private:
    string host;
    string url;
    string login;
    string password;
    string content_type;
    string computed_request;

public: 
    void set_host(string host);
    void set_url(string url);
    void set_login(string login);
    void set_password(string password);
    void set_content_type(string content_type);
    void compute_request();
    string get_request();

};

