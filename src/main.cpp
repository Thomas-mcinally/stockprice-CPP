#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please provide one stock ticker\n");
        printf("Example: stockprice tsla\n");
        return 0;
    }
    std::string ticker = argv[1];

    httplib::Client cli("https://query2.finance.yahoo.com");
    cli.enable_server_certificate_verification(false); // Want to distribute as static binary
    std::string url = "/v8/finance/chart/" + ticker + "?interval=1d&range=30d";
    
    auto res = cli.Get(url);

    printf("Status code: %d\n", res->status);
    printf("Body: %s\n", res->body.c_str());
    return 0;
}