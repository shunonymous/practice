#include <iostream>
#include <boost/locale.hpp>

int main()
{
    boost::locale::generator gen;

    gen.add_messages_path("./local");
    gen.add_messages_domain("locale_test");

    std::locale::global(gen(""));
    std::cout.imbue(std::locale());
			
    std::cout << boost::locale::translate("Hello,world!!") << std::endl;

    return 0;
}
