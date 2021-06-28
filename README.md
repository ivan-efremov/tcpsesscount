
tcpsesscount - show counter for TCP sessions

1. Build project
```
    $ sudo apt-get install libpcap-dev libcunit1-dev
    $ ./build.sh release
```

2. Create TCP test.pcap file
```
    $ cd bin
    $ sudo tcpdump port 443 -w test.pcap
```

3. Run program
```
    $ ./tcpsesscount test.pcap
    
    Total packages: 54
    TCP sessions active: 5
    TCP sessions terminated success: 1
    TCP Sessions disconnected: 0
```
