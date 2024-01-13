## RouterSim

### Overview

#### Router Queue Simulation

This program, written in C++, simulates the packet processing within a router queue. It takes into account various parameters such as buffer size and WLAN capacity. The simulation has been rigorously tested using `zoom.txt` and `stream.txt` trace files, provided by the course instructor Janet Leahy. Compatibility checks were conducted on both a personal Mac computer and Linux CPSC servers.

### Usage

#### Compilation

To compile this program, ensure that your C++ compiler supports C++11 or later versions.

**Command to compile on macOS:**
```
clang++ -std=c++11 -o siu simulation.cpp
```

#### Execution

Run the compiled executable, passing the name of the input file (either `zoom.txt` or `stream.txt`) as a command-line argument.

**Example command for execution on macOS:**
```
./siu zoom.txt
```

#### Adjustable Parameters

Within the main function, you can modify `bufferSize` and `wlanCapacity` to simulate different network scenarios.

### Sample Output

```
File read: zoom.txt
Buffer Size: 100
WLAN Capacity: 10 Mbps
Incoming Packets: 712841
Delivered Packets: 712841
Dropped Packets: 0
Packet Loss Percentage: 0%
Average Queuing Delay: 0.00387264 seconds
Total Queuing Delay: 2760.57 seconds
```

### File Structure

- `simulation.cpp`: Main program file.
- Additional trace files (e.g., `zoom.txt`, `stream.txt`).

### Dependencies

- C++11 or higher.
- Libraries:
  - `<iostream>`
  - `<fstream>`
  - `<queue>`
  - `<vector>`

### Assumptions

- The `bufferSize` and `wlanCapacity` should be adjusted according to specific network configurations and requirements.
- Input files must follow the prescribed format, containing timestamp and packet size data.
- Extremely large input files should be avoided to prevent simulation performance issues.

---

*Created by Mohammad Mahtab Khan*
