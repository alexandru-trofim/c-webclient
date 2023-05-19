#include "../include/includes.hpp"

PostBuilder& PostBuilder::setHost(const std::string& host) {
    request.set_host(host);
    return *this;
}

PostBuilder& PostBuilder::setUrl(const std::string& url) {
    request.set_url(url);
    return *this;
}

PostBuilder& PostBuilder::setLogin(const std::string& login) {
    request.set_login(login);
    return *this;
}

PostBuilder& PostBuilder::setPassword(const std::string& password) {
    request.set_password(password);
    return *this;
}

PostBuilder& PostBuilder::setContentType(const std::string& content_type) {
    request.set_content_type(content_type);
    return *this;
}

PostRequest PostBuilder::build() {
    return request;
}