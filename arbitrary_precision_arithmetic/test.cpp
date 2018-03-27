#include <iostream>
#include <iomanip>
#include "APInt.h"

using namespace std;

int main(){
	for(int n=0;n<=50;n++) cout<<setw(2)<<n<<"! = "<<APInt::factorial(n)<<endl;
	return 0;
}
