#ifndef HANDLER_H
#define HANDLER_H

#include <cpprest/asyncrt_utils.h>
#include <cpprest/containerstream.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/producerconsumerstream.h>
#include <cpprest/uri.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class handler {
 public:
  handler();
  explicit handler(utility::string_t url);
  virtual ~handler();

  pplx::task<void> open() { return m_listener.open(); }
  pplx::task<void> close() { return m_listener.close(); }

 protected:
 private:
  void handle_get(http_request message);
  void handle_put(http_request message);
  void handle_post(http_request message);
  void handle_delete(http_request message);
  void handle_error(pplx::task<void>& t);
  http_listener m_listener;
};

#endif  // HANDLER_H