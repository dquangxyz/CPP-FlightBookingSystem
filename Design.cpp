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
           std::string departureTime, std::string arrivalTime, double basePrice)
            : flightNumber(std::move(flightNumber)), origin(std::move(origin)), destination(std::move(destination)),
              departureTime(std::move(departureTime)), arrivalTime(std::move(arrivalTime)), basePrice(basePrice) {}

    virtual ~Flight() = default;

    virtual std::string getFlightNumber(){
        return flightNumber;
    };

    virtual void displayFlightDetails() const = 0;

    virtual bool addPassenger(const Passenger &newPassenger) {
        passengers.push_back(newPassenger);
        this->displayFlightDetails();
        return true;
    }

    virtual bool removePassenger(Passenger passenger){
        for (auto iterator = passengers.begin(); iterator < passengers.end(); ++iterator) {
            if (iterator->getName() == passenger.getName()) {
                std::cout << "Passenger "<< iterator->getName() << " is removed from the flight " << this->getFlightNumber() <<'\n';
                passengers.erase(iterator);
            }
        }
        this->displayAllPassengersOnFlight();
        return true;
    }

    virtual double calculateTicketPrice(){}

    void displayAllPassengersOnFlight(){
        std::cout << "On flight number "<< this->getFlightNumber() << " : ";
        for (Passenger passenger : passengers){
            std::cout << passenger.getName() << ", ";
        }
        std::cout << '\n';
    }

protected:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    std::vector<Passenger> passengers;
    double basePrice;
};

class DomesticFlight : public Flight{
public:
    DomesticFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime,std::string arrivalTime, double basePrice)
            : Flight(std::move(flightNumber), std::move(origin), std::move(destination), std::move(departureTime), std::move(arrivalTime),std::move(basePrice)) {};

    void displayFlightDetails() const override {
        std::cout << "Domestic Flight Number: " << flightNumber << ", Origin: " << origin
                  << ", Destination: " << destination << ", Departure Time: " << departureTime
                  << ", Arrival Time: " << arrivalTime << std::endl;
    }

    double calculateTicketPrice() override {
        return (basePrice - domesticDiscount);
    };

    void applyDomesticDiscount(double discount){
        domesticDiscount = basePrice*(discount/100);
    }
private:
    double domesticDiscount;
};

class InternationalFlight : public Flight{
public:
    InternationalFlight(std::string flightNumber, std::string origin, std::string destination, std::string departureTime, std::string arrivalTime, double basePrice)
            : Flight(std::move(flightNumber), std::move(origin), std::move(destination), std::move(departureTime), std::move(arrivalTime), std::move(basePrice)) {};

    void displayFlightDetails() const override {
        std::cout << "International Flight Number: " << flightNumber << ", Origin: " << origin
                  << ", Destination: " << destination << ", Departure Time: " << departureTime
                  << ", Arrival Time: " << arrivalTime << std::endl;
    }

    double calculateTicketPrice() override {
        return (basePrice + internationalSurcharge);
    };

    void applyInternationalSurcharge(double surcharge){
        internationalSurcharge = basePrice*(surcharge/100);
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
        std::string bookingReferenceNumber = generateBookingReferenceNumber();
        Booking newBooking(bookingReferenceNumber, flight, passenger);
        bookings.push_back(newBooking);
        flight->addPassenger(passenger);
        return true;
    }

    // Cancel a given booking
    bool cancelBooking(std::string bookingRef) override {
        for (auto iterator = bookings.begin(); iterator < bookings.end(); ++iterator) {
            if (iterator->getBookingReferenceNumber() == bookingRef) {
                std::cout << iterator->getBookingReferenceNumber() <<  " is cancelled" <<'\n';
                bookings.erase(iterator);
                iterator->getFlight()->removePassenger(iterator->getPassenger());
                return true;
            }
        }
        return true;
    }

