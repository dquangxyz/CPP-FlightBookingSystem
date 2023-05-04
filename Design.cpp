#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

class Passenger {
public:
    Passenger(std::string name, int age, std::string contactInfo, std::string passportNo = "")
            : name(std::move(name)), age(age), contactInfo(std::move(contactInfo)), passportNo(std::move(passportNo)) {}


    // Getter functions
    std::string getName(){
        return name;
    }

    // Setter functions
    void setName(std::string newName){
        name = newName;
    }

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
            : flightNumber(std::move(flightNumber)), origin(std::move(origin)), destination(std::move(destination)),
              departureTime(std::move(departureTime)), arrivalTime(std::move(arrivalTime)) {}

    virtual ~Flight() = default;

    virtual std::string getFlightNumber(){
        return flightNumber;
    };

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
    DomesticFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime,std::string arrivalTime)
            : Flight(std::move(flightNumber), std::move(origin), std::move(destination), std::move(departureTime), std::move(arrivalTime)) {};

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
    InternationalFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime, std::string arrivalTime)
            : Flight(std::move(flightNumber), std::move(origin), std::move(destination), std::move(departureTime), std::move(arrivalTime)) {};

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

class Booking {
public:
    Booking(std::string referenceNumber, Flight* flight, Passenger passenger)
            : bookingReferenceNumber(std::move(referenceNumber)), flight(flight), passenger(std::move(passenger)) {}

    // Getter functions
    std::string getBookingReferenceNumber() const {
        return bookingReferenceNumber;
    }
    Flight* getFlight() const {
        return flight;
    }
    Passenger getPassenger() const {
        return passenger;
    }

    // Setter functions
    void setFlight(Flight* newFlight) {
        flight = newFlight;
    }
    void setPassenger(Passenger newPassenger) {
        passenger = std::move(newPassenger);
    }
    void setBookingReferenceNumber(std::string newBookingReferenceNumber){
        bookingReferenceNumber = newBookingReferenceNumber;
    }

protected:
    std::string bookingReferenceNumber;
    Flight* flight;
    Passenger passenger;
};

class IBookingSystem {
public:
//    virtual ~IBookingSystem() = default;
    virtual bool createBooking(Flight* flight, Passenger& passenger) = 0;
    virtual bool cancelBooking(std::string bookingRef) = 0;
    virtual bool updateBooking(std::string bookingRef, Flight* newFlight) = 0;
    virtual void displayAvailableFlights() = 0;
    virtual void displayAllBookingDetails() = 0;
    virtual void displayFlightDetails(Flight* flight) = 0;
    virtual void displayBookingDetails(std::string bookingRef) = 0;
};


class FlightBookingSystem : public IBookingSystem {
public:
    FlightBookingSystem(std::vector<Booking> bookings, std::vector<Flight*> flights)
            : bookings(std::move(bookings)), flights(std::move(flights)) {}

    // Create new booking
    bool createBooking(Flight* flight, Passenger& passenger) override {
        // generate a random booking reference number
        std::string bookingReferenceNumber = generateBookingReferenceNumber();
        // create a new booking with the provided flight and passenger
        Booking newBooking(bookingReferenceNumber, flight, passenger);
        // add the booking to the list of bookings
        bookings.push_back(newBooking);
        return true;
    }

    // Cancel a given booking
    bool cancelBooking(std::string bookingRef) override {
        for (auto it = bookings.begin(); it < bookings.end(); ++it) {
            if (it->getBookingReferenceNumber() == bookingRef) {
                std::cout << it->getBookingReferenceNumber() <<  " is cancelled" <<'\n';
                bookings.erase(it);
                return true;
            }
        }
        return true;
    }

    // Update a given booking - change to a new flight (given)
    bool updateBooking(std::string bookingRef, Flight* newFlight) override {
        for (auto it = bookings.begin(); it < bookings.end(); ++it) {
            if (it->getBookingReferenceNumber() == bookingRef) {
                std::cout << it->getBookingReferenceNumber() <<  " is updated" <<'\n';
                it->setFlight(newFlight);
                return true;
            }
        }
        return true;
    }

    void displayAvailableFlights() override {
        std::cout << "----- ALL Available flights ---------" << std::endl;
        for (const Flight* flight : flights) {
            flight->displayFlightDetails();
        }
    }

    void displayFlightDetails(Flight* flight) override {
        std::cout << "----- Displaying flight details from a provided flight -----" << std::endl;
        flight->displayFlightDetails();
    }

