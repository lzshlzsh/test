#include <stdio.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <link.h>

static void print_link_map(const int *got)
{
	const struct link_map *link_map, *lnk_tmp;
	int i;

	for (i = 0; i < 3; i++){
		printf("got[%d] = %#x\n", i, got[i]);
	}

	link_map = (const struct link_map *)got[1];

	printf("Loaded images:\n");
	for (lnk_tmp = link_map; lnk_tmp; lnk_tmp = lnk_tmp->l_next){
		printf("\t%s: %#x\n", lnk_tmp->l_name, lnk_tmp->l_addr);
	}
	printf("\n***************\n\n");
}

int main(int argc, char **argv)
{
	int fd;
	int base, img_base;
	int i, dyna_sect_sz = 0;
	struct stat stat;
	const Elf32_Ehdr *ehdr;
	const Elf32_Shdr *shdr, *dyna_sect;
	const Elf32_Phdr *phdr;
	const char *strtab;
	const int *got = 0;



	if ((fd = open(argv[0], O_RDONLY)) < 0){
		perror("open");
		exit(errno);
	}

	if (fstat(fd, &stat) < 0){
		perror("fstat");
		exit(errno);
	}
	
	if (-1 == (base = (int)mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, 
					fd, 0))){
		perror("mmap");
		exit(errno);
	}

	if (close(fd) < 0){
		perror("close");
		exit(errno);
	}

	ehdr = (const Elf32_Ehdr *)base;
	phdr = (const Elf32_Phdr *)(base + ehdr->e_phoff);

	/*
	 * get the progress image's base address, for executable file, this 
	 * address is the same with the static address
	 */
	for (i = 0; i < ehdr->e_phnum; i++){
		if (PT_LOAD == phdr[i].p_type){
			img_base = phdr[i].p_vaddr;
			break;
		}
	}

	shdr = (const Elf32_Shdr *)(base + ehdr->e_shoff);

	strtab = (const char *)(base + shdr[ehdr->e_shstrndx].sh_offset);

	for (i = 0; i < ehdr->e_shnum; i++){
		if (!strcmp(".got.plt", strtab + shdr[i].sh_name)){
			got = (const int *)shdr[i].sh_addr;
			break;
		}
	}

	if (0 == got){
		/*try section .got*/
		for (i = 0; i < ehdr->e_shnum; i++){
			if (!strcmp(".got", strtab + shdr[i].sh_name)){
				got = (const int *)shdr[i].sh_addr;
				break;
			}
		}
	}
	
	assert(got);
	
	/*get .dynamic section*/
	for (i = 0; i < ehdr->e_shnum; i++){
		if (!strcmp(".dynamic", strtab + shdr[i].sh_name)){
			dyna_sect = shdr + i;
			dyna_sect_sz = dyna_sect->sh_size;
			break;
		}
	}

	/*temp map file is useless now, unmap it*/
	if (munmap((void *)base, stat.st_size) < 0){
		perror("munmap");
		exit(errno);
	}


	printf("one way to get got address(from .got.plt or .got ...)\n");
	
	print_link_map(got);

	/*another way to get got address*/
	for (i = 0; i < dyna_sect_sz / sizeof(Elf32_Dyn); i++){
		if (DT_PLTGOT == _DYNAMIC[i].d_tag){
			got =  (const int *)_DYNAMIC[i].d_un.d_ptr;
		}
	}
	
	printf("another way to get got address(from .dynamic ...)\n");
	print_link_map(got);

	return 0;
}
