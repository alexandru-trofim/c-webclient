#include "../include/includes.hpp"





int main() {

    Client client;


    client.run_client();

        // if (command == "register") {
        //     string login, pass;
        //     cout << "username=";
        //     cin >> login;
        //     cout << "password=";
        //     cin >> pass;
        //     int fd = Helpers::open_connection("34.254.242.81",
        //                                     8080,
        //                                     AF_INET,
        //                                     SOCK_STREAM,
        //                                     0);
        //     string req= PostBuilder()
        //                 .setHost("34.254.242.81")
        //                 .setUrl("/api/v1/tema/auth/register")
        //                 .setContentType("application/json")
        //                 .setLogin(login)
        //                 .setPassword(pass)
        //                 .build()
        //                 .get_request();
        //     cout << req;
        //     char requestData[req.size() + 1];  // +1 for null terminator
        //     strcpy(requestData, req.data());

        //     Helpers::send_to_server(fd, requestData);

        //     char* res = Helpers::receive_from_server(fd);

        //     cout << endl << res;
        // }


    return 0;
}