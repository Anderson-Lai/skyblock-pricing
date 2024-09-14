#include "json.h"

Json::Json(const std::string& representation) : m_jsonString(representation)
{
    m_document = m_parser.iterate(m_jsonString);
    m_object = m_document.get_object();
}

simdjson::ondemand::object& Json::GetObject()
{
    return m_object;
}
