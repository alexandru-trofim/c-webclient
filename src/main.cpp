#include "../include/includes.hpp"

using json = nlohmann::json;



int main() {

    Client client;

    // we deactivate the buffering for low latency
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    client.ip = "34.254.242.81";

    client.run_client();


    return 0;
}