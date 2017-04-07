/*
 Jacob Fisher
 4/17/16
 Defines the interface and member functions of a Time class, which needs to work with given drivers
*/

#ifndef time_h
#define time_h

#include <iostream>

class Time {
public:
    
    /*
     •overloads << in order to implement cout for Time objects
     •we have a version where T is const and one where T is not const
     •the const version handles when we need to cout a sum (like "cout << b + c")
     •the non-const versin is made to handle the ultimate driver; when it is called it modifies T's member variables so as to convert to a new time zone that was set by set_her_in_day or set_min_in_hr
     */
    friend std::ostream& operator<<(std::ostream& out, const Time& T);
    friend std::ostream& operator<<(std::ostream& out, Time& T);
    
    //static setter functions
    static void set_hr_in_day(int myHours);
    static void set_min_in_hr(int myMinutes);
    
    //constructors
    Time();
    Time(int myMinutes);
    Time(int myHours, int myMinutes);
    Time(double myHours);
    
    //comparison operators
    bool operator<(Time& T) const;
    bool operator<=(Time& T) const;
    bool operator>(Time& T) const;
    bool operator>=(Time& T) const;
    bool operator==(Time& T) const;
    bool operator!=(Time& T) const;
    
    //addition operators
    friend Time operator+(const Time lhs, const Time& rhs);
    friend Time operator+(const int lhs, const Time& rhs);
    friend Time operator+(const double lhs, const Time& rhs);
    
    void operator+=(const Time& T);
    void operator+=(const int& myInt);
    void operator+=(const double& myDouble);
    
    //setter functions
    void set_minutes(int myMinutes);
    void set_minutes(double myMinutes);
    void set_hours(int myHours);
    void set_hours(double myHours);
    
    //getter functions
    int minutes() const;
    int hours() const;
    
private:
    
    /***************** EXTRA CREDIT SECTION *****************/
    /*
     • variables to keep track of what units the Time object's variables are currently in
     • this should usually correspond to the static variables hr_in_day and min_in_hr, but right when the static variables are changed, these private variables will remain the same until cout is called and the Time object is converted into the new hr_in_day and min_in_hr settings
     */
    int current_hr_in_day = 24;
    int current_min_in_hr = 60;
    /********************************************************/
    
    //static variables
    static int hr_in_day;
    static int min_in_hr;
    
    //normal private variables of Time class
    int min;
    int hr;
};

#endif
