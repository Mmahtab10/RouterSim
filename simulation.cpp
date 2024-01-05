/*  Author: Mohammad Mahtab Uddin Khan
    Email: mohammadmahtab.khan@ucalgary.ca 

    Citation:
    - Referenced the pseudocode from the slides on Network Simulation by Sadaf Erfanmanesh, available on D2L.
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Packet {
    double arrivalTime; 
    double departureTime; 
    int packetSize;           
};

vector<Packet> parseInputFile(const string& fileName) {
    vector<Packet> packets; // Vector of type Packet
    ifstream traceFile(fileName);// Input file stream for reading the trace file
    double timestamp;
    int packetSize;

    while (traceFile >> timestamp >> packetSize) {
        packets.push_back({timestamp, 0.0, packetSize});// Create a Packet struct and add it to the vector
    }

    traceFile.close();
    return packets; // Return the vector containing the packets read from trace file
}

void runSimulation(const vector<Packet>& packets, int bufferSize, double wlanCapacity) {
    double currentTime = 0.0;
    double totalQueuingDelay = 0.0;
    int packetsDropped = 0;
    queue<Packet> routerQ;

    //Iterate through each incoming packets at the router
    for (const auto& packet : packets) {
        while (!routerQ.empty() && routerQ.front().departureTime <= packet.arrivalTime) {
            totalQueuingDelay += routerQ.front().departureTime - routerQ.front().arrivalTime;
            routerQ.pop();
        }

        //Check if buffer is full
        if (routerQ.size() < bufferSize) {
            double transmissionTime = static_cast<double>(packet.packetSize) * 8.0 / (wlanCapacity * 1e6); //Packets are in bytes and wlan is in Mbps, so needs to be converted
            double departureTime = max(currentTime, packet.arrivalTime) + transmissionTime;
            currentTime = departureTime; // update currentTime for use in the next iteration
            routerQ.push({packet.arrivalTime, departureTime, packet.packetSize}); // Add packet to router queue
        } else {
            // Buffer is full, drop the incoming packet
            packetsDropped++;
        }
    }

    // Output results (unit in seconds)
    cout << "Incoming Packets: " << packets.size() << endl;
    cout << "Delivered Packets: " << (packets.size() - packetsDropped) << endl;
    cout << "Dropped Packets: " << packetsDropped << endl;
    cout << "Packet Loss Percentage: " << (static_cast<double>(packetsDropped) / packets.size()) * 100 << "%" << endl;
    cout << "Average Queuing Delay: " << (totalQueuingDelay / (packets.size() - packetsDropped)) << " seconds" << endl;
    cout << "Total Queueing Delay: " << totalQueuingDelay << " seconds" << endl;
}

int main(int argc, char* argv[]) {
    
    int bufferSize = 100;   // Size of the buffer capacity of packets, adjust as needed
    double wlanCapacity = 10.0; // WLAN speed in Mbps , adjust as needed

    cout << "File read: " << argv[1] << endl;
    cout << "Buffer Size: " << bufferSize << endl;
    cout << "WLAN Capacity: " << wlanCapacity << " Mbps" << endl;

    //Read input file passed through commandline argument
    auto streamPackets = parseInputFile(argv[1]);
    // Start of simulation
    runSimulation(streamPackets, bufferSize, wlanCapacity);

    return 0;
}