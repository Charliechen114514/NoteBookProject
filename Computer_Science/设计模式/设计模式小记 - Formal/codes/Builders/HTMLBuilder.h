#pragma once

#include <string>
#include <vector>
#include <sstream>

struct LabelStringCreater
{
    static std::string createLabelString(const std::string& label)
    {
        std::ostringstream oss;
        oss << "<" << label << ">";
        return oss.str();
    }

    static std::string createLabelEndString(const std::string& label)
    {
        std::ostringstream oss;
        oss << "</" << label << ">";
        return oss.str();
    }

    static std::string createPlainLabelString(const std::string& label, const std::string& text)
    {
        return  LabelStringCreater::createLabelString(label) + text + 
                LabelStringCreater::createLabelEndString(label) + "\n";
    }

};


struct HTMLElements
{
private:
    friend struct HTMLBuilder;
    HTMLElements() = default;
    HTMLElements(const std::string name, const std::string text):
        name(name), text(text){}
    std::string name, text;
    std::vector<HTMLElements>   elements;
public:
    std::string createString(int indent = 0, bool is_tree = true) const;
};

struct HTMLBuilder
{
    HTMLBuilder(std::string root_name){root.name = root_name;} 
    HTMLBuilder& addChild(const std::string name, const std::string text);

    std::string createString();
private:
    HTMLElements    root;
};

void testThis();

