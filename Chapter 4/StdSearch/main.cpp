/// -- STL test

#include <QString>
#include <algorithm>
#include <iostream>

int main()
{
    QString text = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor "
                   "incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                   "exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute "
                   "iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                   "Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt "
                   "mollit anim id est laborum. ";
    QString needle ="amet";

    // needs C++17
#if 0
    auto iter = std::search(text.constBegin(), text.constEnd(),
                            std::boyer_moore_searcher(
                              needle.constBegin(), needle.constEnd()));
#endif

    auto iter = std::search(text.constBegin(), text.constEnd(),
                            needle.constBegin(), needle.constEnd());

    if(iter != text.constEnd())
    {
        auto pos = iter - text.constBegin();
        QStringRef rest(&text, pos, text.size() - pos);
        std::cout << "found at offset: " << pos << ", text=" << rest.toString().toStdString() << std::endl;
    }

    // 2nd needele
    needle = "mollit";

    iter = std::search(text.constBegin(), text.constEnd(),
                       needle.constBegin(), needle.constEnd());

    if(iter != text.constEnd())
    {
        auto pos = iter - text.constBegin();
        QStringRef rest(&text, pos, text.size() - pos);
        std::cout << "\nfound at offset: " << pos << ", text=" << rest.toString().toStdString() << std::endl;
    }
}
