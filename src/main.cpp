#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include <sstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please provide o comman-delimited list of tickets\n");
        printf("Example: stockprice tsla,btc-usd\n");
        return 0;
    }

    std::stringstream s_stream(argv[1]); 
    std::vector<std::string> tickers;
    std::string ticker;

    while(std::getline(s_stream, ticker, ',')) { 
        tickers.push_back(ticker);
    }

    httplib::Client cli("https://query2.finance.yahoo.com");
    cli.enable_server_certificate_verification(false); // Want to distribute as static binary

    for(std::string &ticker : tickers) {
        std::string url = "/v8/finance/chart/" + ticker + "?interval=1d&range=30d";
        auto res = cli.Get(url.c_str());

        printf("Status code: %d\n", res->status);
        printf("Body: %s\n", res->body.c_str());
        printf("\n%s\n", res->get_header_value("Content-Type").c_str());
    }

    return 0;
}

// Todo:
// - add function to extract info from response body
// - use this function in main loop