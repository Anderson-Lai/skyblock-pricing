#include "file.h"
#include <fstream>
#include "conversions.h"
#include "log.h"
#include <format>
#include <string>
#include "json.h"

int File::CreateFile(const std::string& fileName)
{
    {
        std::ifstream file(fileName);
        if (!file.fail())
        {
            Log::Println(std::format("{} was found, {} will not be recreated", fileName, fileName));
            return 0;
        }
    }

    {
        Log::Println(std::format("{} was not found, {} is being created", fileName, fileName));
        std::ofstream file(fileName);
        if (file.fail())
        {
            Log::Error(std::format("Could not create {}", fileName));
            return 1;
        }
        file << "{\n}";
    }

    return 0;
}

std::string File::ReadFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (file.fail())
    {
        Log::Error(std::format("Could not read the contents of {}, {} does not exist", fileName, fileName));
        return "";
    }

    std::string contents;
    std::string temp;
    while (std::getline(file, temp))
    {
        contents += temp;
    }
    return contents;
}

void File::WritePrices(const std::string& fileName,
        const std::unordered_map<std::wstring, long long>& prices)
{
    std::string contents = File::ReadFile(fileName);
    if (contents == "")
    {
        Log::Error(std::format("An error occurred while reading the contents of {}, writing to {} will not proceed", 
                    fileName, fileName));
        return;
    }

    try 
    {
        Json json(contents);
        std::unordered_map<std::string, long long> filePrices;
        simdjson::ondemand::object& object = json.GetObject();
        for (auto field : object)
        {
            try 
            {
                std::string_view view = field.unescaped_key();
                filePrices[std::string(view)] = field.value().get_int64();
            }
            catch (const simdjson::simdjson_error& e) 
            {
                Log::Error(std::format("An error occurred while reading the prices of {}: {}", fileName, e.what()));
            }
        }
        
        std::mutex mtx;
        {
            // auction house may still be getting scraped 
            // asynchronously in the case of slow internet
            std::unique_lock<std::mutex> lock(mtx);
            for (const auto& [key, value] : prices)
            {
                // values should be clean at this point
                filePrices[Conversions::ToNarrowString(key)] = value;
            }
        }

        std::string fileData = "{\n";
        for (const auto& [key, value] : filePrices)
        {
            fileData += std::format("\t\"{}\": {},\n", key, value);
        }

        // remove the trailing comma and add back the newline character
        if (fileData != "{\n")
        {
            fileData.pop_back();
            fileData.pop_back();
            fileData += "\n";
        }

        // close the JSON object
        fileData += "}";

        // open and write to file 
        std::fstream file(fileName, std::ios::out | std::ios::trunc);
        if (file.fail())
        {
            Log::Error(std::format("Could not open {} to truncate its contents to write new data", fileName));
            return;
        }

        file << fileData;
    }
    catch (const simdjson::simdjson_error& e)
    {
        Log::Error(std::format("An error occurred while writing json data to {}: {}", fileName, e.what()));
    }
}
