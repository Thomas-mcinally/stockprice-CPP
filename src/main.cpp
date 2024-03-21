#include <sstream>
#include <string>
#include <vector>
#include "../include/stockprice/get_ticker_statistics.hpp"


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

    for(const std::string& ticker : tickers) {
        TickerStatistics statistics;
        try{
            statistics = get_ticker_statistics(ticker);
        } catch (const std::runtime_error& e) {
            printf("Threw exception when processing ticker %s, error_message: %s",ticker.c_str(), e.what());
            continue;
        }
        printf("%s -- Current price: %.2f %s -- Daily change: %.2f%%, 7-day change: %.2f%%, 30-day change: %.2f%%\n", ticker.c_str(), statistics.current_price, statistics.currency.c_str(), statistics.percentage_change_1day, statistics.percentage_change_7day, statistics.percentage_change_30day);

    }

    return 0;
}
