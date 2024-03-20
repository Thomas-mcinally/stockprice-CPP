#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/nlohmann_json/json.hpp"
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

double calculate_percentage_price_change_over_n_days(int n, std::vector<int> timestamps, std::vector<double> closing_prices) {
    double current_price = closing_prices.back();
    double price_on_last_trading_day_n_days_ago;

    auto now = std::chrono::system_clock::now();
    auto date_n_days_ago = now - std::chrono::hours(24*n);
    std::time_t start_timestamp  = std::chrono::system_clock::to_time_t(date_n_days_ago);

    int i = 0;
    while (i < timestamps.size()-1) {
        if (timestamps[i+1] >= start_timestamp) break;
        i++;
    }
    price_on_last_trading_day_n_days_ago = closing_prices[i];
    double percentage_change = 100 * (current_price - price_on_last_trading_day_n_days_ago) / price_on_last_trading_day_n_days_ago;
    return percentage_change;
}

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
        if (res->status == 404){
            printf("The ticker %s is not listed on Yahoo Finance.\n", ticker.c_str());
            continue;
        }

        nlohmann::json response_json = nlohmann::json::parse(res->body);
        std::string currency = response_json["chart"]["result"][0]["meta"]["currency"];
        std::vector<double> closing_prices = response_json["chart"]["result"][0]["indicators"]["quote"][0]["close"];
        std::vector<int> timestamps = response_json["chart"]["result"][0]["timestamp"];

        double current_price = closing_prices.back();

        double percentage_change_30day = calculate_percentage_price_change_over_n_days(30, timestamps, closing_prices);
        double percentage_change_7day = calculate_percentage_price_change_over_n_days(7, timestamps, closing_prices);
        double percentage_change_1day = calculate_percentage_price_change_over_n_days(1, timestamps, closing_prices);

        printf("%s -- Current price: %.2f %s -- Daily change: %.2f%%, 7-day change: %.2f%%, 30-day change: %.2f%%\n", ticker.c_str(), current_price, currency.c_str(), percentage_change_1day, percentage_change_7day, percentage_change_30day);
    }

    return 0;
}

