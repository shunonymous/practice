#include <iostream>
using namespace std;

template <typename T>
T echo(T pi)
{
    return pi;
}

int main()
{
    int const YUTORI = 3;
    double const PI = 3.14;
    
    double pi1,pi2,pi3;

    pi1 = echo(PI);
    pi2 = echo(YUTORI);
    pi3 = echo<int>(PI);

    cout << pi1 << endl;
    cout << pi2 << endl;
    cout << pi3 << endl;


    cout << PI << endl;

    return 0;

}
