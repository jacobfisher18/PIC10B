#include "time.h"

//static variables of Time class, sets to default values
int Time::min_in_hr = 60;
int Time::hr_in_day = 24;

//static setter functions
void Time::set_hr_in_day(int myHours) {    
    Time::hr_in_day = myHours;
}

void Time::set_min_in_hr(int myMinutes) {
    Time::min_in_hr = myMinutes;
}

//overloads << in order to implement cout for Time objects
std::ostream& operator<<(std::ostream& out, const Time& T) {
    
    /***************** EXTRA CREDIT SECTION *****************/
    //find the current amount of total minutes, using current_min_in_hour (not yet up to date with the static variable min_in_hr)
    int totalMinutes = T.current_min_in_hr * T.hr + T.min;
    
    //finds the new values for hr and min based on the static variable min_in_hr
    int newHr = totalMinutes / Time::min_in_hr;
    int newMin = totalMinutes % Time::min_in_hr;
    
    //updates T's current_min_in_hr and current_hr_in_day values
    T.current_min_in_hr = Time::min_in_hr;
    T.current_hr_in_day = Time::hr_in_day;

    //sets T's new values based on the new Time zone
    T.hr = newHr;
    T.min = newMin;
    /********************************************************/
    
    out << T.hr << ":";
    if (T.min < 10)
        out << "0";
    out << T.min;
    return out;
}

//constructors
Time::Time() {
    hr = 0;
    min = 0;
}

Time::Time(int myMinutes) {
    hr = myMinutes / min_in_hr;
    min = myMinutes % min_in_hr;
}

Time::Time(int myHours, int myMinutes) {
    hr = myHours % hr_in_day + (myMinutes / min_in_hr);
    min = myMinutes % min_in_hr;
}

Time::Time(double myHours) {
    hr = int(myHours) % hr_in_day;
    min = int((myHours - int(myHours)) * min_in_hr + 0.5); //+ 0.5 for rounding
}

//comparison operators
bool Time::operator<(Time& T) const {
    return hr * min_in_hr + min < T.hr * min_in_hr + T.min;
}

bool Time::operator<=(Time& T) const {
    return hr * min_in_hr + min <= T.hr * min_in_hr + T.min;
}

bool Time::operator>(Time& T) const {
    return hr * min_in_hr + min > T.hr * min_in_hr + T.min;
}

bool Time::operator>=(Time& T) const {
    return hr * min_in_hr + min >= T.hr * min_in_hr + T.min;
}

bool Time::operator==(Time& T) const {
    return hr * min_in_hr + min == T.hr * min_in_hr + T.min;
}

bool Time::operator!=(Time& T) const {
    return hr * min_in_hr + min != T.hr * min_in_hr + T.min;
}

//addition operators
Time operator+(Time lhs, const Time& rhs) {
    int myMinutes = lhs.min + rhs.min;
    int myHours = (lhs.hr + rhs.hr + (myMinutes / Time::min_in_hr)) % Time::hr_in_day;
    myMinutes %= Time::min_in_hr;
    
    return Time(myHours, myMinutes);
}

Time operator+(int lhs, const Time& rhs) {
    lhs %= Time::hr_in_day * Time::min_in_hr;
    int lhsHours = lhs / Time::min_in_hr;
    int lhsMinutes = lhs % Time::min_in_hr;
    int myMinutes = lhsMinutes + rhs.min;
    int myHours = (lhsHours + rhs.hr + (myMinutes / Time::min_in_hr)) % Time::hr_in_day;
    myMinutes %= Time::min_in_hr;
    
    return Time(myHours, myMinutes);
}

Time operator+(double lhs, const Time& rhs) {
    int lhsHours = int(lhs) % Time::hr_in_day;
    int lhsMinutes = int((lhs - int(lhs)) * Time::min_in_hr);
    int myMinutes = lhsMinutes + rhs.min;
    int myHours = (lhsHours + rhs.hr + (myMinutes / Time::min_in_hr)) % Time::hr_in_day;
    myMinutes %= Time::min_in_hr;
    
    return Time(myHours, myMinutes);
}

void Time::operator+=(Time T) {
    int myMinutes = min + T.min;
    int myHours = (hr + T.hr + (myMinutes / min_in_hr)) % hr_in_day;
    myMinutes %= min_in_hr;
    
    min = myMinutes;
    hr = myHours;
}

void Time::operator+=(int myInt) {
    myInt %= hr_in_day * min_in_hr;
    int intHours = myInt / min_in_hr;
    int intMinutes = myInt % min_in_hr;
    int myMinutes = intMinutes + min;
    int myHours = (intHours + hr + (myMinutes / min_in_hr)) % hr_in_day;
    myMinutes %= min_in_hr;
    
    min = myMinutes;
    hr = myHours;
}

void Time::operator+=(double myDouble) {
    int doubleHours = int(myDouble) % hr_in_day;
    int doubleMinutes = int((myDouble - int(myDouble)) * min_in_hr + 0.5); //+ 0.5 for rounding
    int myMinutes = doubleMinutes + min;
    int myHours = (doubleHours + hr + (myMinutes / min_in_hr)) % hr_in_day;
    myMinutes %= min_in_hr;
    
    min = myMinutes;
    hr = myHours;
}

//setter functions
void Time::set_minutes(int myMinutes) {
    min = myMinutes % min_in_hr;
}

void Time::set_minutes(double myMinutes) {
    min = int(myMinutes + 0.5) % min_in_hr; //+ 0.5 for rounding
}

void Time::set_hours(int myHours) {
    hr = myHours % hr_in_day;
}

void Time::set_hours(double myHours) {
    hr = int(myHours);
    
}

//getter functions
int Time::minutes() const {
    return min;
}

int Time::hours() const {
    return hr;
}