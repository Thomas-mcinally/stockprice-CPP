#include <iostream>
#include <string>
#include <cpr/cpr.h>

int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"https://query2.finance.yahoo.com/v8/finance/chart/BTC-USD?interval=1d&range=30d"},
                                cpr::Header{{"User-Agent", "Mozilla/5.0"}}
                               );
    std::cout << "Status code: " << r.status_code << '\n';
    std::cout << "Text: " << r.text << '\n';
    return 0;
}