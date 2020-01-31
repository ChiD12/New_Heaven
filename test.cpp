#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
   int v = 0;
   int& y = v;
   v = 5;
   //int* p = v;
   //*p = 7;
   
   cout << y;
   
}