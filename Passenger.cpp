#include <iostream>
#include <vector>
#include <string>

class Passenger {
public:
    Passenger(std::string name, int age, std::string contactInfo, std::string passportNo = "")
        : name(name), age(age), contactInfo(contactInfo), passportNo(passportNo) {}

    void displayPassengerDetails() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Contact Info: " << contactInfo;
        if (!passportNo.empty()) {
            std::cout << ", Passport No: " << passportNo;
        }
        std::cout << std::endl;
    }

private:
    std::string name;
    int age;
    std::string contactInfo;
    std::string passportNo;
};

class Flight {
public:
    Flight(std::string flightNumber, std::string origin, std::string destination,
           std::string departureTime, std::string arrivalTime)
        : flightNumber(flightNumber), origin(origin), destination(destination),
          departureTime(departureTime), arrivalTime(arrivalTime) {}

    void displayFlightDetails() const {
        std::cout << "Flight Number: " << flightNumber << ", Origin: " << origin
                  << ", Destination: " << destination << ", Departure Time: " << departureTime
                  << ", Arrival Time: " << arrivalTime << std::endl;
    }

    bool addPassenger(const Passenger &p) {
        passengers.push_back(p);
        return true;
    }

private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    std::vector<Passenger> passengers;
};

int main() {
    // Create flights
    Flight flight1("F1", "New York", "Los Angeles", "09:00", "14:00");
    Flight flight2("F2", "New York", "London", "19:00", "07:00");

    // Create passengers
    Passenger passenger1("John Doe", 35, "1234567890");
    Passenger passenger2("Jane Doe", 29, "0987654321");

    // Add passengers to flights
    flight1.addPassenger(passenger1);
    flight2.addPassenger(passenger2);

    // Display flight details
    flight1.displayFlightDetails();
    flight2.displayFlightDetails();

    // Display passenger details
    std::cout << "Passengers on flight F1:" << std::endl;
    passenger1.displayPassengerDetails();

    std::cout << "Passengers on flight F2:" << std::endl;
    passenger2.displayPassengerDetails();

    return 0;
}
