#include <iostream>
#include <cstdlib>
#include <fstream>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;
using namespace boost::locale;

int main(int argc,char ** argv)
{

    //TRANSLATORS : Mikukawaii.
    options_description options1(translate("Miku is so cute."));
    options_description options2(translate("How cute is miku?"));
    options_description options3(translate("Miku!Miku!Miku!"));
    
    options1.add_options()
	("cute",translate("Miku is cute."))
	("so-cute",translate("Miku is so cute."))
	;
	
    options2.add_options()
	("cuteness,c",value<int>(),translate("Miku's cuteness."))
	;

    options3.add_options()
	("louise,l",translate("Display the sentence likes \"that\"."))
	;

    variables_map values;

    try
    {
	store(parse_config_file(argc,argv,options2),values);

	ifstream ifs(translate("mikukopipe.txt"));
	store(parse_config_file(ifs,option3),values);

	notify(values);

	if(value.count("option1")){
	    cout << translate("Miku is so cute.") << endl;
	}
	
	cout << translate("Miku's cuteness is ") << values["option3"].as<int>() << "%" << endl;
	
    } catch (exception &e) {
	cout << e.what() << endl;
	cout << translate("By the way, Miku is cute, isn't it?") << endl;
    }

    return 0;
}
