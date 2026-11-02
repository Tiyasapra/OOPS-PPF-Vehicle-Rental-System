#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Base Class
class Vehicle {
private:
    string vehicleID;
    string model;
    int rentalDays;
    double dailyRate;

public:
    // Constructor
    Vehicle(string id, string m, int days, double rate) {
        vehicleID = id;
        model = m;
        rentalDays = days;
        dailyRate = rate;
    }

    virtual double calculateRentalCharge() const = 0;

    virtual void displayDetails() const {
        cout << "\n------ VEHICLE DETAILS ------\n";
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Model: " << model << endl;
        cout << "Rental Days: " << rentalDays << endl;
        cout << "Daily Rate: Rs. " << dailyRate << endl;
    }

    virtual ~Vehicle() {}

protected:
    int getRentalDays() const {
        return rentalDays;
    }

    double getDailyRate() const {
        return dailyRate;
    }
};

// Derived Class: Car
class Car : public Vehicle {
public:
    Car(string id, string m, int days)
        : Vehicle(id, m, days, 1500) {}

    double calculateRentalCharge() const override {
        double amount = getDailyRate() * getRentalDays();
        return amount + (amount * 0.10);
    }

    void displayDetails() const override {
        Vehicle::displayDetails();

        cout << "Vehicle Type: Car" << endl;
        cout << "Service Charge: 10%" << endl;
        cout << "Total Rental Charge: Rs. "
             << fixed << setprecision(2)
             << calculateRentalCharge() << endl;
    }
};

// Derived Class: Bike
class Bike : public Vehicle {
public:
    Bike(string id, string m, int days)
        : Vehicle(id, m, days, 500) {}

    double calculateRentalCharge() const override {
        return getDailyRate() * getRentalDays();
    }

    void displayDetails() const override {
        Vehicle::displayDetails();

        cout << "Vehicle Type: Bike" << endl;
        cout << "Total Rental Charge: Rs. "
             << fixed << setprecision(2)
             << calculateRentalCharge() << endl;
    }
};

// Function to validate rental duration
int getRentalDays() {
    int days;

    while (true) {
        cout << "Enter rental duration (days): ";
        cin >> days;

        if (cin.fail()) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (days <= 0) {
            cout << "Days must be greater than zero!\n";
        }
        else {
            return days;
        }
    }
}

// Main Function
int main() {
    int choice;

    cout << "================================\n";
    cout << "      VEHICLE RENTAL SYSTEM\n";
    cout << "================================\n";

    do {
        cout << "\n----------- MAIN MENU -----------\n";
        cout << "1. Rent a Car\n";
        cout << "2. Rent a Bike\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input! Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        if (choice == 3) {
            cout << "\nThank you for using our system!\n";
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        string id, model;

        cout << "Enter Vehicle ID: ";
        getline(cin, id);

        cout << "Enter Vehicle Model: ";
        getline(cin, model);

        int days = getRentalDays();

        Vehicle* vehicle = nullptr;

        if (choice == 1) {
            vehicle = new Car(id, model, days);
        }
        else {
            vehicle = new Bike(id, model, days);
        }

        vehicle->displayDetails();

        delete vehicle;

    } while (true);

    return 0;
}
