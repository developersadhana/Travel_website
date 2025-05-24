#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "travel_log.txt"
#define MAX_INPUT 1024
#define CURRENT_TRIP_FILE "current_trip.txt"
#define EXPENDITURES_FILE "expenditures.csv"


typedef struct {
    char destination[100];
    char date[50];
    char highlights[1024];
} TravelEntry;

// Save a new entry to the text file
void createEntry() {
    TravelEntry entry;
    printf("\n");
    printf("~ Creating Entry ~\n");
    printf("Enter destination name: ");
    fgets(entry.destination, sizeof(entry.destination), stdin);
    entry.destination[strcspn(entry.destination, "\n")] = 0;

    printf("Enter date of visit: ");
    fgets(entry.date, sizeof(entry.date), stdin);
    entry.date[strcspn(entry.date, "\n")] = 0;

    printf("Enter highlights: ");
    fgets(entry.highlights, sizeof(entry.highlights), stdin);
    entry.highlights[strcspn(entry.highlights, "\n")] = 0;

    FILE *fp = fopen(FILE_NAME, "a"); // append mode
    if (!fp) {
        perror("Failed to open file");
        return;
    }


    fprintf(fp, "Destination: %s\n", entry.destination);
    fprintf(fp, "Date: %s\n", entry.date);
    fprintf(fp, "Highlights: %s\n", entry.highlights);
    fprintf(fp, "===\n"); // separator for entries

    fclose(fp);
    printf("Entry saved successfully.\n");
}


void viewEntries() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        perror("Could not open file");
        return;
    }

    printf("\n=== TRAVEL ENTRIES ===\n\n");

    char line[MAX_INPUT];
    int entryCount = 0;

    while (fgets(line, MAX_INPUT, fp)) {
        if (strcmp(line, "===\n") == 0 || strcmp(line, "===\r\n") == 0) {
            entryCount++;
            printf("-----------------------------\n");
        } else {
            printf("%s", line);
        }
    }

    if (entryCount == 0) {
        printf("No entries found.\n");
    }

    fclose(fp);
}

