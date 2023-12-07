#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Bus {
private:
    std::string busName;
    int totalSeats;
    int currentOccupancy;
    std::vector<std::string> availableDays;

public:
    Bus(const std::string& name, int seats, const std::vector<std::string>& days)
        : busName(name), totalSeats(seats), currentOccupancy(0), availableDays(days) {}

    // Getters
    std::string getBusName() const { return busName; }
    int getTotalSeats() const { return totalSeats; }

    // Updated getter as const member function
    int getCurrentOccupancy() const { return currentOccupancy; }

    const std::vector<std::string>& getAvailableDays() const { return availableDays; }

    // Setters
    void setCurrentOccupancy(int occupancy) { currentOccupancy = occupancy; }

    // Display bus details
    void displayBusDetails() const {
        std::cout << "Bus Name: " << busName << "\n";
        std::cout << "Total Seats: " << totalSeats << "\n";
        std::cout << "Current Occupancy: " << currentOccupancy << "\n";
        std::cout << "Available Days: ";
        for (const auto& day : availableDays) {
            std::cout << day << " ";
        }
        std::cout << "\n\n";
    }
};


class Admin {
private:
    std::vector<Bus> buses;

public:
    // Manage Bus Details
    void addBus(const Bus& bus) {
        buses.push_back(bus);
        std::cout << "Bus added successfully.\n";
    }

    void updateBus(const std::string& busName, int newOccupancy) {
        auto it = std::find_if(buses.begin(), buses.end(),
            [&busName](const Bus& bus) { return bus.getBusName() == busName; });
    
        if (it != buses.end()) {
            it->setCurrentOccupancy(newOccupancy);
            std::cout << "Bus details updated successfully.\n";
        } else {
            std::cout << "Bus not found.\n";
        }
    }


    void deleteBus(const std::string& busName) {
        auto it = std::remove_if(buses.begin(), buses.end(),
            [&busName](const Bus& bus) { return bus.getBusName() == busName; });

        if (it != buses.end()) {
            buses.erase(it, buses.end());
            std::cout << "Bus deleted successfully.\n";
        } else {
            std::cout << "Bus not found.\n";
        }
    }

    // Display all buses
    void displayAllBuses() const {
        if (buses.empty()) {
            std::cout << "No buses available.\n";
        } else {
            std::cout << "All Buses:\n";
            for (const auto& bus : buses) {
                bus.displayBusDetails();
            }
        }
    }

    // Getters for accessing buses
    const std::vector<Bus>& getBuses() const {
        return buses;
    }
};

class User {
private:
    std::string username;
    std::string source;
    std::string destination;

public:
    User(const std::string& name, const std::string& source, const std::string& destination)
        : username(name), source(source), destination(destination) {}

    // Browse Available Buses
    void browseAvailableBuses(const Admin& admin) const {
        std::cout << "Available Buses from " << source << " to " << destination << ":\n";

        for (const auto& bus : admin.getBuses()) {
            if (isBusAvailable(bus)) {
                bus.displayBusDetails();
                // In a real-world scenario, you would calculate and display the actual distance and ETA.
                std::cout << "Distance: " << rand() % 100 << " km\n";
                std::cout << "Estimated Time of Arrival: " << rand() % 3 + 1 << " hours\n\n";
            }
        }
    }

    // Check Seat Availability
    void checkSeatAvailability(const Admin& admin, const std::string& busName) const {
        for (const auto& bus : admin.getBuses()) {
            if (bus.getBusName() == busName && isBusAvailable(bus)) {
                int availableSeats = bus.getTotalSeats() - bus.getCurrentOccupancy();
                std::cout << "Available seats on " << busName << ": " << availableSeats << "\n";
                return;
            }
        }
        std::cout << "Bus not found or not available for the selected route.\n";
    }

    // Seat Booking
    // Inside the User class
// Inside the User class

// Seat Booking
void bookSeat(Admin& admin, const std::string& busName) {
    for (auto& bus : admin.getBuses()) {
        if (bus.getBusName() == busName && isBusAvailable(bus)) {
            if (bus.getCurrentOccupancy() < bus.getTotalSeats()) {
                // Use a non-const reference here
                admin.updateBus(busName, bus.getCurrentOccupancy() + 1);
                std::cout << "Seat booked successfully on " << busName << ".\n";
            } else {
                std::cout << "No available seats on " << busName << ".\n";
            }
            return;
        }
    }
    std::cout << "Bus not found or not available for the selected route.\n";
}

// Cancel Seat Booking
void cancelSeatBooking(Admin& admin, const std::string& busName) {
    for (auto& bus : admin.getBuses()) {
        if (bus.getBusName() == busName && isBusAvailable(bus) && bus.getCurrentOccupancy() > 0) {
            // Use a non-const reference here
            admin.updateBus(busName, bus.getCurrentOccupancy() - 1);
            std::cout << "Seat booking canceled successfully on " << busName << ".\n";
            return;
        }
    }
    std::cout << "No booked seats found on " << busName << ".\n";
}

private:
    // Helper function to check if the bus is available for the user's route
    bool isBusAvailable(const Bus& bus) const {
        // In a real-world scenario, you would have a more complex logic to check if the bus serves the specified route.
        return true;
    }
};

int main() {
    // Example usage
    Bus bus1("Bus A", 50, { "Monday", "Wednesday", "Friday" });
    Bus bus2("Bus B", 40, { "Tuesday", "Thursday" });

    Admin admin;
    admin.addBus(bus1);
    admin.addBus(bus2);

    User user("John", "City A", "City B");

    admin.displayAllBuses();

    user.browseAvailableBuses(admin);
    user.checkSeatAvailability(admin, "Bus A");
    user.bookSeat(admin, "Bus A");

    user.browseAvailableBuses(admin);
    user.cancelSeatBooking(admin, "Bus A");

    user.browseAvailableBuses(admin);

    return 0;
}
