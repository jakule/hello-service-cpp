#include <handler.hpp>

handler::handler() {
  // ctor
}

handler::handler(utility::string_t url) : m_listener(url) {
  m_listener.support(methods::GET, std::bind(&handler::handle_get, this,
                                             std::placeholders::_1));
  m_listener.support(methods::PUT, std::bind(&handler::handle_put, this,
                                             std::placeholders::_1));
  m_listener.support(methods::POST, std::bind(&handler::handle_post, this,
                                              std::placeholders::_1));
  m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this,
                                             std::placeholders::_1));
}
handler::~handler() {
  // dtor
}

void handler::handle_error(pplx::task<void>& t) {
  try {
    t.get();
  } catch (...) {
    // Ignore the error, Log it if a logger is available
  }
}

//
// Get Request
//
void handler::handle_get(http_request message) {
  ucout << message.to_string() << endl;

  auto response = json::value::object();
  response["status"] = json::value::string("ready");
  response["version"] = json::value::string("0.1.1");
  message.reply(status_codes::OK, response);
};

//
// A POST request
//
void handler::handle_post(http_request message) {
  ucout << message.to_string() << endl;

  string rep = U("not implemented yet");
  message.reply(status_codes::NotImplemented, rep);
};

//
// A DELETE request
//
void handler::handle_delete(http_request message) {
  ucout << message.to_string() << endl;
  string rep = U("not implemented yet");
  message.reply(status_codes::NotImplemented, rep);
};

//
// A PUT request
//
void handler::handle_put(http_request message) {
  ucout << message.to_string() << endl;
  string rep = U("not implemented yet");
  message.reply(status_codes::NotImplemented, rep);
};
