#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <elf.h>

void display_elf_header(const Elf64_Ehdr* header) {
	int i;

    printf("Magic:   ");
    for (i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
    printf("Class:				%s\n", header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "Unknown");
    printf("Data:				%s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "Unknown");
    printf("Version:				%d\n", header->e_ident[EI_VERSION]);
    printf("OS/ABI:				%d\n", header->e_ident[EI_OSABI]);
    printf("ABI Version:			%d\n", header->e_ident[EI_ABIVERSION]);
    printf("Type:				%d\n", header->e_type);
    printf("Entry point address:		%lx\n", header->e_entry);
}

int main(int ac, char **av) {
	Elf64_Ehdr header;
	int fd;

    if (ac != 2) {
	dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", av[1]);
	exit(98);
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
	dprintf(STDERR_FILENO, "Unable to open ELF file %s\n", av[1]);
	exit(98);
    }

    
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
	dprintf(STDERR_FILENO, "Unable to read ELF header from file %s\n", av[1]);
	exit(98);
    }

    if (header.e_ident[EI_MAG0] != ELFMAG0 || header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 || header.e_ident[EI_MAG3] != ELFMAG3) {
	dprintf(STDERR_FILENO, "Error: %s is not an ELF file\n", av[1]);
	exit(98);
    }

    display_elf_header(&header);

    close(fd);
    return 0;
}
