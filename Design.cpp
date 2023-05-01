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
    Booking(const std::string& referenceNumber, Flight& flight, const Passenger& passenger)
            : bookingReferenceNumber(referenceNumber), flight(flight), passenger(passenger) {}

    bool createBooking() override {
        std::cout << "Booking createBooking() method with 0 parameters" << std::endl;
        return true;
    }

    bool createBooking(Flight& flight, const Passenger& passenger) {
        std::cout << "Booking createBooking() method with 2 parameters" << std::endl;
        this->flight = flight;
        this->passenger = passenger;
        return true;
    }

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
                  << " Booking Reference: " << bookingReferenceNumber
                  << " Flight Number: " << &flight << std::endl;
    }

protected:
    std::string bookingReferenceNumber;
    Flight& flight;
    Passenger passenger;
};




class FlightBookingSystem : public IBookingSystem{
public:
//    ~FlightBookingSystem(){
//        for (auto item : bookings){
//            delete item;
//        };
//    }
    FlightBookingSystem(const std::vector<Flight*> flights, const std::vector<Booking>& bookings): flights(flights), bookings(bookings){}

    // add a new booking into the vector
    bool createBooking() override {
        std::cout << "create booking" << '\n';
//        bookings.push_back(newBooking);
    };
    // remove a booking
    bool cancelBooking() override {
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
    std::vector<Flight*> flights;
    std::vector<Booking> bookings;
};







int main() {
// Create flights
    DomesticFlight* dom_flight_1 = new DomesticFlight("DF-001", "New York", "Los Angeles", "09:00", "14:00");
    DomesticFlight* dom_flight_2 = new DomesticFlight("DF-002", "California", "Florida", "10:00", "13:00");
    DomesticFlight* dom_flight_3 = new DomesticFlight("DF-003", "Washington DC", "Chicago", "15:00", "16:00");

    std::vector<Flight*> listOfDomesticFlights;
    listOfDomesticFlights.push_back(dom_flight_1);
    listOfDomesticFlights.push_back(dom_flight_2);
    listOfDomesticFlights.push_back(dom_flight_3);


    InternationalFlight* int_flight_1 = new InternationalFlight("IF-001", "New York", "London", "19:00", "07:00");
    InternationalFlight* int_flight_2 = new InternationalFlight("IF-002", "Los Angeles", "Sydney", "00:00", "19:00");
    InternationalFlight* int_flight_3 = new InternationalFlight("IF-003", "Atlanta", "Dubai", "08:00", "20:00");

    std::vector<Flight*> listOfInternationalFlights;
    listOfInternationalFlights.push_back(int_flight_1);
    listOfInternationalFlights.push_back(int_flight_2);
    listOfInternationalFlights.push_back(int_flight_3);



    // Create passengers
    Passenger passenger1("John Doe", 35, "1234567890");
    Passenger passenger2("Jane Doe", 29, "0987654321");

    // Create booking
    Booking booking1("XQ0912", *dom_flight_1, passenger1);
    Booking booking2("KL0689", *int_flight_1, passenger2);

    booking1.displayBookingDetails();
    booking2.displayBookingDetails();

    booking1.createBooking();


    std::vector<Booking> listOfBookings;




    // Flight Booking System
    FlightBookingSystem fbs(listOfDomesticFlights, listOfBookings);
    fbs.createBooking();
}