    void displayAllBookingDetails() override {
        std::cout << "------ ALL Booking Details ------" << std::endl;
        for (Booking& booking : bookings) {
            std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << " || ";
            std::cout << "Passenger Name: " << booking.getPassenger().getName() << " || ";
            std::cout << "Flight Details: " << booking.getFlight()->getFlightNumber();
            std::cout << std::endl;
        }
    }
    void displayBookingDetails(std::string bookingRef) override {
        std::cout << "---- Displaying Booking Details from a provided booking reference number ---" << std::endl;
        for (auto it = bookings.begin(); it < bookings.end(); ++it) {
            if (it->getBookingReferenceNumber() == bookingRef) {
                std::cout << "Booking Reference: " << it->getBookingReferenceNumber() << " || ";
                std::cout << "Passenger Name: " << it->getPassenger().getName() << " || ";
                std::cout << "Flight Details: " << it->getFlight()->getFlightNumber();
                std::cout << std::endl;
            }
        }
    }

protected:
    std::vector<Booking> bookings;
    std::vector<Flight*> flights;

    static std::string generateBookingReferenceNumber() {
        // Generate a random string of length 6
        const int length = 6;
        std::string bookingReferenceNumber(length, ' ');
        bookingReferenceNumber[0] = rand() % 26 + 'A';
        bookingReferenceNumber[1] = rand() % 26 + 'A';
        bookingReferenceNumber[2] = rand() % 10 + '0';
        bookingReferenceNumber[3] = rand() % 10 + '0';
        bookingReferenceNumber[4] = rand() % 26 + 'A';
        bookingReferenceNumber[5] = rand() % 26 + 'A';
        return bookingReferenceNumber;
    }
};


int main() {
    // Create flights (manually) and push all to a vector of Flight*
    Flight* dom_flight_1 = new DomesticFlight("DF-001", "New York", "Los Angeles", "09:00", "14:00");
    Flight* dom_flight_2 = new DomesticFlight("DF-002", "California", "Florida", "10:00", "13:00");
    Flight* dom_flight_3 = new DomesticFlight("DF-003", "Washington DC", "Chicago", "15:00", "16:00");
    Flight* int_flight_1 = new InternationalFlight("IF-001", "New York", "London", "19:00", "07:00");
    Flight* int_flight_2 = new InternationalFlight("IF-002", "Los Angeles", "Sydney", "00:00", "19:00");
    Flight* int_flight_3 = new InternationalFlight("IF-003", "Atlanta", "Dubai", "08:00", "20:00");

    std::vector<Flight*> listOfFlights;
    listOfFlights.push_back(dom_flight_1);
    listOfFlights.push_back(dom_flight_2);
    listOfFlights.push_back(dom_flight_3);
    listOfFlights.push_back(int_flight_1);
    listOfFlights.push_back(int_flight_2);
    listOfFlights.push_back(int_flight_3);

    // Create passengers (manually)
    Passenger passenger1("Andy Nguyen", 35, "1234567890");
    Passenger passenger2("Jane Doe", 29, "0987654321");
    Passenger passenger3("Gillian Kan", 29, "01203130423");
    Passenger passenger4("Terry William", 30, "09090909009");

    std::vector<Booking> listOfBookings;

    FlightBookingSystem bookingSystem(listOfBookings, listOfFlights);

    // Test creating bookings to the system
    bookingSystem.createBooking(dom_flight_1, passenger1);
    bookingSystem.createBooking(int_flight_1, passenger2);
    bookingSystem.createBooking(int_flight_2, passenger3);

    // Test displaying all flights
    bookingSystem.displayAvailableFlights();

    // Test displaying all bookings
    std::cout << "----------------" << '\n';
    bookingSystem.displayAllBookingDetails();

    // Test displaying a given flight
    std::cout << "----------------" << '\n';
    bookingSystem.displayFlightDetails(int_flight_3);

    // Test displaying a given booking reference
    std::cout << "----------------" << '\n';
    bookingSystem.displayBookingDetails("LR38QY");

    // Test cancelling a given booking
    std::cout << "----------------" << '\n';
    bookingSystem.cancelBooking("YQ73RT");
    bookingSystem.displayAllBookingDetails();

    // Test updating a given booking
    std::cout << "----------------" << '\n';
    bookingSystem.updateBooking("UQ39KX", dom_flight_2);
    bookingSystem.displayBookingDetails("UQ39KX");
}