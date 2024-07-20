#include <stdio.h>
#include <stdlib.h>  
#include <elf.h>

#define FILE_PATH "taskv2.elf"

int main() {
    FILE *elffile = fopen(FILE_PATH, "r");  // Open in binary mode
    if (elffile == NULL) {
        printf("Failed to open file!!\n");
        return EXIT_FAILURE;  // Exit with failure status
    }

    Elf64_Ehdr elfheader;
    size_t bytesRead = fread(&elfheader, sizeof(elfheader), 1, elffile);
    if (bytesRead != 1) {
        printf("Failed to read ELF header\n");
        fclose(elffile);
        return EXIT_FAILURE;  // Exit with failure status
    }else{
    
	    //uint32_t *ptr=(uint32_t*)&elfheader.e_ident[0];
	    printf("Magic:       		 %02X %02X %02X %02X %02X %02X  %02X %02X %02x %02X %02X %02X %02X %02X  %02X %02X\n",elfheader.e_ident[0], elfheader.e_ident[1],
            elfheader.e_ident[2], elfheader.e_ident[3],
            elfheader.e_ident[4],elfheader.e_ident[5], elfheader.e_ident[6],
            elfheader.e_ident[7],elfheader.e_ident[8], elfheader.e_ident[9],
            elfheader.e_ident[10], elfheader.e_ident[11],
            elfheader.e_ident[12],elfheader.e_ident[13], elfheader.e_ident[14],
            elfheader.e_ident[15]);
            
            
            
            switch(elfheader.e_ident[EI_CLASS ]){
            	case 0:
	    		printf("class:					(NONE)\n");break;
	    	case 1:
	    		printf("class:					ELF32\n");break;
	    	case 2:
	    		printf("class:					ELF64\n");break;
	    	default:
	    		printf("invalid\n");
            }
            switch(elfheader.e_ident[EI_DATA]){
            	case 0:
	    		printf("Data:					Invalid data encoding\n");break;
	    	case 1:	
	    		printf("Data:					2's complement, little endian\n");break;
	    	case 2:
	    		printf("Data:					2's complement, big endian\n");break;
	    	default:
	    		printf("invalid\n");
            }
            switch(elfheader.e_version){
	    	case 0:
	    		printf("Vesrion:				%i (NONE)\n", elfheader.e_version);break;
	    	case 1:
	    		printf("Vesrion:				%i (CURRENT)\n", elfheader.e_version);break;
	    	case 2:
	    		printf("Vesrion:				%i (NUM)\n", elfheader.e_version);break;
	    	default:
	    		printf("invalid\n");
	    }
	    
	    
	    switch(elfheader.e_ident[EI_OSABI ]){
            	case 0:
	    		printf("OS/ABI:					UNIX System V ABI\n");break;
	    	case 3:	
	    		printf("OS/ABI:					UNIX - GNU\n");break;
	    	case 64:
	    		printf("OS/ABI:					ARM EABI\n");break;
	    	case 97:	
	    		printf("OS/ABI:					ARM\n");break;
	    	case 255:
	    		printf("OS/ABI:					Standalone (embedded) application \n");break;
	    	default:
	    		printf("invalid\n");
            }
            printf("ABI Version:				%i\n",elfheader.e_ident[EI_ABIVERSION]);
	    
	    if(0==elfheader.e_type){
	    	printf("Type :					NONE\n");
	    }else if(1==elfheader.e_type){
	    	printf("Type :					REL\n");
	    }else if(2==elfheader.e_type){
	    	printf("Type :					EXEC\n");	
	    }else if(3==elfheader.e_type){
	    	printf("Type :					DYN\n");
	    }else if(4==elfheader.e_type){
	    	printf("Type :					CORE\n");		
	    }	
	    switch(elfheader.e_machine){
	    	case 0:
	    		printf("machine:				NONE\n");break;
	    	case 1:
	    		printf("machine:				M32\n");break;
	    	case 2:
	    		printf("machine					SPARC\n");break;
	    	case 3:
	    		printf("machine:				386\n");break;/* Intel 80386 */
	    	case 4:
	    		printf("machine:				68K\n");break;/* Motorola m68k family */
	    	case 5:
	    		printf("machine:				88K\n");break;/* Motorola m88k family */
	    	case 6:
	    		printf("machine:				IAMCU\n");break;/* Intel MCU */
	    	case 7:
	    		printf("machine:				860\n");break;
	    	case 8:
	    		printf("machine:				MIPS\n");break;
	    	case 9:
	    		printf("machine:				S370\n");break;
	    	case 40:
	    		printf("machine:				ARM\n");break;
	    	case 60:	
	    		printf("machine:				ST100\n");/*STMicroelectronic ST100 processor*/
	    		break;	
		case 100:
	    		printf("machine:				ST200\n");/*STMicroelectronic ST200 processor*/
	    		break;
	    	case 62:
	    		printf("machine:				Advanced Micro Devices X86_64\n");break;
	    	case 63:
	    		printf("machine:				PDSP\n");break;/* Sony DSP Processor */
	    	case 185:
	    		printf("machine:				AVR32\n");break;/* Amtel 32-bit microprocessor */
	    	case 186:	
	    		printf("machine:				STM8\n");break;/* STMicroelectronics STM8 */

	    	default:
	    		printf("invalid\n");
	    }
	    switch(elfheader.e_version){
	    	case 0:
	    		printf("Vesrion:				0x%x \n", elfheader.e_version);break;
	    	case 1:
	    		printf("Vesrion:				0x%x \n", elfheader.e_version);break;
	    	case 2:	
	    		printf("Vesrion:				0x%x\n", elfheader.e_version);break;
	    	default:
	    		printf("invalid\n");
	    }
	   
	    
	    printf("entry point address: 			0x%x\n",elfheader.e_entry);
	    printf("start of program headers:		%i(bytes into files)\n",elfheader.e_phoff);
	    printf("start of section headers:		%i(bytes into files)\n",elfheader.e_shoff);
	    printf("flags:					0x%x\n",elfheader.e_flags);
	    printf("size of this header:			%i(bytes)\n",elfheader.e_phoff);
	    printf("size of program headers:		%i(bytes)\n",elfheader.e_phentsize);
	    
	    printf("number of program headers:		%i\n",elfheader.e_phnum);
	    printf("size of section headers:		%i(bytes)\n",elfheader.e_shentsize);
	    printf("number of section headers:		%i\n",elfheader.e_shnum);
	    
	    printf("section header string table index:	%i\n",elfheader.e_shstrndx);
    }	
    fclose(elffile);
    return EXIT_SUCCESS;  // Exit with success status
}
