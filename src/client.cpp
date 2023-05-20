#include "../include/includes.hpp"

using json = nlohmann::json;

void Client::run_client() {

    string command;

    while (1) {
        /*Receive commands*/
        cin >> command;

        if (command == "register") {
            register_command();
        } else if (command == "login") {
            login_command();
        } else if (command == "enter_library") {
            get_acces_lib_command();
        } else if (command == "get_books") {
            get_all_books();
        } else if (command == "get_book") {
           get_book();
        } else if (command == "add_book") {
            add_book();
        } else if (command == "delete_book") {
            delete_book();
        } else if (command == "logout") {
            logout();
        } else if (command == "exit") {
            return;            
        } else {
           cout << "Wrong command.\n";
        }
    }
}

void Client::register_command() {
    string login, pass;

    /*Get credentials*/
    cout << "username=";
    cin >> login;
    cout << "password=";
    cin >> pass;

    string req= RequestBuilder()
                .setType("POST")
                .setHost(ip)
                .setUrl("/api/v1/tema/auth/register")
                .setContentType("application/json")
                .setLogin(login)
                .setPassword(pass)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    /*Analyze the response*/
    if (strstr(res, "400 Bad Request") != nullptr) {
        cout << "Error! The username " << login << " is already taken.\n";
    } else {
        cout << "200 - OK - User created successfully.\n";
    }
}

void Client::login_command() {

    string login, pass;

    /*Get credentials*/
    cout << "username=";
    cin >> login;
    cout << "password=";
    cin >> pass;

    string req= RequestBuilder()
                .setType("POST")
                .setHost(ip)
                .setUrl("/api/v1/tema/auth/login")
                .setContentType("application/json")
                .setLogin(login)
                .setPassword(pass)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    /*Get the cookie from the http response*/
    session_cookie = Helpers::extract_cookie(res);

    if (!session_cookie.empty()) {
        cout << "Login successful.\n";
    } else {
        cout << "Error! Wrong credentials.\n";
    }

}

void Client::get_acces_lib_command() {

    string req= RequestBuilder()
                .setType("GET")
                .setHost(ip)
                .setUrl("/api/v1/tema/library/access")
                .setSessionCookie(session_cookie)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    if (strstr(res, "200 OK") != nullptr) {
        string string_res(res);
        json json_res = json::parse(string_res.substr(string_res.find("{")));
        jwt = json_res["token"];

        cout << "Library entered succesfully.\n";
    } else {
        cout << "Error!! Cannot enter the library.\n";
    }
}


void Client::get_all_books() {

    string req= RequestBuilder()
                .setType("GET")
                .setHost(ip)
                .setUrl("/api/v1/tema/library/books")
                .setJwt(jwt)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    if (strstr(res, "200 OK") != nullptr) {
        int any_book = 0;
        string json_books(res);
        json json_res = json::parse(json_books.substr(json_books.find("[")));

        for (const auto& book : json_res) {
            int id = book["id"];
            string title = book["title"];

            cout << "id="    << id    << "\n";
            cout << "title=" << title << "\n";
            cout << "\n";

            any_book = 1;
        }
        if (any_book == 0) {
            cout << "This user has no books.\n";
        }
    } else { 
        cout << "Error! You don't have access to the library.\n";
    }

}

void Client::add_book() {
     
    string title, author, genre, page_count, publisher;

    /* Get book info */
    std::cin.ignore();
    std::cout << "title=";
    std::getline(std::cin, title);

    std::cout << "author=";
    std::getline(std::cin, author);

    std::cout << "genre=";
    std::getline(std::cin, genre);

    std::cout << "publisher=";
    std::getline(std::cin, publisher);

    std::cout << "page_count=";
    std::getline(std::cin, page_count);

    // Check if page_count is a valid number
    bool isValidPageCount = false;
    try {
        int page_count_nr = stoi(page_count);
        isValidPageCount = true;
    } catch (const std::exception&) {
        isValidPageCount = false;
    }

    if (!isValidPageCount) {
        cout << "Error! entered page count is not a number\n";
        return;
    }

    string req= RequestBuilder()
                .setType("POST")
                .setHost(ip)
                .setUrl("/api/v1/tema/library/books")
                .setContentType("application/json")
                .setAuthor(author)
                .setGenre(genre)
                .setPublisher(publisher)
                .setPageCount(page_count)
                .setTitle(title)
                .setJwt(jwt)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);


    if (strstr(res, "200 OK") != nullptr) {
        cout << "Book added succesfully.\n";
    } else {
        cout << "Error!! Cannot add book.\n";
    }
}


void Client::get_book() {
    string id;
    cout << "id=";
    cin >> id;

    // Check if id is a valid number
    bool isValidId = false;
    try {
        int id_nr = stoi(id);
        isValidId = true;
    } catch (const std::exception&) {
        isValidId = false;
    }

    if (!isValidId) {
        cout << "Error! entered id is not a number\n";
        return;
    }

    string url = "/api/v1/tema/library/books/" + id;
    string req= RequestBuilder()
                .setType("GET")
                .setHost(ip)
                .setUrl(url)
                .setJwt(jwt)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    if (strstr(res, "200 OK") != nullptr) {

        string json_book(res);
        json json_res = json::parse(json_book.substr(json_book.find("{")));
        cout << "id=" << json_res["id"] << "\n"
            << "title=" << json_res["title"] << "\n"
            << "author=" << json_res["author"] << "\n"
            << "publisher=" << json_res["publisher"] << "\n"
            << "genre=" << json_res["genre"] << "\n"
            << "genre=" << json_res["genre"] << "\n"
            << "page_count=" << json_res["page_count"] << "\n";
    } else {
        cout << "Error! Can't get the book\n";
    }
}

void Client::delete_book() {

    string id;
    cout << "id=";
    cin >> id;

    // Check if id is a valid number
    bool isValidId = false;
    try {
        int id_nr = stoi(id);
        isValidId = true;
    } catch (const std::exception&) {
        isValidId = false;
    }

    if (!isValidId) {
        cout << "Error! entered id is not a number.\n";
        return;
    }

    string url = "/api/v1/tema/library/books/" + id;
    string req= RequestBuilder()
                .setType("DELETE")
                .setHost(ip)
                .setUrl(url)
                .setJwt(jwt)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    if (strstr(res, "200 OK") != nullptr) {

        cout << "Book deleted.\n";

    } else {
        cout << "Error! Book can't be deleted.\n";
    }
}

void Client::logout() {
    string req= RequestBuilder()
                .setType("GET")
                .setHost(ip)
                .setUrl("/api/v1/tema/auth/logout")
                .setSessionCookie(session_cookie)
                .build()
                .get_request();

    char* res = send_req_recv_res(req);

    if (strstr(res, "200 OK") != nullptr) {
        cout << "Logged out.\n";
    } else {
        cout << "Error! Can't log out.\n";
    }

    jwt = "";
    session_cookie = "";
}


char* Client::send_req_recv_res(string &req) {
    /*Open connection, Generate request, and send it*/
    char ip[15];
    strcpy(ip, "34.254.242.81");
    fd = Helpers::open_connection(  ip,
                                    8080,
                                    AF_INET,
                                    SOCK_STREAM,
                                    0);

    char requestData[req.size() + 1];  // +1 for null terminator
    strcpy(requestData, req.data());

    Helpers::send_to_server(fd, requestData);

    char* res = Helpers::receive_from_server(fd);

    Helpers::close_connection(fd); 

    return res;
}

