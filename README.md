
tcpsesscount - show counter for TCP sessions

Build:
```
    $ sudo apt-get install libpcap-dev libcunit1-dev
    $ ./build.sh release
    $ bin/tcpsesscount test.pcap
    
    Total packages: 54
    Sessions active: 5
    Sessions terminated success: 1
    Sessions disconnected: 0
```
