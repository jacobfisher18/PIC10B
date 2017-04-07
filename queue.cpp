/*
 Jacob Fisher
 5/23/16
 A program that simulates a queue in a bank
 
 Waiting times for different Probabilities and Tellers
 +------------------------------------------------+
 |        | T = 1 | T = 2 | T = 3 | T = 4 | T = 5 |
 | P = 10 | 10.37 | 0.41  | 0.15  | 0.00  | 0.00  |
 | P = 20 | 258.59| 7.92  | 0.56  | 0.10  | 0.00  |
 | P = 30 | 477.53| 102.47| 11.84 | 0.54  | 0.04  |
 | P = 40 | 719.89| 199.38| 62.24 | 10.10 | 0.88  |
 | P = 50 | 816.18| 326.36| 133.71| 25.89 | 1.17  |
 +------------------------------------------------+
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "queue.h" //a custom queue wrapper class

using namespace Pic10B; //in order to use our custom queue

class Cliente {
public:
    inline Cliente( std::string n = "Default_client" , int a = 0 , int s = 0 )
    : name(n) , arrivalTime(a) , serviceTime(s) { }
    
    // Accessors
    inline std::string get_name() const { return name; }
    inline int get_arrival_time() const { return arrivalTime; }
    inline int get_service_time() const { return serviceTime; }
    
    friend std::istream& operator>>(std::istream& in, Cliente& rhs);
    
private:
    std::string name;
    int arrivalTime;
    int serviceTime;
};

class Counter {
public:
    //Default values for a counter with a given name
    Counter(std::string myName) {
        name = myName;
        atCounter = Cliente();
        empty = true;
        startService = 0;
    }
    
    //Getters
    std::string get_name() const {return name;}
    Cliente get_client() const {return atCounter;} //returns the Cliente at the counter
    bool isEmpty() const {return empty;}
    int get_start_service() const {return startService;}
    
    //Modifiers
    void enter_client(const Cliente& newCliente) {atCounter = newCliente; empty = false;}
    void exit_client() {empty = true;}
    void set_start_service(const int& newStartTime) {startService = newStartTime;};
    
private:
    std::string name;
    Cliente atCounter;
    bool empty;
    int startService;
};

//Overload of input operator for Clientes
std::istream& operator>>(std::istream& in , Cliente& rhs) {
    in >> rhs.name >> rhs.arrivalTime >> rhs.serviceTime;
    return in;
}

//Prints the time on the screen, given the number of minutes after 9:00am
void output_time(std::ostream& out, int minsAfterNine) {
    const int MIN_PER_HOUR = 60;
    
    int hour = 9 + minsAfterNine / MIN_PER_HOUR;
    int min = minsAfterNine % MIN_PER_HOUR;
    
    if (hour <= 12) out << hour << ":";
    else out << hour - 12 << ":";
    
    if (min > 9) out << min;
    else out << "0" << min;
    
    if (hour <= 12) out << "am";
    else out << "pm";
    
    return;
}

//returns true if at least one counter is occupied
bool anyCountersOccupied(std::vector<Counter> v) {
    for (int i = 0; i < v.size(); i++) {
        if (!v[i].isEmpty())
            return true;
    }
    return false;
}

//Just for fun, used to give randomly generated customers random names
std::string randName() {
    int n = rand() % 26;
    
    std::string firstName;
    char middleInitial = rand() % 26 + 65;
    char lastInitial = rand() % 26 + 65;
    
    if (n == 0) firstName = "Alex";
    else if (n == 1) firstName = "Bob";
    else if (n == 2) firstName = "Charlie";
    else if (n == 3) firstName = "Derek";
    else if (n == 4) firstName = "Evan";
    else if (n == 5) firstName = "Frank";
    else if (n == 6) firstName = "Georgia";
    else if (n == 7) firstName = "Haley";
    else if (n == 8) firstName = "Ingrid";
    else if (n == 9) firstName = "Josh";
    else if (n == 10) firstName = "Kendyl";
    else if (n == 11) firstName = "Lanna";
    else if (n == 12) firstName = "Margaret";
    else if (n == 13) firstName = "Naomi";
    else if (n == 14) firstName = "Oliver";
    else if (n == 15) firstName = "Peter";
    else if (n == 16) firstName = "Quincy";
    else if (n == 17) firstName = "Rebecca";
    else if (n == 18) firstName = "Steve";
    else if (n == 19) firstName = "Talia";
    else if (n == 20) firstName = "Ulysses";
    else if (n == 21) firstName = "Victoria";
    else if (n == 22) firstName = "Winston";
    else if (n == 23) firstName = "Xander";
    else if (n == 24) firstName = "Yolanda";
    else firstName = "Zack";
    
    return firstName + "_" + middleInitial + "_" + lastInitial + "";
}

int main() {
    
    srand((int)time(0)); //set the seed for random numbers
    
    queue<Cliente> customerList; //a queue of all the customers that will be served in the day
    
    int customersServed = 0; //total number of customers served in the day
    int lineSize = 0; //current size of the line
    int maxLineSize = 0; //maximum line size throughout the day
    int totalWaitingTime = 0; //the total waiting time in line of all the customers
    
    //in order to output the play-by-play and statistics to a file
    std::ofstream fout;
    fout.open("output.txt");
    
    char listType;
    std::cout << "Retrieve the customer list from a file (enter 'f') or generate a list randomly ('r')?" << std::endl;
    std::cin >> listType;
    
    //Read customer file. Assume the format is: name arrivalTime serviceTime, and that the list is sorted based on arrival times.
    if (listType == 'f') {
        
        std::string fileName;
        std::cout << "What is the name of the file?" << std::endl;
        std::cin >> fileName;
        
        std::ifstream fin;
        fin.open(fileName.c_str());
        
        Cliente newCustomer;
        
        while ( fin >> newCustomer )
            customerList.enter(newCustomer);
        
        fin.close();
        
        if ( customerList.is_empty() ) {
            std::cout << "ERROR: Could not read file " << fileName << std::endl;
            return 1; // Standard practice is to NOT RETURN 0 if an error occurs.
        }
    }
    
    //Generate customer list randomly
    else {
        int probability;
        std::cout << "What is the probability that a customer arrives each minute (integer between 1 and 100)?" << std::endl;
        std::cin >> probability;
        
        //goes through all times from opening (9AM) through closing (6PM)
        for (int i = 0; i < 540; i++) {
            int randProb = rand() % 100 + 1; //random between 1 and 100, inclusive of bounds
            if (randProb <= probability) {
                int serviceTime = rand() % 14 + 2; //random between 2 and 15, inclusive of bounds
                Cliente newCustomer(randName(), i, serviceTime);
                customerList.enter(newCustomer);
            }
        }
    }
    
    //Prompt for the number of counters in the bank
    int numTellers;
    std::cout << "How many tellers are there?" << std::endl;
    std::cin >> numTellers;
    
    //Create the vector of counters, fill it with objects
    std::vector<Counter> tellers;
    for (int i = 0; i < numTellers; i++) {
        Counter newCounter("Counter " + std::to_string(i+1));
        tellers.push_back(newCounter);
    }
    
    //First customer steps up to the first counter immediately when he arrives. Clock starts running at this arrival time.
    int currentTime = tellers[0].get_client().get_arrival_time();
    tellers[0].enter_client(customerList.leave());
    tellers[0].set_start_service(currentTime);
    
    //Display when the first customer enters the bank and steps up to the counter
    output_time(fout, currentTime);
    fout << "  " << tellers[0].get_client().get_name() << " enters the bank." << std::endl;
    output_time(fout, currentTime);
    fout << "  " << tellers[0].get_client().get_name() << " steps up to " << tellers[0].get_name() << "." << std::endl;
    
    //Set up our empty line
    queue<Cliente> line;
    
    //There are still customers being served or yet to be served
    //At least one of customerList, line, and the counters is not empty
    while (!customerList.is_empty() || !line.is_empty() || anyCountersOccupied(tellers)) {
        
        //A Cliente enters the line
        if (!customerList.is_empty() && customerList.peek().get_arrival_time() <= currentTime){
            output_time(fout, currentTime);
            fout  << "  " << customerList.peek().get_name()
            << " enters the bank." << std::endl;
            
            line.enter(customerList.leave());
            lineSize++;
        }
        
        //A Cliente leaves a counter
        for (int i = 0; i < tellers.size(); i++) {
            if (!(tellers[i].isEmpty()) && (tellers[i].get_start_service() + tellers[i].get_client().get_service_time() <= currentTime)) {
                
                tellers[i].exit_client();
                output_time(fout, currentTime);
                fout << "  " << tellers[i].get_client().get_name()
                << " leaves " << tellers[i].get_name() << "." << std::endl;
                
                customersServed++;
            }
        }
        
        //Someone steps up to a counter
        for (int i = 0; i < tellers.size(); i++) {
            if (tellers[i].isEmpty() && !line.is_empty()) {
                tellers[i].enter_client(line.leave());
                tellers[i].set_start_service(currentTime);
                
                output_time(fout, currentTime);
                fout << "  " << tellers[i].get_client().get_name()
                << " steps up to " << tellers[i].get_name() << "." << std::endl;
                lineSize--;
            }
        }
        
        if (lineSize > maxLineSize)
            maxLineSize = lineSize;
        
        totalWaitingTime += lineSize; //each minute, the total waiting time is increased by the number of people in line
        
        ++currentTime;
    }
    
    //Output Final Statistics
    fout << std::endl << "FINAL STATISTICS" << std:: endl;
    fout << "----------------" << std:: endl;
    fout << "Customers Served: " << customersServed << std::endl;
    fout << "Average waiting time: " << std::fixed << std::setprecision(2) << totalWaitingTime/double(customersServed) << std::endl;
    fout << "Maximum customers in line at once: " << maxLineSize << std::endl;
    
    std::cout << "Results outputted to output.txt" << std::endl;
    
    fout.close();
    
    return 0;
}