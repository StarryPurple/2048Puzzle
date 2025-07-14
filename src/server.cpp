#include "../third_party/Crow/include/crow.h"
#include "include/game_logic.h"
#include <iostream>
#include <stdexcept>
#include <random>

void add_cors_header(crow::response &res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
    res.add_header("Access-Control-Max-Age", "86400");
}

int main() {
    crow::SimpleApp app;

    app.port(18080).multithreaded();

    CROW_ROUTE(app, "/<path>")
        .methods("OPTIONS"_method)([](const crow::request& req, crow::response& res, const std::string& path){
            res.code = 204;
            add_cors_header(res);
            res.end();
        });

    CROW_ROUTE(app, "/")([](){
        crow::response res("Hello from C++ 2048 Backend!");
        add_cors_header(res);
        return res;
    });

    CROW_ROUTE(app, "/init")
    .methods("POST"_method)([&](){
        std::random_device rd;
        std::mt19937 gen(rd());
        PZ2048::Start(4, 4, gen());

        crow::json::wvalue response_json;
        response_json["message"] = "Game initialized successfully!";
        response_json["board"] = PZ2048::SerializeBoard();
        response_json["score"] = PZ2048::Score();
        response_json["steps"] = PZ2048::Steps();

        crow::response res(200, response_json);
        res.add_header("Content-Type", "application/json");
        add_cors_header(res);
        return res;
    });

    CROW_ROUTE(app, "/play")
    .methods("POST"_method)([&](const crow::request& req){
        crow::json::rvalue request_body_json;
        try {
            request_body_json = crow::json::load(req.body);
        } catch (const std::runtime_error& e) {
            crow::json::wvalue error_json;
            error_json["error"] = "Invalid JSON in request body.";
            error_json["details"] = e.what();
            crow::response res(400, error_json);
            res.add_header("Content-Type", "application/json");
            add_cors_header(res);
            return res;
        }

        std::string direction_str;
        if (request_body_json.has("direction") &&
            request_body_json["direction"].t() == crow::json::type::String) {
            direction_str = request_body_json["direction"].s();
        } else {
            crow::json::wvalue error_json;
            error_json["error"] = "Missing or invalid 'direction' in request body.";
            crow::response res(400, error_json);
            res.add_header("Content-Type", "application/json");
            add_cors_header(res);
            return res;
        }

        if (direction_str.empty()) {
            crow::json::wvalue error_json;
            error_json["error"] = "'direction' string cannot be empty.";
            crow::response res(400, error_json);
            res.add_header("Content-Type", "application/json");
            add_cors_header(res);
            return res;
        }

        char dir = direction_str[0];

        bool moved = PZ2048::TryRun(dir);

        crow::json::wvalue response_json;
        response_json["status"] = "success";
        response_json["board"] = PZ2048::SerializeBoard();
        response_json["score"] = PZ2048::Score();
        response_json["steps"] = PZ2048::Steps();
        response_json["moved"] = moved;
        response_json["stuck"] = PZ2048::Stuck();

        crow::response res(200, response_json);
        res.add_header("Content-Type", "application/json");
        add_cors_header(res);
        return res;
    });

    CROW_ROUTE(app, "/undo")
    .methods("POST"_method)([&](){
        bool undone = PZ2048::Undo();

        crow::json::wvalue response_json;
        response_json["status"] = undone ? "success" : "failed";
        response_json["message"] = undone ? "Undo successful." : "No previous move to undo.";
        response_json["board"] = PZ2048::SerializeBoard();
        response_json["score"] = PZ2048::Score();
        response_json["steps"] = PZ2048::Steps();

        crow::response res(200, response_json);
        res.add_header("Content-Type", "application/json");
        add_cors_header(res);
        return res;
    });

    CROW_ROUTE(app, "/board")([](){
        crow::json::wvalue response_json;
        response_json["board"] = PZ2048::SerializeBoard();
        response_json["score"] = PZ2048::Score();
        response_json["steps"] = PZ2048::Steps();
        response_json["stuck"] = PZ2048::Stuck();

        crow::response res(200, response_json);
        res.add_header("Content-Type", "application/json");
        add_cors_header(res);
        return res;
    });

    std::cout << "C++ 2048 Backend listening on port 18080..." << std::endl;
    app.run();
    return 0;
}