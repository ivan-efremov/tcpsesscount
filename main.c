/**
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <pcap.h>

#include "array_unique.h"


//#define VERBOSE 1


/**
 * @short Открытие файла *.pcap
 * @return Хендлер pcap
 */
pcap_t* pcapfile_open(const char* fname)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_offline(fname, errbuf);
    if(pcap == NULL) {
        fprintf(stderr, "pcapfile_open: error open file: %s\n", errbuf);
        exit(-2);
    }
    return pcap;
}


/**
 * @short Подсчет статистики по пакетам
 * Internet Datagram Header:
 *         0                   1                   2                   3
 *         0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |Version|  IHL  |Type of Service|          Total Length         |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |         Identification        |Flags|      Fragment Offset    |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |  Time to Live |    Protocol   |         Header Checksum       |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |                       Source Address                          |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |                    Destination Address                        |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *        |                    Options                    |    Padding    |
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
void pcapfile_do_statistic(pcap_t* pcap)
{
    long                       count = 0l;
    struct array_unique        sessions;
    const struct ether_header* ethernet;
    const struct iphdr*        ip;
    const struct tcphdr*       tcp;
    const u_char*              payload;
    
    const int                  sizeEthernet = sizeof(struct ether_header);
    const int                  sizeIp = sizeof(struct iphdr);
    const int                  sizeTcp = sizeof(struct tcphdr);
    
    struct pcap_pkthdr         header;
    const u_char*              packet = NULL;
    
    if(array_unique_init(&sessions, 2) == -1) {
        fprintf(stderr, "pcapfile_do_statistic: array_unique_init returned -1\n");
        exit(-3);
    }
    
    while((packet = pcap_next(pcap, &header)) != NULL) {
        ethernet = (const struct ether_header*)(packet);
        if(ntohs(ethernet->ether_type) == ETHERTYPE_IP) {
        #ifdef VERBOSE
            struct in_addr addr;
        #endif
            ip = (const struct iphdr*)(packet + sizeEthernet);
        #ifdef VERBOSE
            printf("ip.id: %04x\n", ntohs(ip->id));
            addr.s_addr = ip->saddr;
            printf("ip.saddr: %s\n", inet_ntoa(addr));
            addr.s_addr = ip->daddr;
            printf("ip.daddr: %s\n", inet_ntoa(addr));
        #endif
            if(ip->protocol == 0x06) {
                uint64_t hash = 0ul;
                tcp = (const struct tcphdr*)(packet + sizeEthernet + sizeIp);
                payload = (const u_char*)(packet + sizeEthernet + sizeIp + sizeTcp);
            #ifdef VERBOSE
                printf("tcp.sport: %hu\n", ntohs(tcp->th_sport));
                printf("tcp.dport: %hu\n", ntohs(tcp->th_dport));
                printf("tcp.flags: %02x\n", tcp->th_flags);
            #endif
                hash = ntohl(ip->saddr);
                hash += ntohl(ip->daddr);
                hash += ntohs(tcp->th_sport);
                hash += ntohs(tcp->th_dport);
            #ifdef VERBOSE
                printf("hash: %llu\n", hash);
            #endif
                if((tcp->th_flags & (TH_SYN | TH_ACK)) == (TH_SYN | TH_ACK)) {
                    array_unique_push(&sessions, hash);
                } else if((tcp->th_flags & (TH_PUSH | TH_ACK)) == (TH_PUSH | TH_ACK)) {
                    array_unique_push(&sessions, hash);
                } else if((tcp->th_flags & (TH_URG | TH_ACK)) == (TH_URG | TH_ACK)) {
                    array_unique_push(&sessions, hash);
                } else if(tcp->th_flags & TH_FIN) {
                    array_unique_erase(&sessions, hash);
                } else if(tcp->th_flags & TH_RST) {
                    array_unique_erase(&sessions, hash);
                }
            } else {
                printf("ip.protocol: %02x\n", ip->protocol);
            }
        #ifdef VERBOSE
            printf("===========================\n");
        #endif
        } else {
            printf("ethernet.ether_type: %04x\n", ntohs(ethernet->ether_type));
        }
        ++count;
    }
    printf("Total: %ld\n", count);
    printf("Sessions: %zu\n", array_unique_size(&sessions));
    array_unique_destroy(&sessions);
}


/**
 * @short Закрытие файла
 */
void pcapfile_close(pcap_t* pcap)
{
    pcap_close(pcap);
}



/**
 * 
 * @short Точка входа
 * 
 */
int main(int argc, const char** argv)
{
    pcap_t* pcap = NULL;
    if(argc != 2) {
        printf("Usage:\n\t%s dump.pcap\n", argv[0]);
        exit(-1);
    }
    pcap = pcapfile_open(argv[1]);
    pcapfile_do_statistic(pcap);
    pcapfile_close(pcap);
    return 0;
}
