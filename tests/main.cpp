#include "simdjson.h"

using namespace simdjson;

int main(int argc, char** argv) {
    std::string a = "abcd";    
    padded_string padded(a);
    ondemand::parser parser;
    try {

        ondemand::document doc = parser.iterate(padded);
        std::string_view res = doc["notasldfk"].get_string();
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
    }
    


    return 0;
}
