#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    std::string getName() const {
        return name;
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

    virtual ~Flight() {}

    virtual void displayFlightDetails() const = 0;

    virtual bool addPassenger(const Passenger &p) {
        passengers.push_back(p);
        return true;
    }

    virtual bool removePassenger(const Passenger &p){
        // search for passenger id and remove it from the vector p
    }

    virtual double calculateTicketPrice(){}

protected:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    std::vector<Passenger> passengers;
};

class DomesticFlight : public Flight{
public:
    DomesticFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
                   std::string arrivalTime) : Flight(flightNumber, origin, destination, departureTime, arrivalTime) {};

    void displayFlightDetails() const override {
        std::cout << "Domestic Flight Number: " << flightNumber << ", Origin: " << origin
                  << ", Destination: " << destination << ", Departure Time: " << departureTime
                  << ", Arrival Time: " << arrivalTime << std::endl;
    }

    double calculateTicketPrice() override {
        //
    };

    void applyDomesticDiscount(double discount){
        //
    }
private:
    double domesticDiscount;
};

class InternationalFlight : public Flight{
public:
    InternationalFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime,
                   std::string arrivalTime) : Flight(flightNumber, origin, destination, departureTime, arrivalTime) {};

    void displayFlightDetails() const override {
        std::cout << "International Flight Number: " << flightNumber << ", Origin: " << origin
                  << ", Destination: " << destination << ", Departure Time: " << departureTime
                  << ", Arrival Time: " << arrivalTime << std::endl;
    }

    double calculateTicketPrice() override {
        //
    };

    void applyInternationalSurcharge(double surcharge){
        //
    }
private:
    double internationalSurcharge;
};


class IBookingSystem {
public:
    virtual ~IBookingSystem() {}
    virtual bool createBooking() = 0;
    virtual bool cancelBooking() = 0;
    virtual bool updateBooking() = 0;
    virtual void displayAvailableFlights() = 0;
    virtual void displayFlightDetails() = 0;
    virtual void displayBookingDetails() = 0;
};

class Booking : public IBookingSystem {
public:
    Booking(const std::string& referenceNumber, Flight* flight, const Passenger& passenger)
            : bookingReferenceNumber(referenceNumber), flight(flight), passenger(passenger) {}

    bool createBooking() override {
        return true;
    };

    bool cancelBooking() override {
        return true;
    }

    bool updateBooking() override {
        return true;
    }

    void displayAvailableFlights() override {
        std::cout << "Displaying available flights" << std::endl;
    }

    void displayFlightDetails() override {
        std::cout << "Displaying flight details" << std::endl;
    }

    void displayBookingDetails() override {
        std::cout << "Customer: " << passenger.getName()
                  << "Booking Reference: " << bookingReferenceNumber
                  << "Flight Number: " << &flight << std::endl;
    }

protected:
    std::string bookingReferenceNumber;
    Flight* flight;
    Passenger passenger;
};


class FlightBookingSystem : public IBookingSystem{
public:
//    ~FlightBookingSystem(){
//        for (auto item : bookings){
//            delete item;
//        };
//    }

    // add a new booking into the vector
    bool createBooking(Booking newBooking) {
        bookings.push_back(newBooking);
    };
    // remove a booking
    bool cancelBooking(Booking cancelledBooking) {
//        auto i = std::find(bookings.begin(), bookings.end(), cancelledBooking);
//        if (i != bookings.end()) {
//            delete *i;
//            bookings.erase(i);
//        }
    };


    bool updateBooking() override {
        // implementation
    };
    void displayAvailableFlights() override {
        // implementation
    };
    void displayFlightDetails() override {
        // implementation
    };
    void displayBookingDetails() override {
        // implementation
    };
protected:
    std::vector<Flight> flights;
    std::vector<Booking> bookings;
};







int main() {
    // Create flights
    DomesticFlight flight1("F1", "New York", "Los Angeles", "09:00", "14:00");
    InternationalFlight flight2("F2", "New York", "London", "19:00", "07:00");

    // Create passengers
    Passenger passenger1("John Doe", 35, "1234567890");
    Passenger passenger2("Jane Doe", 29, "0987654321");

    // Create booking
    Booking booking1("XQ0912", &flight1, passenger1);
    Booking booking2("KL0689", &flight2, passenger2);

    booking1.displayBookingDetails();
    booking2.displayBookingDetails();



    return 0;
}

//int main() {
//    std::cout <<  "This is test file" << '\n';
//    // Create flights
//    DomesticFlight flight1("F1", "New York", "Los Angeles", "09:00", "14:00");
//    InternationalFlight flight2("F2", "New York", "London", "19:00", "07:00");
//
//    // Create passengers
//    Passenger passenger1("John Doe", 35, "1234567890");
//    Passenger passenger2("Jane Doe", 29, "0987654321");
//
//    // Add passengers to flights
//    flight1.addPassenger(passenger1);
//    flight2.addPassenger(passenger2);
//
//    // Display flight details
//    flight1.displayFlightDetails();
//    flight2.displayFlightDetails();
//
//    // Display passenger details
//    std::cout << "Passengers on flight F1:" << std::endl;
//    passenger1.displayPassengerDetails();
//
//    std::cout << "Passengers on flight F2:" << std::endl;
//    passenger2.displayPassengerDetails();
//
//    return 0;
//}

// testing
// Create booking for passenger1 on domesticFlight
//Booking booking1;
//bool success = booking1.createBooking(&domesticFlight, &passenger1);
//if (success) {
//// Display booking details for booking1
//booking1.displayBookingDetails();
//}
//
//// Create booking for passenger2 on internationalFlight
//Booking booking2;
//success = booking2.createBooking(&internationalFlight, &passenger2);
//if (success) {
//// Display booking details for booking2
//booking2.displayBookingDetails();
//}