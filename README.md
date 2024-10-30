# ft_malcolm
An introduction to Man in the Middle attacks.

## project plan

1. [✅] **create a command-line argument parser to validate user input**
   * parse mandatory arguments: source IP, source MAC, target IP, and target MAC
   * validate optional flags:
     - `-v`: enable verbose mode to print detailed packet information
     - `-g`: send a gratuitous ARP broadcast
     - `-t TIMEOUT`: set a timeout (1-300 seconds) to wait for an ARP request
     - `--help`: display usage information and exit

2. [✅] **validate input**
   * verify that IP and MAC addresses follow valid formats
   * display appropriate error messages for invalid or unresolvable addresses
   * resolve IP addresses to hostnames if possible

3. [✅] **identify and select an available network interface**
   * check for an available network interface (e.g. `eth0` for the testing environment)

4. [❌] **initialize ARP packets**
   * set up ARP request and reply packets:
     - use spoofed source IP and MAC addresses
     - set target IP and MAC to impersonated addresses

5. [❌] **wait for and respond to ARP requests**
   * wait for an ARP request broadcast from the target IP
   * send an ARP reply with spoofed source information upon receiving a request

6. [❌] **implement signal handling**
   * exit gracefully on `SIGINT` and ensure resources are properly freed

7. [❌] **implement verbose output**
   * if `-v` is set, print packet details, including source and target IP/MAC addresses

8. [❌] **set timeout for ARP requests**
   * use `-t TIMEOUT` to define a timeout period (in seconds) for waiting for an ARP request

9. [❌] **send gratuitous ARP broadcast (if `-g` is set)**
   * if `-g` is provided, broadcast an ARP packet to announce the spoofed IP and MAC association

10. [❌] **define exit conditions**
   * on completion (timeout or after ARP reply), close sockets and exit gracefully
