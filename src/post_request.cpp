#include "../include/includes.hpp"

using namespace std;

string Request::get_request() {
    compute_request();
    return computed_request;
}

void Request::set_type(string type) {
    this->type = type;
}

void Request::set_session_cookie(string session_cookie) {
    this->session_cookie = session_cookie;
}

void Request::set_host(string host) {
    this->host = host;
}

void Request::set_url(string url) {
    this->url = url;
}

void Request::set_login(string login) {
    this->login = login;
}

void Request::set_password(string password) {
    this->password = password;
}

void Request::set_content_type(string content_type) {
    this->content_type = content_type;
}

void Request::set_jwt(string jwt) {
    this->jwt = jwt;
}

void Request::set_title(string title) {
    this->title = title;
}

void Request::set_author(string author) {
    this->author = author;
}

void Request::set_genre(string genre) {
    this->genre = genre;
}

void Request::set_page_count(string page_count) {
    this->page_count = page_count;
}

void Request::set_publisher(string publisher) {
    this->publisher = publisher;
}

void Request::compute_request() {
    if (computed_request != "") {
        return;
    }

    string content; 

    /*Fill the json*/
    if (url.find("/library/books") != string::npos) {
        map<string, string> data = {
            {"title", title},
            {"author", author},
            {"genre", genre},
            {"page_count", page_count},
            {"publisher", publisher}
        };
        content = Helpers::generate_json(data);

    } else {
        map<string, string> data = {
            {"password", password},
            {"username",login} 
        };
        content = Helpers::generate_json(data);
    } 

    computed_request += type + " " + url + "\r\n";

    computed_request += "Host: " + host + "\r\n";

    if (type == "POST") {
        computed_request += "Content-Type: " + content_type + "\r\n";
        computed_request += "Content-Length: " + to_string(content.length()) + "\r\n";

        if (url.find("/library/books") != string::npos) {
            computed_request += "Authorization: Bearer " + jwt + "\r\n";
        }

        computed_request += "\r\n";

        computed_request += content;

    } else if (type == "GET") {
        if (url.find("library/access") != string::npos 
            || url.find("auth/logout") != string::npos) {

            computed_request += "Cookie: connect.sid=" + session_cookie + ";\r\n";
        } else {
            /*Add here: Authorization: Bearer eijjkwuqioueu9182712093801293*/
            computed_request += "Authorization: Bearer " + jwt + "\r\n";
        }
        computed_request += "\r\n";
    } else if (type == "DELETE") {
        computed_request += "Authorization: Bearer " + jwt + "\r\n";
        computed_request += "\r\n";
    }

}






