#include "HTMLBuilder.h"
#include <iostream>
#include <sstream>


HTMLBuilder& HTMLBuilder::addChild(const std::string name, const std::string text)
{
    HTMLElements h{name, text};
    root.elements.emplace_back(std::move(h));
    return *this;
}

std::string HTMLBuilder::createString()
{
        return root.createString();
}

std::string HTMLElements::createString(int indent, bool is_tree) const
{
        int print_indent = indent;
        std::ostringstream oss;
        while(print_indent-->0) 
            oss << "\t";
        oss << LabelStringCreater::createLabelString(name) << text;
        if(is_tree)
            oss << "\n";
        for(const auto& each_element : elements)
        {
            oss << each_element.createString(indent + 1, 
            !each_element.elements.empty());
        }
        oss << LabelStringCreater::createLabelEndString(name) << "\n";
        return oss.str();
}


void testThis()
{
    HTMLBuilder builder("ul");
    builder.addChild("li", "hello_world").addChild("li", "hello, world");
    std::cout << builder.createString();
}