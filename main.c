#include <stdio.h>
#include <stdlib.h>

#define LINE 256


// create file if not it doesn't exist
void createFile(const char* filename)
{
	FILE* file = fopen(filename,"a");
	if (file == NULL)
	{
		printf("Failed to create file\n");
	}
	fclose(file);
}

// create new note
void newNote(const char* filename)
{
	char newNote[LINE];
	printf("inserting new note: ");
	fgets(newNote, sizeof(newNote), stdin);

	FILE* file = fopen(filename,"a");
	fprintf(file, "%s",newNote);
	fclose(file);
}

// print all notes to the screen
void listAllNotes(const char* filename)
{
	FILE* file = fopen(filename,"r");
	char line[LINE];

	// clear screen
	system("clear");	

	printf("\nListing all notes:\n");
	int lineNumber = 1;
	while (fgets(line, sizeof(line), file) !=NULL)
	{
		printf("%d - %s",lineNumber, line);
		lineNumber++;
	}

	fclose(file);
}

// delete one note (create temp file without the line)
void deleteNote(const char* filename)
{
	listAllNotes(filename); // list all

	FILE* file = fopen(filename, "r");

	// create temp file
	FILE* tempFile = fopen("temp.txt","w");	

	char line[LINE];
	int currentLine = 1;

	int lineToDelete;
	printf("Which note to delete: ");
	scanf("%d", &lineToDelete);
	

	while (fgets(line, sizeof(line), file) != NULL)
	{
		// if the line is not the one to delete execute
		if (currentLine != lineToDelete)
		{
			fputs(line, tempFile); // write line to temp file
		}
		currentLine++;
	}
	fclose(file);
	fclose(tempFile);

	// Delete original
    	if (remove(filename) != 0) {
       		printf("Failed to delete the original file.\n");
        	return;
    	}

    	// Rename the temporary file to the original filename
    	if (rename("temp.txt", filename) != 0) {
       		printf("Failed to rename the temporary file.\n");
        	return;
    	}	
}

int main() 
{
	const char* filename = "notes.txt";

	createFile(filename);

	int choice;
	printf("Enter a number\n1 - add new note\n2 - list all notes\n3 - Delete a note\n\nYour choice: ");
	scanf("%d", &choice);
	getchar(); // to consume \n from scanf buffer

	switch (choice) {
		case 1:
			newNote(filename);
			break;
		case 2:
			listAllNotes(filename);
			break;
		case 3:
			deleteNote(filename);		
			break;

		// everything else
		default: 
			printf("Invalid Choice");
			break; 
	}

	return 0;
}
