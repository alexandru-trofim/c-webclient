#include "../include/includes.hpp"

RequestBuilder& RequestBuilder::setHost(const std::string& host) {
    request.set_host(host);
    return *this;
}

RequestBuilder& RequestBuilder::setUrl(const std::string& url) {
    request.set_url(url);
    return *this;
}

RequestBuilder& RequestBuilder::setLogin(const std::string& login) {
    request.set_login(login);
    return *this;
}

RequestBuilder& RequestBuilder::setPassword(const std::string& password) {
    request.set_password(password);
    return *this;
}

RequestBuilder& RequestBuilder::setContentType(const std::string& content_type) {
    request.set_content_type(content_type);
    return *this;
}

RequestBuilder& RequestBuilder::setType(const std::string& type) {
    request.set_type(type);
    return *this;
}

RequestBuilder& RequestBuilder::setSessionCookie(const std::string& sessionCookie) {
    request.set_session_cookie(sessionCookie);
    return *this;
}

RequestBuilder& RequestBuilder::setJwt(const std::string& jwt) {
    request.set_jwt(jwt);
    return *this;
}

RequestBuilder& RequestBuilder::setTitle(const std::string& title) {
    request.set_title(title);
    return *this;
}

RequestBuilder& RequestBuilder::setAuthor(const std::string& author) {
    request.set_author(author);
    return *this;
}

RequestBuilder& RequestBuilder::setGenre(const std::string& genre) {
    request.set_genre(genre);
    return *this;
}

RequestBuilder& RequestBuilder::setPageCount(const std::string& page_count) {
    request.set_page_count(page_count);
    return *this;
}

RequestBuilder& RequestBuilder::setPublisher(const std::string& publisher) {
    request.set_publisher(publisher);
    return *this;
}

Request RequestBuilder::build() {
    return request;
}