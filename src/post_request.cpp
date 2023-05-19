#include "../include/includes.hpp"

using namespace std;

string PostRequest::get_request() {
    compute_request();
    return computed_request;
}

void PostRequest::set_host(string host) {
    this->host = host;
}

void PostRequest::set_url(string url) {
    this->url = url;
}

void PostRequest::set_login(string login) {
    this->login = login;
}

void PostRequest::set_password(string password) {
    this->password = password;
}

void PostRequest::set_content_type(string content_type) {
    this->content_type = content_type;
}

void PostRequest::compute_request() {
    if (computed_request != "") {
        return;
    }

    /*Fill the json*/
    map<string, string> data = {
        {"password", password},
        {"username",login} 
    };
    
    string content = Helpers::generate_json(data); 

    computed_request += "POST " + url + "\r\n";
    computed_request += "Host: " + host + "\r\n";
    computed_request += "Content-Type: " + content_type + "\r\n";
    computed_request += "Content-Length: " + to_string(content.length()) + "\r\n";
    computed_request += "\r\n";
    computed_request += content;

}






