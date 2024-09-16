#pragma once
#include "item.h"
#include <memory>
#include "simdjson.h"

namespace Parsing
{
    std::vector<std::unique_ptr<Item>> RemoveAuctions(simdjson::ondemand::array& array);
}
