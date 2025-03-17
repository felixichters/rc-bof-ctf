
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DELAY 500000

int main(int argc, char * argv[]) { 
	char * fileName = argv[1];
	char buffer[1028];
	int i;
	FILE * fileHandler;

	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		return 1;
	}
	buffer[strcspn(buffer, "\n")] = 0;

	if(!access(fileName, W_OK)) {
		for(i = 0; i < DELAY;i++) {
			int a = i ^ 2;
		}

		fileHandler = fopen(fileName, "w"); 
		fwrite(buffer, sizeof(char), strlen(buffer), fileHandler); 
		fclose(fileHandler);
	} else {
		printf("No permission");
	}
}
