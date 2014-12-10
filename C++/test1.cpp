// -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>
using namespace std;
using namespace boost::program_options;

int main(int argc, char ** argv)
{
    // Architecturing option
    options_description opt("Option");
    opt.add_options()
	("help,h","Displaying help")
	("op", value<string>(),"Kind of operation(add,sub,mul,div)")
	("lhs,L", value<int>()->default_value(100),"Left")
	("rhs,R", value<int>()->default_value(200),"Right");

    // Analize argc/argv and contain result to vm
    variables_map vm;
    store(parse_command_line(argc, argv, opt), vm);
    notify(vm);

    if( vm.count("help") || !vm.count("op") )
	cout << opt << endl; // Displaying help
    else
    {
	string op = vm["op"].as<string>();
	int lhs = vm["lhs"].as<int>();
	int rhs = vm["rhs"].as<int>();
	if( op=="add" ) cout << lhs+rhs << endl;
	if( op=="sub" ) cout << lhs-rhs << endl;
	if( op=="mul" ) cout << lhs*rhs << endl;
	if( op=="div" ) cout << lhs/rhs << endl;
    }
}
