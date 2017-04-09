#include <dlfcn.h> 
#include <link.h>
#include <elf.h>
#include <stdio.h> 

static void print_elf(const Elf32_Ehdr *elf_h)
{
	printf("entry: 0x%x\n", elf_h->e_entry);
	const Elf32_Phdr *ph_tab = (Elf32_Phdr *)((int)elf_h + elf_h->e_phoff);
	int i = 0;
	for (; i < elf_h->e_phnum; i++){
		const Elf32_Phdr *ph = ph_tab + i;
		if (ph->p_flags & PF_X)
		  printf("0x%x - 0x%x\n", (int)elf_h + ph->p_offset, (int)elf_h + ph->p_offset + ph->p_memsz);
	}
}
int main() 
{ 
	void *libc; 
	void (*printf_call)();
	char* error_text; 
	if((libc = dlopen("/lib64/libc.so.6", RTLD_NOW /*RTLD_LAZY*/))){ 
		struct link_map *lm = (struct link_map *)libc;
		printf("sizeof(struct link_map): %d\n", sizeof(struct link_map));
		printf_call = dlsym(libc,"printf"); 
		(*printf_call)("hello, world\n"); 
		for (; lm; lm = lm->l_next){
			printf("========\n");
			printf("%s: 0x%x, %p\n", lm->l_name, lm->l_addr, lm->l_ld);
			Elf32_Ehdr *elf_h = (Elf32_Ehdr *)(lm->l_addr);
			if (elf_h)
			  print_elf(elf_h);
		}
		dlclose(libc);
		return 0;
	}
	error_text= dlerror();
	printf("%s\n", error_text);
	return 0;
}
