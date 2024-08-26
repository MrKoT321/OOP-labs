#include "HtmlDecode.h"

namespace htmlDecode
{
    std::map<std::string, std::string> htmToView = {
        {"&gt;", ">"},
        {"&lt;", "<"},
        {"&amp;", "&"},
        {"&apos;", "'"},
        {"&quot;", "\""}
    };

    const size_t maxEncodedLen = std::max_element(
        htmToView.begin(),
        htmToView.end(),
        [](const auto& x, const auto& y) {
            return x.first.size() < y.first.size();
        }
    )->first.size();
}

// сложно и непонятно
// избавиться от параметра pos, подавать срез строки
std::string FindReplacedHtmlString(size_t pos, std::string_view text)
{
    size_t textLen = text.length();
    std::string replaced;
    char encodedEndsSymb = ';';
    char nextSymb;
    auto maxEncodedLen = htmlDecode::maxEncodedLen;

    for (int i = 0; i < maxEncodedLen; i++)
    {
        if (pos + i == textLen)
        {
            return replaced;
        }

        replaced += text[pos + i];
        if (text[pos + i] == encodedEndsSymb)
        {
            return htmlDecode::htmToView[replaced].empty()
                ? replaced
                : htmlDecode::htmToView[replaced];
        }
    }

    return replaced;
}

std::string HtmlDecode(std::string_view text)
{
    if (text.empty())
    {
        return "";
    }

    std::string result;
    size_t pos = 0;
    size_t lastPos = 0;
    char encodedStartsSymb = '&';

    while (pos != std::string_view::npos)
    {
        pos = text.find_first_of(encodedStartsSymb, lastPos);
        result.append(text, lastPos, pos - lastPos);
        if (pos != std::string_view::npos)
        {
            // сложно и непонятно
            auto replaced = FindReplacedHtmlString(pos, text.substr(pos));
            result.append(replaced);
            lastPos = pos + replaced.length();
        }
    }

    return result;
}