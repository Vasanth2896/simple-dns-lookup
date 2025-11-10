# 🔍 DNS Lookup Tool (C++)

A simple C++ command-line utility that performs DNS lookups using the `getaddrinfo()` API.  
It displays detailed information about the resolved IP addresses, including protocol family, socket type, and protocol type.

---

## 🧠 Overview

This tool resolves a given hostname (like `google.com`) into its corresponding IP addresses (IPv4 and/or IPv6).  
It uses modern C++ syntax (typedefs, `std::string`, clean function design) while still interacting directly with low-level POSIX networking APIs.

---

## ⚙️ Features

- Performs DNS lookups using the standard `getaddrinfo()` function  
- Supports both **IPv4** and **IPv6**
- Prints:
  - Address family (`AF_INET`, `AF_INET6`)
  - Socket type (`SOCK_STREAM`, `SOCK_DGRAM`)
  - Protocol type (`TCP`, `UDP`, etc.)
  - Human-readable IP addresses (via `inet_ntop()`)
- Clean and modular C++ implementation

---

## Learning Sources
- Beej's guide to Network Programming
- Daniel Hirsch's youtube video on Coding DNS lookup from scratch in C.

## Sample Input
```bash
./lookup google.com
```

## Sample Output
```bash
Performing DNS lookup for google.com
DNS Lookup for google.com
Family: IPv4
SocketType: TCP/IP
Protocol: TCP
IPv4: 142.250.195.78

Family: IPv6
SocketType: TCP/IP
Protocol: TCP
IPv6: 2607:f8b0:4004:c17::66
```

Vasanth Nayak.
Embedded Software Developer

