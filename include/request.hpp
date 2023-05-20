
using namespace std;

class Request {
private:
    string type;
    string host;
    string url;
    string login;
    string password;
    string content_type;
    string computed_request;
    string session_cookie;
    string jwt;
    string title;
    string author;
    string genre;
    string page_count;
    string publisher;

public: 
    /*Setters*/
    void set_type(string type);
    void set_host(string host);
    void set_url(string url);
    void set_login(string login);
    void set_password(string password);
    void set_content_type(string content_type);
    void set_session_cookie(string session_cookie);
    void set_jwt(string jwt);
    void set_title(string title);
    void set_author(string author);
    void set_genre(string genre);
    void set_page_count(string page_count);
    void set_publisher(string publisher);
    /*Generates the request with all the parameters*/
    void compute_request();
    string get_request();

};

