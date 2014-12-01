#include <hayai.hpp>
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>
#include <picojson.h>
#include <fstream>
#include <iterator>
#include <string>

BENCHMARK(RapidJson, ParseFile, 2, 10) {
    FILE *fp = fopen("MOCK_DATA.json" , "r");
    rapidjson::FileStream is(fp);
    rapidjson::Document document;
    document.ParseStream<0>(is);
}

BENCHMARK(PicoJson, ParseFile, 2, 10) {
    std::ifstream fs("MOCK_DATA.json");
    picojson::value v;
    fs >> v;
}

int main() {
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
