#include <stdio.h>
#include <elf.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void print(char *first, char *addr, Elf32_Rel *rel, Elf32_Sym *sym, char *str)
{
#if 1	
	printf("%p - %s\n", addr, str + sym[ELF32_R_SYM(rel[(addr - first) / 0x10].r_info)].st_name);
#else
	int i, j;
	
	i = (addr - first) / 0x10;
	j = ELF32_R_SYM(rel[i].r_info);
	printf("%d, %d, ", i, j);
	printf("%p - %s\n", addr, str + sym[j].st_name);
#endif
}

int main(int argc, char **argv)
{
	int fd, err;
	char *addr_fp10;
	struct stat stat;
	Elf32_Ehdr *e_hdr;
	Elf32_Shdr *s_hdr, *sh_plt = NULL, *sh_relplt = NULL;
	Elf32_Shdr *sh_sym, *sh_symstr;
	Elf32_Rel *rel_relplt;
	Elf32_Sym *sym_sym;
	char *sh_str, *sym_str;
	char *addr_plt, *addr;
	int i;

	fd = open("/home/lzs/flashplayer10", O_RDONLY);
	if (-1 == fd){
		perror("open");
		exit(-1);
	}
	
	err = fstat(fd, &stat);
	if (-1 == err){
		perror("fstat");
		exit(-1);
	}

	addr_fp10 = (char *)mmap(0, stat.st_size, PROT_READ, MAP_SHARED, 
			fd, 0);
	if (MAP_FAILED == (void *)addr_fp10){
		perror("mmap");
		exit(-1);
	}
	
	e_hdr = (Elf32_Ehdr *)addr_fp10;
	s_hdr = (Elf32_Shdr *)(addr_fp10 + e_hdr->e_shoff);

	assert(SHN_UNDEF != e_hdr->e_shstrndx);
	sh_str = addr_fp10 + s_hdr[e_hdr->e_shstrndx].sh_offset;
	
	for (i = 0; i < e_hdr->e_shnum; i++){
		if (!strcmp(".plt", sh_str + s_hdr[i].sh_name)){
			sh_plt = &s_hdr[i];
		}else if (!strcmp(".rel.plt", sh_str + s_hdr[i].sh_name)){
			sh_relplt = &s_hdr[i];
		}
		if (sh_plt && sh_relplt)
			break;
	}

	assert(sh_plt && sh_relplt);
	
	addr_plt = addr_fp10 + sh_plt->sh_offset + 0x10;
	
	rel_relplt = (Elf32_Rel *)(addr_fp10 + sh_relplt->sh_offset);

	sh_sym = &s_hdr[sh_relplt->sh_link];
	sym_sym = (Elf32_Sym *)(addr_fp10 + sh_sym->sh_offset);
	sh_symstr = &s_hdr[sh_sym->sh_link];

	sym_str = addr_fp10 + sh_symstr->sh_offset;

	for (addr = addr_plt; addr < addr_fp10 + sh_plt->sh_offset + sh_plt->sh_size;
			addr += 0x10){
		print(addr_plt, addr, rel_relplt, sym_sym, sym_str);
	}
		
	munmap(addr_fp10, stat.st_size);	
	close(fd);	
	return 0;
}
