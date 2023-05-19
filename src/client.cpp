#include "../include/includes.hpp"

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

        } else if (command == "get_books") {

        } else if (command == "get_book") {

        } else if (command == "delete_book") {

        } else if (command == "logout") {

        } else if (command == "exit") {

            return;            
        } else {
           cout << "Wrong command\n";
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

    /*Validate credentials*/

    /*Open connection, Generate request, and send it*/
    int fd = Helpers::open_connection("34.254.242.81",
                                    8080,
                                    AF_INET,
                                    SOCK_STREAM,
                                    0);
    string req= PostBuilder()
                .setHost("34.254.242.81")
                .setUrl("/api/v1/tema/auth/register")
                .setContentType("application/json")
                .setLogin(login)
                .setPassword(pass)
                .build()
                .get_request();
    cout << req;
    char requestData[req.size() + 1];  // +1 for null terminator
    strcpy(requestData, req.data());

    Helpers::send_to_server(fd, requestData);

    char* res = Helpers::receive_from_server(fd);

    cout << endl << res;

    /*Analyze the response*/
    if (strstr(res, "400 Bad Request") != nullptr) {
        cout << "The username " << login << " is already taken\n";
    } else {
        cout << "200 - OK - Utilizatorul a fost creat cu succes\n";
    }

    Helpers::close_connection(fd);

}

void Client::login_command() {

    string login, pass;

    /*Get credentials*/
    cout << "username=";
    cin >> login;
    cout << "password=";
    cin >> pass;

    /*Validate credentials*/

    /*Open connection, Generate request, and send it*/
    int fd = Helpers::open_connection("34.254.242.81",
                                    8080,
                                    AF_INET,
                                    SOCK_STREAM,
                                    0);
    string req= PostBuilder()
                .setHost("34.254.242.81")
                .setUrl("/api/v1/tema/auth/login")
                .setContentType("application/json")
                .setLogin(login)
                .setPassword(pass)
                .build()
                .get_request();

    cout << req;

    char requestData[req.size() + 1];  // +1 for null terminator
    strcpy(requestData, req.data());

    Helpers::send_to_server(fd, requestData);

    char* res = Helpers::receive_from_server(fd);

    cout << endl << res;

    string cookie = Helpers::extract_cookie(res);

    if (!cookie.empty()) {
        cout << "Login successful\n" << cookie;
    } else {
        cout << "SHIIT, Wrong credentials\n";
    }

    /*Analyze the response*/
    // if (strstr(res, "400 Bad Request") != nullptr) {
    //     cout << "The username " << login << " is already taken\n";
    // } else {
    //     cout << "200 - OK - Utilizatorul a fost creat cu succes\n";
    // }

    Helpers::close_connection(fd);



}