#include <regex>
#include <regex.h>
#include <iostream>
#include <curl/curl.h>

using namespace::std;


class FileTransfer {

    private:
        CURL *chandle; 
        string def_url = "https://bpa.st/";
        string data = " -d 'code=hotdogs' -d 'lexer=c' -d 'expiry=1day'";
    public:
        int connections;

    FileTransfer() {
        cout << "Handling Constructed...!" << endl;
        chandle = curl_easy_init();
    };

    FileTransfer(string url) {
        cout << "You have passed an alternate URL...!" << endl;
        chandle = curl_easy_init();
        def_url = url;
    };

    void make_connection(void) {
        if (chandle) {
            cout << "Inside connection handling..." << endl;
            CURLcode res;
            curl_easy_setopt(chandle, CURLOPT_URL, def_url.c_str()); 
            curl_easy_setopt(chandle, CURLOPT_POSTFIELDS, data.c_str());
            res = curl_easy_perform(chandle);
            if (res != CURLE_OK) {
                cout << curl_easy_strerror(res) << endl;
            } else {
                cout << "Curl Return: " << res << endl;
            }

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

    string curl_url(argv[1]);
    regex url_regex(R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", REG_EXTENDED);
    smatch url_match_result;
    /*
    if (regex_match(curl_url, url_match_result, url_regex)) {
        FileTransfer *ft = new FileTransfer(curl_url);
        ft->make_connection();
    } else {
        FileTransfer *ft = new FileTransfer();
        ft->make_connection();
    };
    */
    FileTransfer *ft = new FileTransfer();
    ft->make_connection();
    
    return 0;
}

