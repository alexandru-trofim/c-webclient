using namespace std;

typedef struct buffer {
    char *data;
    size_t size;
} buffer;


class Helpers {

public: 
    static string  generate_json(map <string, string> &data);
    static int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag);
    static void close_connection(int sockfd);
    static char* receive_from_server(int sockfd);
    static void send_to_server(int sockfd, char *message);
    static string extract_cookie(char* http_response);

    // initializes a buffer
    static buffer buffer_init(void);

    // destroys a buffer
    static void buffer_destroy(buffer *buffer);

    // adds data of size data_size to a buffer
    static void buffer_add(buffer *buffer, const char *data, size_t data_size);

    // checks if a buffer is empty
    static int buffer_is_empty(buffer *buffer);

    // finds data of size data_size in a buffer and returns its position
    static int buffer_find(buffer *buffer, const char *data, size_t data_size);

    // finds data of size data_size in a buffer in a
    // case-insensitive fashion and returns its position
    static int buffer_find_insensitive(buffer *buffer, const char *data, size_t data_size);


};