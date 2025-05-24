//
// Created by giuse on 24 mag 2025.
//

#ifndef TYPE_HTTP_H
#define TYPE_HTTP_H

#include <duktape.h>
#include <string>

struct HttpResponse
{
    HttpResponse() = default;
    HttpResponse(const int status, const std::string& body) : status(status), body(body) {};

    int status;
    std::string body;
};

namespace duk {
    class Context;

    template <>
    struct Type<HttpResponse> {
        static void push(Context &ctx, HttpResponse const &val) {
            duk_push_object(ctx);

            duk_push_number(ctx, val.status);
            duk_put_prop_string(ctx, -2, "status");

            duk_push_string(ctx, val.body.c_str());
            duk_put_prop_string(ctx, -2, "body");
        }

        static void get(Context &ctx, HttpResponse &val, int index) {
            duk_get_prop_string(ctx, index, "status");
            int status = static_cast<int>(duk_get_number(ctx, -1));
            duk_pop(ctx);

            duk_get_prop_string(ctx, index, "body");
            std::string body = std::string(duk_get_string(ctx, -1));
            duk_pop(ctx);

            val = HttpResponse(status, body);
        }

        static constexpr bool isPrimitive() { return true; }
    };

}

#endif //TYPE_HTTP_H
