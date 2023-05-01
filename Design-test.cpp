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

class Booking {
public:
    Booking(const std::string& referenceNumber, Flight& flight, const Passenger& passenger)
            : bookingReferenceNumber(referenceNumber), flight(flight), passenger(passenger) {}

    std::string getBookingReferenceNumber() const {
        return bookingReferenceNumber;
    }

    Flight& getFlight() const {
        return flight;
    }

    Passenger getPassenger() const {
        return passenger;
    }

protected:
    std::string bookingReferenceNumber;
    Flight& flight;
    Passenger passenger;
};

class FlightBookingSystem : public IBookingSystem {
public:
    bool createBooking() override {
        // TODO: implement cancelBooking method
        return true;
    }
    bool createBooking(Flight& flight, const Passenger& passenger) {
        // generate a random booking reference number
        std::string bookingReferenceNumber = generateBookingReferenceNumber();

        // create a new booking with the provided flight and passenger
        Booking newBooking(bookingReferenceNumber, flight, passenger);

        // add the booking to the list of bookings
        bookings.push_back(newBooking);

        return true;
    }

    bool cancelBooking() override {
        // TODO: implement cancelBooking method
        return true;
    }

    bool updateBooking() override {
        // TODO: implement updateBooking method
        return true;
    }

    void displayAvailableFlights() override {
        // TODO: implement displayAvailableFlights method
        std::cout << "Displaying available flights" << std::endl;
    }

    void displayFlightDetails() override {
        // TODO: implement displayFlightDetails method
        std::cout << "Displaying flight details" << std::endl;
    }

    void displayBookingDetails() override {
        std::cout << "------ Booking Details ------" << std::endl;
        for (Booking& booking : bookings) {
            std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << std::endl;
            std::cout << "Passenger Name: " << booking.getPassenger().getName() << std::endl;
            std::cout << "Flight Details: " << std::endl;
            booking.getFlight().displayFlightDetails();
            std::cout << std::endl;
        }
    }

protected:
    std::vector<Booking> bookings;

    std::string generateBookingReferenceNumber() {
        // generate a random string for the booking reference number
        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const int length = 6;
        std::string bookingReferenceNumber;
        for (int i = 0; i < length; i++) {
            bookingReferenceNumber += charset[rand() % sizeof(charset)];
        }
        return bookingReferenceNumber;
    }
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


    std::vector<Booking> listOfBookings;

    FlightBookingSystem bookingSystem;

    // Add bookings to the system
    bookingSystem.createBooking(*dom_flight_1, passenger1);
    bookingSystem.createBooking(*int_flight_1, passenger2);

    bookingSystem.displayBookingDetails();
//    bookingSystem.cancelBooking("XQ0912");
//    bookingSystem.updateBooking("KL0689", *dom_flight_2, passenger1);
//    bookingSystem.displayAvailableFlights();
//    bookingSystem.displayAvailableFlights();


}