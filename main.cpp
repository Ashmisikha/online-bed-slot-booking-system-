#include <iostream>
#include "bed_slot.h"

using namespace std;

void menu() {
    cout << "\n🏥 Bed Slot Booking System";
    cout << "\n1️⃣ Book a Bed";
    cout << "\n2️⃣ Cancel Booking";
    cout << "\n3️⃣ View Available Beds";
    cout << "\n4️⃣ Exit";
    cout << "\nEnter choice: ";
}

int main() {
    int choice;

    while (true) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                bookBed();
                break;
            case 2:
                cancelBooking();
                break;
            case 3:
                displayBeds();
                break;
            case 4:
                cout << "🚀 Exiting system...\n";
                return 0;
            default:
                cout << "❌ Invalid choice! Try again.\n";
        }
    }
}
