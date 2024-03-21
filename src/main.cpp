#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/nlohmann_json/json.hpp"
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

struct TickerStatistics {
    std::string ticker;
    std::string currency;
    double current_price;
    double percentage_change_1day;
    double percentage_change_7day;
    double percentage_change_30day;
};

double calculate_percentage_price_change_over_n_days(int n, std::vector<int> timestamps, std::vector<double> closing_prices) {
    double current_price = closing_prices.back();
    double price_n_days_ago;

    std::time_t now_timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t start_timestamp  = now_timestamp - 24*60*60*n;

    if (timestamps[0] >= start_timestamp) {
        printf("Need more historic data to calculate percentage change over %d days.\n", n);
        return 0;
    }

    int i = 0;
    while (i < timestamps.size()) {
        if (timestamps[i] >= start_timestamp) break;
        i++;
    }
    price_n_days_ago = closing_prices[i-1];
    double percentage_change = 100 * (current_price - price_n_days_ago) / price_n_days_ago;
    return percentage_change;
}

TickerStatistics get_ticker_statistics(const std::string& ticker) {
    httplib::Client cli("https://query2.finance.yahoo.com");
    cli.enable_server_certificate_verification(false); // Want to distribute as static binary
    std::string path = "/v8/finance/chart/" + ticker + "?interval=1d&range=30d";
    auto res = cli.Get(path.c_str());
    if (res->status == 404){
        printf("The ticker %s is not listed on Yahoo Finance.\n", ticker.c_str());
        return TickerStatistics{}; // RAISE INSTEAD
    }

    nlohmann::json response_json = nlohmann::json::parse(res->body);
    std::string currency = response_json["chart"]["result"][0]["meta"]["currency"];
    std::vector<double> closing_prices = response_json["chart"]["result"][0]["indicators"]["quote"][0]["close"];
    std::vector<int> timestamps = response_json["chart"]["result"][0]["timestamp"];

    double current_price = closing_prices.back();

    double percentage_change_30day = calculate_percentage_price_change_over_n_days(30, timestamps, closing_prices);
    double percentage_change_7day = calculate_percentage_price_change_over_n_days(7, timestamps, closing_prices);
    double percentage_change_1day = calculate_percentage_price_change_over_n_days(1, timestamps, closing_prices);

    return TickerStatistics{ticker, currency, current_price, percentage_change_1day, percentage_change_7day, percentage_change_30day};
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

    for(const std::string &ticker : tickers) {
        TickerStatistics statistics = get_ticker_statistics(ticker);
        printf("%s -- Current price: %.2f %s -- Daily change: %.2f%%, 7-day change: %.2f%%, 30-day change: %.2f%%\n", ticker.c_str(), statistics.current_price, statistics.currency.c_str(), statistics.percentage_change_1day, statistics.percentage_change_7day, statistics.percentage_change_30day);

    }

    return 0;
}

