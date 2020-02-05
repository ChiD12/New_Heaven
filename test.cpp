#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
   int* v = new int(0);
   int* y = v;
   *y = 5;
   //int* p = v;
   //*p = 7;
   
   cout << v;
   
}