    // Update a given booking - change to a new flight (given)
    bool updateBooking(std::string bookingRef, Flight* newFlight) override {
        for (Booking& booking : bookings){
            if (booking.getBookingReferenceNumber() == bookingRef) {
                std::cout << booking.getBookingReferenceNumber() <<  " is updated" <<'\n';
                booking.setFlight(newFlight);
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
        for (Booking& booking : bookings){
            if (booking.getBookingReferenceNumber() == bookingRef) {
                std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << " || ";
                std::cout << "Passenger Name: " << booking.getPassenger().getName() << " || ";
                std::cout << "Flight Details: " << booking.getFlight()->getFlightNumber();
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
    Flight* dom_flight_1 = new DomesticFlight("DF-001", "New York", "Los Angeles", "09:00", "14:00", 280);
    Flight* dom_flight_2 = new DomesticFlight("DF-002", "California", "Florida", "10:00", "13:00", 300);
    Flight* dom_flight_3 = new DomesticFlight("DF-003", "Washington DC", "Chicago", "15:00", "16:00", 75);
    Flight* int_flight_1 = new InternationalFlight("IF-001", "New York", "London", "19:00", "07:00", 330);
    Flight* int_flight_2 = new InternationalFlight("IF-002", "Los Angeles", "Sydney", "00:00", "19:00", 1700);
    Flight* int_flight_3 = new InternationalFlight("IF-003", "Atlanta", "Dubai", "08:00", "20:00", 2550);

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

    bool inBookingSession = true;
    std::string input;
    while(inBookingSession){
        std::cout << "Please choose an option:" << '\n';
        std::cout << "1. Create a booking  || 2. Cancel a booking || 3. Update a booking" << '\n';
        std::cout << "4. View booking details  || 5. View flight details || 6. Display all available flights || 7. Quit" << '\n'<< '\n';
        std::getline(std::cin, input);
        if (input == "7"){
            inBookingSession = false;
        } else {
            if (input == "1"){
                bookingSystem.createBooking(int_flight_2, passenger1);
            } else if (input == "2"){
                std::cout << "Please enter the booking reference number to be cancelled: " << '\n';
                std::string bookRef;
                std::getline(std::cin, bookRef);
                bookingSystem.cancelBooking(bookRef);
            } else if (input == "3"){
                bookingSystem.displayAllBookingDetails();
                std::cout << "Please enter the booking reference number to be updated:" << '\n';
                std::string bookRef;
                std::getline(std::cin, bookRef);

                std::cout << "Please select the flight number you want to change to:" << '\n';
                std::string newFlightSelection;
                std::getline(std::cin, newFlightSelection);
                Flight* newFlight = int_flight_2;
                switch (stoi(newFlightSelection)){
                    case 1:
                        newFlight = dom_flight_1;
                        break;
                    case 2:
                        newFlight = dom_flight_2;
                        break;
                    case 3:
                        newFlight = dom_flight_3;
                        break;
                    case 4:
                        newFlight = int_flight_1;
                        break;
                    case 5:
                        newFlight = int_flight_2;
                        break;
                    case 6:
                        newFlight = int_flight_3;
                        break;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                        break;
                }
                bookingSystem.updateBooking(bookRef, newFlight);
            } else if (input == "4"){
                bookingSystem.displayBookingDetails("PH40HU");
            } else if (input == "5"){
                bookingSystem.displayFlightDetails(int_flight_2);
            } else if (input == "6"){
                bookingSystem.displayAvailableFlights();
            } else {
                std::cout << "Invalid option - please choose a valid number" << '\n';
            }
        }
    }


//    // Test creating bookings to the system
//    bookingSystem.createBooking(int_flight_2, passenger1);
//    bookingSystem.createBooking(int_flight_2, passenger2);
//    bookingSystem.createBooking(int_flight_2, passenger3);
//
//    // Test displaying all flights
//    bookingSystem.displayAvailableFlights();
//
//    // Test displaying all bookings
//    std::cout << "----------------" << '\n';
//    bookingSystem.displayAllBookingDetails();
//
//    // Test displaying a given flight
//    std::cout << "----------------" << '\n';
//    bookingSystem.displayFlightDetails(int_flight_3);
//
//    // Test displaying a given booking reference
//    std::cout << "----------------" << '\n';
//    bookingSystem.displayBookingDetails("LF11FI");
//
//    // Test cancelling a given booking
//    std::cout << "----------------" << '\n';
//    bookingSystem.cancelBooking("LF11FI");
//    bookingSystem.displayAllBookingDetails();
//
//    // Test updating a given booking
//    std::cout << "----------------" << '\n';
//    bookingSystem.updateBooking("ME24LN", dom_flight_2);
//    bookingSystem.displayBookingDetails("ME24LN");
}