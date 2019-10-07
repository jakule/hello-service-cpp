#include <csignal>
#include <handler.hpp>
#include <memory>
#include <thread>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;
static bool interrupt = false;
std::condition_variable cv;

void signal_handler(int signum) {
  interrupt = true;
  cv.notify_one();
}

void on_initialize(const string_t& address) {
  uri_builder uri(address);

  auto addr = uri.to_uri().to_string();
  g_httpHandler = std::make_unique<handler>(addr);
  g_httpHandler->open().wait();

  ucout << utility::string_t(U("Listening for requests at: ")) << addr
        << std::endl;
}

void on_shutdown() { g_httpHandler->close().wait(); }

int main(int argc, char* argv[]) {
  utility::string_t port = U("34568");
  if (argc == 2) {
    port = argv[1];
  }

  utility::string_t address = U("http://0.0.0.0:");
  address.append(port);

  on_initialize(address);

  signal(SIGINT, signal_handler);

  std::cout << "Press Ctrl + C to exit." << std::endl;
  std::mutex m;
  std::unique_lock ul(m);
  cv.wait(ul, []() { return interrupt; });
  std::cout << "Closing app..." << std::endl;

  on_shutdown();
  return 0;
}