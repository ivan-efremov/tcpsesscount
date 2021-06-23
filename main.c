#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>


pcap_t* pcapfile_open(const char* fname)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_offline(fname, errbuf);
    if(pcap == NULL) {
        fprintf(stderr, "Error open file %s: %s\n", fname, errbuf);
        exit(-1);
    }
    return pcap;
}

void pcapfile_do_statistic(pcap_t* pcap)
{
}

void pcapfile_close(pcap_t* pcap)
{
    pcap_close(pcap);
}




int main(int argc, const char** argv)
{
    pcap_t* pcap = pcapfile_open(argv[1]);
    pcapfile_do_statistic(pcap);
    pcapfile_close(pcap);
    return 0;
}
