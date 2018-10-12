#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>


template <typename T, class KeyFunc>
auto schwartzianTransf(
    const std::vector<T>& input,
    const KeyFunc& keyFunc) -> std::vector<T>
{
    typedef decltype(std::declval<KeyFunc>()(std::declval<T>())) Key;
    typedef std::pair<Key, const T*> Ext;

    // extend
    std::vector<Ext> tmp;
    for (const T& t : input) {
        tmp.emplace_back(keyFunc(t), &t);
    }

    // sort by extension
    auto lessFunc = [](const Ext& lhs, const Ext& rhs) -> bool {
        return (lhs.first < rhs.first);
    };

    std::sort(tmp.begin(), tmp.end(), lessFunc);

    // prune
    std::vector<T> out;
    for (const Ext& p : tmp) {
        out.emplace_back(std::move(*p.second));
    }

    return out;
}


int main()
{
    // test Schwartzian transform

    std::vector<std::string> unsorted = {"========", "aaaa", "a", "aaa", "aaaaa", "aa", "aaaaaa", "" };

    auto sorted =
        schwartzianTransf(unsorted, [](const std::string& s) { return s.size(); });

    for (auto &s : sorted)
    {
        std::cout <<  s << "\n";
    }

    // more complicated key function:

    std::vector<std::string> treeParts = {"xxxxxxxxx", "  xxxxx  ", "    x   ", "   xxx   ", " xxxxxxx ", "" };

    sorted =
        schwartzianTransf(treeParts,
                          [](const std::string& s)
                          {
                              auto count =
                                std::count_if(s.begin(), s.end(),
                                              [] (const char c)
                                              {
                                                  return c != ' ';
                                              });

                              return count;
                            });

    for (auto &s : sorted)
    {
        std::cout <<  s << "\n";
    }

    std::cout << "    N   \n";
    std::cout << "----------\n\n";

    return 0;
}
