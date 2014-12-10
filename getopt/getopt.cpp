#include <iostream>
#include <unistd.h>

using namespace std;
int main(int argc,char** argv)
{
    int i;
    char c;

    for(i=0;i<argc;i++)
    {
	c[i] = getopt(argc,argv,"a,b,c:");
	cout << c[i] << endl;
    }

    return 0;

}
