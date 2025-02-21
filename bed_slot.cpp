#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int TOTAL_BEDS = 10;
string databaseFile = "database.txt";

// Structure for a bed slot
struct Bed {
    int bedNumber;
    bool isOccupied;
    string patientName;
};

// Function to load bed data from file
vector<Bed> loadBeds() {
    vector<Bed> beds(TOTAL_BEDS);
    ifstream file(databaseFile);

    if (!file) {
        // Initialize default beds
        for (int i = 0; i < TOTAL_BEDS; i++) {
            beds[i] = {i + 1, false, ""};
        }
    } else {
        for (int i = 0; i < TOTAL_BEDS; i++) {
            file >> beds[i].bedNumber >> beds[i].isOccupied;
            file.ignore();
            getline(file, beds[i].patientName);
        }
    }

    file.close();
    return beds;
}

// Function to save bed data to file
void saveBeds(const vector<Bed>& beds) {
    ofstream file(databaseFile);
    for (const auto& bed : beds) {
        file << bed.bedNumber << " " << bed.isOccupied << " " << bed.patientName << endl;
    }
    file.close();
}

// Function to display available and occupied beds
void displayBeds() {
    vector<Bed> beds = loadBeds();
    cout << "\n🏥 Bed Slot Status:\n";
    for (const auto& bed : beds) {
        cout << "Bed " << bed.bedNumber << " - ";
        if (bed.isOccupied)
            cout << "Occupied by " << bed.patientName << endl;
        else
            cout << "Available\n";
    }
}

// Function to book a bed
void bookBed() {
    vector<Bed> beds = loadBeds();
    int bedChoice;
    string patientName;

    cout << "\nEnter Bed Number to Book (1-" << TOTAL_BEDS << "): ";
    cin >> bedChoice;

    if (bedChoice < 1 || bedChoice > TOTAL_BEDS || beds[bedChoice - 1].isOccupied) {
        cout << "❌ Bed is not available! Try another bed.\n";
        return;
    }

    cout << "Enter Patient Name: ";
    cin.ignore();
    getline(cin, patientName);

    beds[bedChoice - 1].isOccupied = true;
    beds[bedChoice - 1].patientName = patientName;

    saveBeds(beds);
    cout << "✅ Bed " << bedChoice << " booked successfully for " << patientName << "!\n";
}

// Function to cancel a booking
void cancelBooking() {
    vector<Bed> beds = loadBeds();
    int bedChoice;

    cout << "\nEnter Bed Number to Cancel Booking (1-" << TOTAL_BEDS << "): ";
    cin >> bedChoice;

    if (bedChoice < 1 || bedChoice > TOTAL_BEDS || !beds[bedChoice - 1].isOccupied) {
        cout << "❌ Invalid Bed Number or No Booking Found!\n";
        return;
    }

    beds[bedChoice - 1].isOccupied = false;
    beds[bedChoice - 1].patientName = "";

    saveBeds(beds);
    cout << "✅ Booking for Bed " << bedChoice << " has been cancelled.\n";
}
