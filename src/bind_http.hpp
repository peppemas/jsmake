//
// Created by giuse on 14 dic 2024.
//

#ifndef JSMAKE_BIND_HTTP_HPP
#define JSMAKE_BIND_HTTP_HPP

#include <duktape-cpp/DuktapeCpp.h>
#include <termcolor/termcolor.hpp>

#include <httplib.h>
#include <fstream>
#include <iostream>

namespace HttpBinder {

    class HttpClient {
    public:
        explicit HttpClient() = default;

        // download a file with picohttpclient to a specific path
        int Download(std::string url, std::string filename) {
            // Use regex to parse the URL into protocol, host, and path
            std::regex url_regex(R"((http|https):\/\/([^\/]+)(\/.*)?)");
            std::smatch url_match;

            if (!std::regex_match(url, url_match, url_regex)) {
                std::cerr << termcolor::red << "Invalid URL format: " << url << termcolor::reset << std::endl;
                return -1; // Return error code for invalid URL
            }

            std::string protocol = url_match[1];
            std::string host = url_match[2];
            std::string path = url_match[3].str().empty() ? "/" : url_match[3].str();

            std::cout << termcolor::green << "Downloading from: " << host << " path: " << path << " to: " << filename << termcolor::reset << std::endl;
            httplib::Client cli(host.c_str());
            auto res = cli.Get(path);
            if (res && res->status == 200) {
                std::ofstream ofs(filename, std::ios::binary);
                ofs << res->body;
            }
            return res->status;
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template <class Inspector>
        static void inspect(Inspector &i)
        {
            i.construct(&std::make_shared<HttpClient>);
            i.method("download", &HttpClient::Download);
        }

    private:
        std::stringstream ss;	// ansi string stream
    };

}

#endif //JSMAKE_BIND_HTTP_HPP
