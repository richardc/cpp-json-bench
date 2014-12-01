#include <hayai.hpp>
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>
#include <picojson.h>
#include <json/json.h>
#include <fstream>
#include <iterator>
#include <string>

BENCHMARK(RapidJson, ParseFile, 20, 1) {
    FILE *fp = fopen("MOCK_DATA.json" , "r");
    rapidjson::FileStream is(fp);
    rapidjson::Document document;
    document.ParseStream<0>(is);
}

BENCHMARK(PicoJson, ParseFile, 20, 1) {
    std::ifstream fs("MOCK_DATA.json");
    picojson::value v;
    fs >> v;
}

BENCHMARK(JsonCPP, ParseFile, 20, 1) {
    std::ifstream fs("MOCK_DATA.json");
    Json::Value v;
    Json::Reader r;
    r.parse(fs, v);
}

int main() {
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
