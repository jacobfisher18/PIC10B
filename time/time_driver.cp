/*
#include <iostream>
#include "time.h"

using std::cout;

int main(){
   cout << "*****************************************\n";
   cout << "Welcome to 'San Angel'!\n";
   cout << "[ 1 day = 24 hours, 1 hour = 60 minutes ]\n\n";

   Time a;
   Time b(5);
   Time c(61);
   Time d(47,59);
   Time X(5.0);
   Time Y(1.5);
   Time Z(25.1);

   cout << "a = " << a << "\t";
   cout << "b = " << b << "\t";
   cout << "c = " << c << "\n";
   cout << "d = " << d << "\t";
   cout << "X = " << X << "\t";
   cout << "Y = " << Y << "\n";
   cout << "\t\tZ = " << Z << "\n";


   Time::set_hr_in_day(60);
   Time::set_min_in_hr(24);
   cout << "*****************************************\n";
   cout << "Welcome to the land of the remembered!\n";
   cout << "[ 1 day = 60 hours, 1 hour = 24 minutes ]\n\n";

   cout << "a = " << a << "\t";
   cout << "b = " << b << "\t";
   cout << "c = " << c << "\n";
   cout << "d = " << d << "\t";
   cout << "X = " << X << "\t";
   cout << "Y = " << Y << "\n";
   cout << "\t\tZ = " << Z << "\n";

   Time::set_hr_in_day(144);
   Time::set_min_in_hr(10);
   cout << "*****************************************\n";
   cout << "Welcome to the land of the forgotten!\n";
   cout << "[1 day = 144 hours,  1 hour = 10 minutes]\n\n";

   cout << "a = " << a << "\t";
   cout << "b = " << b << "\t";
   cout << "c = " << c << "\n";
   cout << "d = " << d << "\t";
   cout << "X = " << X << "\t";
   cout << "Y = " << Y << "\n";
   cout << "\t\tZ = " << Z << "\n";

   Time::set_hr_in_day(24);
   Time::set_min_in_hr(60);
   cout << "*****************************************\n";
   cout << "Welcome back to 'San Angel'!\n\n";
   cout << "a = " << a << "\t";
   cout << "b = " << b << "\t";
   cout << "c = " << c << "\n";
   cout << "d = " << d << "\t";
   cout << "X = " << X << "\t";
   cout << "Y = " << Y << "\n";
   cout << "\t\tZ = " << Z << "\n";

   return 0;
}

/*

OUTPUT:

*****************************************
Welcome to 'San Angel'!
[ 1 day = 24 hours, 1 hour = 60 minutes ]

a =  0:00	b =  0:05	c =  1:01
d = 23:59	X =  5:00	Y =  1:30
		Z =  1:06
*****************************************
Welcome to the land of the remembered!
[ 1 day = 60 hours, 1 hour = 24 minutes ]

a =  0:00	b =  0:05	c =  2:13
d = 59:23	X = 12:12	Y =  3:18
		Z =  2:18
*****************************************
Welcome to the land of the forgotten!
[1 day = 144 hours,  1 hour = 10 minutes]

a =  0:00	b =  0:05	c =  6:01
d = 143:09	X = 30:00	Y =  9:00
		Z =  6:06
*****************************************
Welcome back to 'San Angel'!

a =  0:00	b =  0:05	c =  1:01
d = 23:59	X =  5:00	Y =  1:30
		Z =  1:06


*/
