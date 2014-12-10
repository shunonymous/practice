#include <iostream>
using namespace std;

class aaa
{
private:
    int a;
public:
    int getA() const {return a;}
    int setA(int a){return this->a = a;}
};

int main()
{
    aaa num;

    int b;
    const int c = 5;

    num.setA(c);
    b = num.getA();

    cout << b << endl;

    return 0;
}
