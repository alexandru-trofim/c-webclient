using namespace std;

class RequestBuilder{
private:
    Request request;

public:
    RequestBuilder& setHost(const std::string& host);
    RequestBuilder& setUrl(const std::string& url);
    RequestBuilder& setLogin(const std::string& login);
    RequestBuilder& setPassword(const std::string& password);
    RequestBuilder& setContentType(const std::string& contentType);
    RequestBuilder& setType(const std::string& type);
    RequestBuilder& setSessionCookie(const std::string& sessionCookie);
    RequestBuilder& setJwt(const std::string& jwt);
    RequestBuilder& setTitle(const std::string& title);
    RequestBuilder& setAuthor(const std::string& author);
    RequestBuilder& setGenre(const std::string& genre);
    RequestBuilder& setPageCount(const std::string& page_count);
    RequestBuilder& setPublisher(const std::string& publisher);
    Request build();
};