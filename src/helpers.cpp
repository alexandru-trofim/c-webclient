#include "../include/includes.hpp"

using namespace std;

buffer Helpers::buffer_init(void)
{
    buffer buffer;

    buffer.data = NULL;
    buffer.size = 0;

    return buffer;
}

void Helpers::buffer_destroy(buffer *buffer)
{
    if (buffer->data != NULL) {
        free(buffer->data);
        buffer->data = NULL;
    }

    buffer->size = 0;
}

int Helpers::buffer_is_empty(buffer *buffer)
{
    return buffer->data == NULL;
}

void Helpers::buffer_add(buffer *buffer, const char *data, size_t data_size)
{
    if (buffer->data != NULL) {
        buffer->data = (char *)realloc(buffer->data, (buffer->size + data_size) * sizeof(char));
    } else {
        buffer->data = (char *)calloc(data_size, sizeof(char));
    }

    memcpy(buffer->data + buffer->size, data, data_size);

    buffer->size += data_size;
}

int Helpers::buffer_find(buffer *buffer, const char *data, size_t data_size)
{
    if (data_size > buffer->size)
        return -1;

    size_t last_pos = buffer->size - data_size + 1;

    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;

        for (j = 0; j < data_size; ++j) {
            if (buffer->data[i + j] != data[j]) {
                break;
            }
        }

        if (j == data_size)
            return i;
    }

    return -1;
}

int Helpers::buffer_find_insensitive(buffer *buffer, const char *data, size_t data_size)
{
    if (data_size > buffer->size)
        return -1;

    size_t last_pos = buffer->size - data_size + 1;

    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;

        for (j = 0; j < data_size; ++j) {
            if (tolower(buffer->data[i + j]) != tolower(data[j])) {
                break;
            }
        }

        if (j == data_size)
            return i;
    }

    return -1;
}

string Helpers::generate_json (map<string, string> &data) {
    string stream;

    stream += "{";

    bool first = true;

    for (const auto& pair : data) {
        if (!first) {
            stream += ",";
        }
        stream += "\"" + pair.first + "\":\"" + pair.second + "\"";
        first = false;
    }
    stream += "}";
    return stream;

}

int Helpers::open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag) {
    struct sockaddr_in serv_addr;
    int sockfd = socket(ip_type, socket_type, flag);
    if (sockfd < 0) {
        cout << "ERROR opening socket\n";
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = ip_type;
    serv_addr.sin_port = htons(portno);
    inet_aton(host_ip, &serv_addr.sin_addr);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        cout << "ERROR connecting to socket\n";
        exit(1);
    }

    return sockfd;
}

void Helpers::close_connection(int sockfd) {
    close(sockfd);
}

void Helpers::send_to_server(int sockfd, char *message) {
    int bytes, sent = 0;
    int total = strlen(message);

    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0) {
            cout << "ERROR writing message to socket\n";
            exit(1);
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

char* Helpers::receive_from_server(int sockfd)
{
    char response[BUFLEN];
    buffer buffer = buffer_init();
    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0){
            cout << "ERROR reading response from socket\n";
            return NULL;
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
        
        header_end = buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start = buffer_find_insensitive(&buffer, CONTENT_LENGTH, CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.data + content_length_start, NULL, 10);
            break;
        }
    } while (1);
    size_t total = content_length + (size_t) header_end;
    
    while (buffer.size < total) {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0) {
            cout << "ERROR reading response from socket\n";
            return NULL;
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
    }
    buffer_add(&buffer, "", 1);
    return buffer.data;
}

string Helpers::extract_cookie(char* http_response) {
    string str(http_response);
    size_t len = 0;

    size_t pos = str.find("connect.sid=");

    if (pos != string::npos) {
        /*skip connect.sid=*/
        pos += sizeof("connect.sid=") - 1;
        while (str[pos + len] != ' ') {
            len++;
        }
    } else {
        /*There is no session cookie(No such user or wrong pass)*/
        return string();
    }

    /*Extract the cookie from the response*/ 
    return str.substr(pos, len - 1);
}






















