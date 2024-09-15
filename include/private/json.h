#pragma once
#include "simdjson.h"
#include <string>

class Json
{
public:
    Json(const std::string& representation);
    simdjson::ondemand::object& GetObject();
private:
    simdjson::ondemand::parser m_parser;
    simdjson::ondemand::document m_document;
    simdjson::ondemand::object m_object;
    simdjson::padded_string m_jsonString;
};
