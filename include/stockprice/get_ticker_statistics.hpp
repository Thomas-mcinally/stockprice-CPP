#include <string>
#include <vector>

#ifndef GET_TICKER_STATISTICS_H
#define GET_TICKER_STATISTICS_H
struct TickerStatistics {
    std::string ticker;
    std::string currency;
    double current_price;
    double percentage_change_1day;
    double percentage_change_7day;
    double percentage_change_30day;
};

double calculate_percentage_price_change_over_n_days(int n, std::vector<int> timestamps, std::vector<double> closing_prices);

TickerStatistics get_ticker_statistics(const std::string& ticker);
#endif