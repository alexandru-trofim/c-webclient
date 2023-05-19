using namespace std;

class PostBuilder {
private:
    PostRequest request;

public:
    PostBuilder& setHost(const std::string& host);
    PostBuilder& setUrl(const std::string& url);
    PostBuilder& setLogin(const std::string& login);
    PostBuilder& setPassword(const std::string& password);
    PostBuilder& setContentType(const std::string& contentType);
    PostRequest build();
};