#include <regex>
#include <iostream>
#include <curl/curl.h>

using namespace::std;


class FileTransfer {

    private:
        CURL *chandle; 
        char *def_url = "https://bpa.st";

    public:
        int connections;

    FileTransfer() {
        cout << "Handling Constructed...!" << endl;
        chandle = curl_easy_init();
    };

    FileTransfer(char *url) {
        cout << "You have passed an alternate URL...!" << endl;
        chandle = curl_easy_init();
        def_url = url;
    };

    void make_connection(void) {
        if (chandle) {
            CURLcode res;
            curl_easy_setopt(chandle, CURLOPT_URL, def_url); 
            res = curl_easy_perform(chandle);
            curl_easy_cleanup(chandle);
        }    
    };
};

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Pass an URL..." << endl;
        exit(0);
    }

    char *curl_url = argv[1];
    // Pass some type of check on URL...
    regex url_regex("R(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", REG_EXTENDED);
    smatch url_match_result;
    if (regex_match(curl_url, url_match_result, url_regex)) {
        FileTransfer *ft = new FileTransfer(curl_url);
        ft->make_connection();
    } else {
        FileTransfer *ft = new FileTransfer();
        ft->make_connection();
    };
    
    return 0;
}

