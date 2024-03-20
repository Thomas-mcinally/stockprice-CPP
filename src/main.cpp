#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/nlohmann_json/json.hpp"
#include <sstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please provide a comma-delimited list of tickers\n");
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
        std::string path = "/v8/finance/chart/" + ticker + "?interval=1d&range=30d";
        auto res = cli.Get(path);

        nlohmann::json response_json = nlohmann::json::parse(res->body);
        std::vector<double> closing_prices = response_json["chart"]["result"][0]["indicators"]["quote"][0]["close"];
        std::string currency = response_json["chart"]["result"][0]["meta"]["currency"];
        printf("Status code: %d\n", res->status);
        printf("first closing price: %f\n", closing_prices[0]);
        printf("currency: %s\n", currency.c_str());
    }

    return 0;
}

// Todo:
// - add function to extract info from response body
// - use this function in main loop