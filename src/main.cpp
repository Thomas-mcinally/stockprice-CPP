#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"


int main(int argc, char** argv) {
    httplib::Client cli("https://query2.finance.yahoo.com");
    cli.enable_server_certificate_verification(false); // Want to distribute as static binary
    auto res = cli.Get("/v8/finance/chart/BTC-USD?interval=1d&range=30d");

    printf("Status code: %d\n", res->status);
    return 0;
}