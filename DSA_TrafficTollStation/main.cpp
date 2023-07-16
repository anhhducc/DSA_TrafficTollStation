#include <iostream>
#include <queue>

using namespace std;

// Structure for vehicle information
struct Vehicle {
    string type;
    int weight;
    int fee;
    int time;
};

// Structure for toll gate information
struct TollGate {
    queue<Vehicle> vehicles;
    int totalVehicles;
    int totalFee;
};

// Function to choose the toll gate with the least queue size
int chooseTollGate(TollGate* tollGates, int numGates) {
    int minQueueSize = tollGates[0].vehicles.size();
    int chosenGate = 0;

    for (int i = 1; i < numGates; i++) {
        if (tollGates[i].vehicles.size() < minQueueSize) {
            minQueueSize = tollGates[i].vehicles.size();
            chosenGate = i;
        }
    }

    return chosenGate;
}

int main() {
    const int numTollGates = 4;
    TollGate tollGates[numTollGates];

    // Initialize toll gate information
    for (int i = 0; i < numTollGates; i++) {
        tollGates[i].totalVehicles = 0;
        tollGates[i].totalFee = 0;
    }

    while (true) {
        int vehicleType;
        int vehicleWeight;

        cout << "Enter vehicle type (1 - Small car, 2 - Medium car, 3 - Large car, 4 - Heavy-duty car): ";
        cin >> vehicleType;

        if (vehicleType < 1 || vehicleType > 4) {
            cout << "Invalid vehicle type. Please try again.\n";
            continue;
        }

        cout << "Enter vehicle weight (tons): ";
        cin >> vehicleWeight;

        if (vehicleWeight <= 0) {
            cout << "Invalid vehicle weight. Please try again.\n";
            continue;
        }

        int tollGateIndex = chooseTollGate(tollGates, numTollGates);
        TollGate& selectedTollGate = tollGates[tollGateIndex];

        if (selectedTollGate.vehicles.size() >= 10) {
            cout << "Queue at toll gate is full. Vehicle cannot enter at the moment.\n";
            continue;
        }

        Vehicle newVehicle;
        newVehicle.weight = vehicleWeight;

        switch (vehicleType) {
        case 1:
            newVehicle.type = "Small car";
            newVehicle.fee = 5000;
            newVehicle.time = 10;
            break;
        case 2:
            newVehicle.type = "Medium car";
            newVehicle.fee = 10000;
            newVehicle.time = 10;
            break;
        case 3:
            newVehicle.type = "Large car";
            newVehicle.fee = 15000;
            newVehicle.time = 15;
            break;
        case 4:
            newVehicle.type = "Heavy-duty car";
            newVehicle.fee = 20000;
            newVehicle.time = 15;
            break;
        }

        selectedTollGate.vehicles.push(newVehicle);
        selectedTollGate.totalVehicles++;
        selectedTollGate.totalFee += newVehicle.fee;

        cout << "Vehicle passed through toll gate " << tollGateIndex + 1 << ".\n";
        cout << "Vehicle type: " << newVehicle.type << ", Weight: " << newVehicle.weight << " tons\n";
        cout << "Toll fee: " << newVehicle.fee << " VND\n";

        // Process vehicle departure
        if (!selectedTollGate.vehicles.empty()) {
            Vehicle& departingVehicle = selectedTollGate.vehicles.front();
            selectedTollGate.vehicles.pop();

            cout << "Vehicle " << departingVehicle.type << " has departed.\n";
            cout << "Departure time: " << departingVehicle.time << "s\n";
        }

        cout << "Total vehicles passed through toll gate " << tollGateIndex + 1 << ": " << selectedTollGate.totalVehicles << endl;
        cout << "Total fee collected at toll gate " << tollGateIndex + 1 << ": " << selectedTollGate.totalFee << " VND\n";

        char continueOption;
        cout << "Continue? (y/n): ";
        cin >> continueOption;

        if (continueOption == 'n') {
            break;
        }
    }

    return 0;
}