void writeJournal() {
    char destination[MAX_INPUT];
    
    printf("\n\n=== JOURNAL ===");
    printf("\nEnter destination name for journal: ");
    scanf("%s", destination);
    getchar(); 

   // snprintf(filename, MAX_FILENAME, "%s_journal.txt", destination);

    FILE *fp = fopen(strcat(destination,".txt"), "w");
    if (!fp) {
        perror("Could not create journal file");
        return;
    }

    char input[MAX_INPUT];

    printf("\n~ Writing journal ~\n");

    printf("\n1. What was the most memorable part of your trip?\n> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    fprintf(fp, "Most memorable moment: %s\n", input);

    printf("\n2.What markets or local products caught your eye?\n> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    fprintf(fp, "Local markets/products: %s\n", input);

    printf("\n3. What local cuisine did you try that you enjoyed the most?\n> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    fprintf(fp, "Favorite local cuisine: %s\n", input);

    printf("\n4. Would you visit this place again? Why?\n> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    fprintf(fp, "Would revisit? %s\n", input);

    printf("\n5. Rate the experience out of 10 eg.(?/10)\n> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    fprintf(fp, "Rating: %s/10\n", input);

    fclose(fp);
    printf("Journal saved!\n");
}

void new_trip()
{
    FILE * trip= fopen("Current_trip.txt","w");
    char destination[20];
    float budget;
    printf("Enter new trip destination: ");
    scanf("%s",destination);
    printf("Enter new trip budget: ");
    scanf("%f",budget);
    fprintf(trip,"%s %f",destination,budget);
    fclose(trip);
}



void pastMenu() {
    int choice;
    do {
        printf("\n=== MEMORIES OF PAST TRIPS ===\n");
        printf("1. Create a new destination entry\n");
        printf("2. View all entries\n");
        printf("3. Write journal\n");
        printf("4. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: createEntry(); break;
            case 2: viewEntries(); break;
            case 3: writeJournal();break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}


void futureSection() {
    int choice;
    do {
        printf("\n=== PLAN FUTURE TRIPS ===\n");
        printf("1. Browse Destinations near Bangalore\n");
        //printf("2. Already have a destination in mind?\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: 
            {
                system("start https://sharvanee08.github.io/travel-website/");
                break;
            }
            //case 2: break;
            case 2: break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 2);



}



void setCurrentTrip() {
    char destination[100];
    float budget;

    printf("Enter current destination: ");
    fgets(destination, sizeof(destination), stdin);
    destination[strcspn(destination, "\n")] = 0;

    printf("Enter trip budget(in numbers): ");
    scanf("%f", &budget);
    getchar(); 

    FILE *fp = fopen(CURRENT_TRIP_FILE, "w");
    if (!fp) {
        perror("Could not open file to save trip");
        return;
    }

    fprintf(fp, "Destination: %s\n", destination);
    fprintf(fp, "Budget: %.2f\n", budget);
    fclose(fp);

    
    fp = fopen(EXPENDITURES_FILE, "w");
    if (fp) fclose(fp);

    printf("New trip set successfully.\n");
}

/*void current_trip()
{
    FILE *fp = fopen(CURRENT_TRIP_FILE, "r");
    if (!fp) {
        printf("No ongoing trips found");
        return ;
    }

    printf("\n=== YOUR CURRENT TRIP ===\n\n");

    char line[MAX_INPUT];

    while (fgets(line, MAX_INPUT, fp)) {
        if (strcmp(line, "===\n") == 0 || strcmp(line, "===\r\n") == 0) {
            printf("-----------------------------\n");
        } else {
            printf("%s", line);
        }
    }
fclose(fp);
return;
}
*/

void addExpenditure() {
    char description[100];
    float amount;
    FILE * trip= fopen(CURRENT_TRIP_FILE,"r");
    if(trip==NULL)
    {
        printf("No ongoing trip.");
        fclose(trip);
        return;
    }
    fclose(trip);
    printf("\nEnter expenditure description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;

    printf("Enter amount spent: ");
    scanf("%f", &amount);
    getchar(); 

    FILE *fp = fopen(EXPENDITURES_FILE, "a");
    if (!fp) {
        perror("Could not open expenditures file");
        return;
    }

    fprintf(fp, "%s,%.2f\n", description, amount);
    fclose(fp);

    printf("Expenditure added.\n");
}


void viewTotalExpenditure() {
    FILE *fp = fopen(EXPENDITURES_FILE, "r");
    if (!fp) {
        perror("Could not open expenditures file");
        return;
    }

    float total = 0.0, amount;
    char line[256], desc[100];

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%[^,],%f", desc, &amount) == 2) {
            total += amount;
        }
    }

    fclose(fp);
    printf("\nTotal Expenditure: %.2f rupees\n", total);
    //FILE * expenditure =fopen("Current_trip.txt","r");
    
    
}

// End current trip (clear files)
void endTrip() {
    if (remove(CURRENT_TRIP_FILE) == 0 && remove(EXPENDITURES_FILE) == 0) {
        printf("\nTrip ended and all data cleared.\n");
        printf("Hope you enjoyed your trip!\n");
    } else {
        printf("Could not clear all trip data. Some files may be missing.\n");
    }
}

void Weather()
{
    FILE *fp=fopen(CURRENT_TRIP_FILE,"r");
    if(fp==NULL)
    {
        printf("No ongoing trip\n");
        return;
    }
    char waste[20],destination[20];
    fscanf(fp,"%s %s",waste,destination);
    //printf("DESTINATION: %s",destination);
    char url[512];
    char query[200]="Weather in ";
    strcat(query,destination);

    snprintf(url, sizeof(url), "https://www.google.com/search?q=%s", query);

    // Replace spaces with '+'
    for (int i = 0; url[i] != '\0'; i++) {
        if (url[i] == ' ') {
            url[i] = '+';
        }
    }

    // Open URL in default browser based on OS
    #if defined(_WIN32) || defined(_WIN64)
        char command[600];
        snprintf(command, sizeof(command), "start \"\" \"%s\"", url);
    #elif defined(__APPLE__)
        char command[600];
        snprintf(command, sizeof(command), "open \"%s\"", url);
    #elif defined(__linux__)
        char command[600];
        snprintf(command, sizeof(command), "xdg-open \"%s\"", url);
    #else
        printf("Unsupported OS\n");
        return;
    #endif

    system(command);

    fclose(fp);
    return;
}

// Present section menu
void presentSection() {
    int choice;
    do {
        printf("\n=== ENJOY YOUR ONGOING TRIP ===\n");
        printf("1. Start New Trip\n");
        printf("2. Add Expenditure\n");
        printf("3. View Total Expenditure\n");
        printf("4. Today's Weather\n");
        printf("5. End Current Trip\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: setCurrentTrip(); break;
            case 2: addExpenditure(); break;
            case 3: viewTotalExpenditure(); break;
            case 5: endTrip(); break;
            case 4: Weather();break;
            case 6: break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);
}





// Main function
int main() {
    int choice;
    do {
        printf("\n=== TRAVEL INNOVATORS MENU ===\n");
        printf("~ The past, present and future of travel ~\n");
        printf("1. Past Travels\n");
        printf("2. Present Travels\n");
        printf("3. Future Travels\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: pastMenu(); break;
            case 2: presentSection(); break;
            case 3: futureSection(); break;
            case 4: printf("\n=== Thank you for using Travel Innovators! ===\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}






