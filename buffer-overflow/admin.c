#include <stdio.h>
#include <stdlib.h>

char *gets(char *s);

void view_logs() {
	FILE *file = fopen(".leak", "r");
	if (file == NULL) {
		printf("Error: Could not open logs.txt\n");
		return;
	}
	char line[256];
	printf("\n=== System Logs ===\n");
	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
	}
	printf("\n====================\n");

	fclose(file);
}

void main_menu() {
	printf("\nMain Menu:\n");
	printf("1. View system logs\n");
	printf("2. Exit\n");

	int choice;
	scanf("%d", &choice);
	getchar();
    
	switch (choice) {
		case 1:
			view_logs();
			break;
		case 2:
			printf("Goodbye!\n");
			exit(0);
		default:
			printf("Invalid choice.\n");
	}
}

void vuln() {
	char buffer[256];
	
	FILE *leak_file = fopen(".leak", "w");

	if (leak_file) {
		fprintf(leak_file, "Leaked: %p\n", buffer);
		fclose(leak_file);
	}
	
	printf("Press enter to access the vault:  \n");
	gets(buffer);
}

int main() {
	printf("=== Secure Vault === \n");
	printf("Warning: Legacy software detected. Upgrade recommended.\n");
	vuln();
	main_menu();
	return 0;
}
