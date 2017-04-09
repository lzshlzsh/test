#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_PARTITIONS 4

typedef unsigned int uint32_t;

struct chs {
  unsigned char head;
  unsigned char sector;
  unsigned char cylinder;
} __attribute__((packed));

struct mbr {
  const unsigned char unused[446];
  struct mbr_partition {
    unsigned char status;
    struct chs first_sector; /* first absolute sector */
    unsigned char type;
    struct chs last_sector; /*last absolute sector */
    uint32_t first_lba; /* first absolute sector */
    uint32_t sectors; /* number of sectors */
  } partitions[MAX_PARTITIONS];
  unsigned char magic[2]; 
} __attribute__((packed));

static int dump_mbr(const struct mbr *mbr)
{
    int i;

    printf("\033[32mPARTITON\033[0m\n");
    for (i = 0; i < MAX_PARTITIONS; i++) {
        printf("partion %d:\n", i);
        printf("\tstatus 0x%02x\n", mbr->partitions[i].status);
        printf("\tfirst_sector: head %d, sector %d, cylinder %d\n", 
                mbr->partitions[i].first_sector.head, 
                mbr->partitions[i].first_sector.sector, 
                mbr->partitions[i].first_sector.cylinder);
        printf("\ttype %d\n", mbr->partitions[i].type);
        printf("\tlast_sector: head %d, sector %d, cylinder %d\n", 
                mbr->partitions[i].last_sector.head, 
                mbr->partitions[i].last_sector.sector, 
                mbr->partitions[i].last_sector.cylinder);
        printf("\tfirst_lba %d\n", mbr->partitions[i].first_lba);
        printf("\tsectors %d\n", mbr->partitions[i].sectors);
    }
    printf("\033[32mMAGIC %x %x\033[0m\n", mbr->magic[0], mbr->magic[1]);
    return 0;
}

int main(int argc, char **argv)
{
    int fd;
    struct mbr *mbr;

    if (argc < 2) {
        printf("Usage: %s mbrfile\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    mbr = (struct mbr *)mmap(NULL, sizeof(*mbr), PROT_READ, 
            MAP_PRIVATE, fd, 0);

    if (MAP_FAILED == (void *)mbr) {
        perror("mmap");
        close(fd);
        return -1;
    }
    close(fd);

    (void)dump_mbr(mbr);

    munmap(mbr, sizeof(*mbr));

    return 0;
}


