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

3. [✅] **set up safe isolated docker environment for development and testing**
   * create a `docker-compose.yml` file to define four containers:
     - executable container: runs `ft_malcolm` with specified arguments and network access
     - source container: will be used to impersonate and alter the target’s ARP table
     - target container: will have its ARP table rewritten to redirect traffic intended for the source
     - destination container: a server to be pinged by the target to trigger ARP requests
   * define a custom network to ensure isolated communication among containers
   * configure a `Makefile` to automate container deployment and testing requirements

4. [✅] **identify and select an available network interface**
   * check for an available network interface

5. [✅] **implement signal handling**
   * exit gracefully on `SIGINT` and ensure resources are properly freed

6. [✅] **wait for the ARP request**
   * set up the socket and sending interface for the ARP protocol
   * wait for an ARP request broadcast from the target IP

7. [✅] **set timeout for ARP requests**
   * use `-t TIMEOUT` to define a timeout period (in seconds) for waiting for an ARP request

8. [✅] **ARP packet handling**
   * analyze received ARP request packet
   * set up ARP reply packet
   * send an ARP reply with spoofed source information upon receiving a request

9. [✅] **implement verbose output**
   * if `-v` is set, print packet details, including source and target IP/MAC addresses

10. [✅] **send gratuitous ARP broadcast (if `-g` is set)**
   * if `-g` is provided, broadcast an ARP packet to announce the spoofed IP and MAC association

11. [✅] **define exit conditions**
   * on completion (timeout or after ARP reply), close sockets and exit gracefully
