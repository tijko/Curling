#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/link/bridge.h>
#include <iostream>
#include <curl/curl.h>
#include <linux/netlink.h>

using namespace::std;

//#define DEBUG  

class FileTransfer {

    private:
        CURL *chandle; 
        string def_url = "https://bpa.st/";
        string data = " -d 'code=hotdogs' -d 'lexer=c' -d 'expiry=1day'";
    public:
        int connections;

    FileTransfer() {
#ifdef DEBUG
        cout << "Handling Constructed...!" << endl;
#endif
        chandle = curl_easy_init();
    };

    FileTransfer(string url) {
#ifdef DEBUG
        cout << "You have passed an alternate URL...!" << endl;
#endif
        chandle = curl_easy_init();
        def_url = url;
    };

    void make_connection(void) {
        if (chandle) {
#ifdef DEBUG
            cout << "Inside connection handling..." << endl;
#endif
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
#ifdef DEBUG
    cout << "DEBUGGING ENABLED" << endl;
#endif
    if (argc == 2) {
        string curl_url(argv[1]);
        FileTransfer *ft = new FileTransfer(curl_url);
        ft->make_connection();
    } else if (argc > 2) {
        cout << "Invalid Arguments" << endl;
        exit(0);
    } else {
        FileTransfer *ft = new FileTransfer();
        ft->make_connection();
    }
    
    struct nl_sock *sk = nl_socket_alloc();
    struct rtnl_link *link = rtnl_link_alloc();
    struct nl_cache *link_cache;
    struct rtnl_link *ltap;

    string name = "New-Bridge";
    nl_connect(sk, NETLINK_ROUTE);
    rtnl_link_alloc_cache(sk, AF_UNSPEC, &link_cache);

    rtnl_link_set_type(link, "bridge");

    rtnl_link_set_name(link, name.c_str());
    rtnl_link_add(sk, link, NLM_F_CREATE);
    rtnl_link_put(link);
    nl_cache_refill(sk, link_cache);
    link = rtnl_link_get_by_name(link_cache, name.c_str());
    ltap = rtnl_link_get_by_name(link_cache, "TEST-BRIDGE");

    rtnl_link_enslave(sk, link, ltap);
    rtnl_link_is_bridge(link);

    rtnl_link_put(ltap);
    nl_cache_refill(sk, link_cache);
    ltap = rtnl_link_get_by_name(link_cache, name.c_str());

    rtnl_link_get_master(ltap);

    return 0;
}

