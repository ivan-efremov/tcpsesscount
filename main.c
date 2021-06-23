/**
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>


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
 */
void pcapfile_do_statistic(pcap_t* pcap)
{
    long count = 0l;
    struct pcap_pkthdr header;
    const u_char* packet = NULL;
    while((packet = pcap_next(pcap, &header)) != NULL) {
        ++count;
    }
    printf("Total: %ld\n", count);
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
