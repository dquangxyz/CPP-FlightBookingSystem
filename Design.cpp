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
    virtual bool createBooking(Flight* flight, Passenger& passenger) = 0;
    virtual bool cancelBooking(std::string bookingRef) = 0;
    virtual bool updateBooking(std::string bookingRef, Flight* newFlight) = 0;
    virtual void displayAvailableFlights() = 0;
    virtual void displayFlightDetails(Flight* flight) = 0;
    virtual bool displayBookingDetails(std::string bookingRef) = 0;
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
        return false;
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
        return false;
    }

    // Display all available flights
    void displayAvailableFlights() override {
        std::cout << "----- ALL Available flights ---------" << std::endl;
        for (const Flight* flight : flights) {
            flight->displayFlightDetails();
        }
    }

    // Display a flight
    void displayFlightDetails(Flight* flight) override {
        std::cout << "----- Displaying flight details from a provided flight -----" << std::endl;
        flight->displayFlightDetails();
    }

    // Display a given booking reference
    bool displayBookingDetails(std::string bookingRef) override {
        std::cout << "---- Displaying Booking Details from a provided booking reference number ---" << std::endl;
        for (Booking& booking : bookings){
            if (booking.getBookingReferenceNumber() == bookingRef) {
                std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << " || ";
                std::cout << "Passenger Name: " << booking.getPassenger().getName() << " || ";
                std::cout << "Flight Details: ";
                booking.getFlight()->displayFlightDetails();
                std::cout << std::endl;
                return true;
            }
        }
        return false;
    }

    // Extra method: to list all bookings made by a passenger
    bool displayPassengerAllBookings(Passenger* passenger) {
        std::cout << "---- Displaying All Bookings from the current passenger ---" << std::endl;
        if (bookings.empty()){
            std::cout << "No record" << std::endl;
            return false;
        } else {
            for (Booking& booking : bookings){
                if (booking.getPassenger().getName() == passenger->getName()) {
                    std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << " || ";
                    std::cout << "Passenger Name: " << booking.getPassenger().getName() << " || ";
                    std::cout << "Flight Number " << booking.getFlight()->getFlightNumber();
                    std::cout << std::endl;
                }
            }
            return true;
        }
    }

    // Extra method: to check all bookings in the system
    void listAllBookingsInSystem() {
        std::cout << "------ ALL Booking Details in the system------" << std::endl;
        for (Booking& booking : bookings) {
            std::cout << "Booking Reference: " << booking.getBookingReferenceNumber() << " || ";
            std::cout << "Passenger Name: " << booking.getPassenger().getName() << " || ";
            std::cout << "Flight Details: " << booking.getFlight()->getFlightNumber();
            std::cout << std::endl;
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
    Flight* int_flight_1 = new InternationalFlight("IF-004", "New York", "London", "19:00", "07:00", 330);
    Flight* int_flight_2 = new InternationalFlight("IF-005", "Seattle", "Sydney", "00:00", "19:00", 1700);
    Flight* int_flight_3 = new InternationalFlight("IF-006", "Atlanta", "Dubai", "08:00", "20:00", 2550);

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

    // Initialize bookingSystem
    std::vector<Booking> listOfBookings;
    FlightBookingSystem bookingSystem(listOfBookings, listOfFlights);

    // Loop 1 (most outer loop) - when the session program is active
    bool inBookingSession = true;
    std::string input;
    while(inBookingSession){
        std::cout << "WELCOME - select user (1,2,3,4): " << '\n';
        Passenger* currentPassenger;
        Flight* newFlight;
        std::string user;
        std::getline(std::cin, user);

        // Loop 2 - when the user is not selected
        while (true) {
            switch (stoi(user)) {
                case 1:
                    currentPassenger = &passenger1;
                    break;
                case 2:
                    currentPassenger = &passenger2;
                    break;
                case 3:
                    currentPassenger = &passenger3;
                    break;
                case 4:
                    currentPassenger = &passenger4;
                    break;
                default:
                    std::cout << "Invalid passenger - please select again (1,2,3,4) " << '\n';
                    std::getline(std::cin, user);
                    continue;
            }

            // Loop 3 - when the user is selected
            while(true){
                std::cout << "Please choose an option:" << '\n';
                std::cout << "1. Create a booking  || 2. Cancel a booking || 3. Update a booking || 4. View booking details"<< '\n';
                std::cout << "5. View passenger details || 6. Display all available flights || 7. Booking for another user || 8. Quit" << '\n';
                std::getline(std::cin, input);

                if (input == "8"){ // quit the most outer while-loop (first loop) - quit program
                    inBookingSession = false;
                    break;
                } else if (input == "7"){ // quit the third loop (select the user again)
                    break;
                } else {
                    if (input == "1"){ // create booking
                        std::cout << "Please choose a flight (1,2,3,4,5,6) :" << '\n';
                        bookingSystem.displayAvailableFlights();

                        std::string newFlightSelection;
                        std::getline(std::cin, input);
                        while(true){ //Loop 4a - when flight is not selected
                            switch (stoi(input)) {
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
                                    std::cout << "Invalid input - please select again (1,2,3,4,5,6)" << '\n';
                                    std::getline(std::cin, input);
                                    continue;
                            }
                            break;
                        }
                        // Call createBooking method at the end
                        bookingSystem.createBooking(newFlight, *currentPassenger);

                    } else if (input == "2"){ // cancel a booking
                        if (bookingSystem.displayPassengerAllBookings(currentPassenger)){
                            std::cout << "Please enter the booking reference number to be cancelled (or press 'b' to go back): " << '\n';
                            std::string bookRefInput;
                            while(true){ // Loop 4b - enter the right book ref for cancelling
                                std::getline(std::cin, bookRefInput);
                                if (bookRefInput == "b" || bookRefInput == "B"){ // Go back
                                    break;
                                } else if (bookingSystem.cancelBooking(bookRefInput)){ // Perform cancelling a booking
                                    break;
                                } else {
                                    std::cout << "Booking reference number not found - please try again (or press 'b' to go back)" << '\n';
                                    continue;
                                }
                            }
                        }

                    } else if (input == "3"){ // update a booking
                        if (bookingSystem.displayPassengerAllBookings(currentPassenger)){
                            std::cout << "Please enter the booking reference number to be updated (or press 'b' to go back):" << '\n';
                            std::string bookRefInput;
                            while(true){ // Loop 4c - enter the right book ref for cancelling
                                std::getline(std::cin, bookRefInput);
                                if (bookRefInput == "b" || bookRefInput == "B"){
                                    break;
                                } else if (bookingSystem.displayBookingDetails(bookRefInput)) {
                                    std::cout << "Please select the flight number you want to change to (1,2,3,4,5,6):" << '\n';
                                    bookingSystem.displayAvailableFlights();
                                    std::string newFlightSelection;
                                    std::getline(std::cin, newFlightSelection);
                                    while(true){ // Loop 4d - enter the right flight choice for cancelling
                                        switch (stoi(newFlightSelection)) {
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
                                                std::cout << "Invalid input - please select again (1,2,3,4,5,6)" << '\n';
                                                std::getline(std::cin, input);
                                                continue;
                                        }
                                        break;
                                    }
                                    break;
                                } else {
                                    std::cout << "Booking reference not found - please try again (or press 'b' to go back)" << '\n';
                                    continue;
                                }

                            }
                            // Call updateBooking method at the end
                            bookingSystem.updateBooking(bookRefInput, newFlight);
                        }


                    } else if (input == "4"){ // View booking details
                        if (bookingSystem.displayPassengerAllBookings(currentPassenger)){
                            std::string bookRef;
                            while(true){ // Loop 4d - enter the right book ref for display
                                std::cout << "Please enter the booking reference number to view more details (or press 'b' to go back): " << '\n';
                                std::getline(std::cin, bookRef);
                                if (bookRef == "b" || bookRef == "B"){
                                    break;
                                } else if (bookingSystem.displayBookingDetails(bookRef)){
                                    break;
                                } else {
                                    std::cout << "Booking reference number not found - please try again (or press 'b' to go back)" << '\n';
                                    continue;
                                }
                            }
                        }

                    } else if (input == "5"){ // View passenger details
                        currentPassenger->displayPassengerDetails();

                    } else if (input == "6"){ // Display all available flights
                        bookingSystem.displayAvailableFlights();

                    } else {
                        std::cout << "Invalid option - please choose a valid number (1,2,3,4,5,6,7,8)" << '\n';
                    }
                }
            }
            break;
        }
    }

}