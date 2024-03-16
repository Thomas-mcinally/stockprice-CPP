#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"


int main(int argc, char** argv) {


    // HTTPS
    httplib::Client cli("https://query2.finance.yahoo.com");
    auto res = cli.Get("/v8/finance/chart/BTC-USD?interval=1d&range=30d");
    std::cout << "Status code: " << res->status << '\n';
    std::cout << "Text: " << res->body << '\n';
    return 0;
}