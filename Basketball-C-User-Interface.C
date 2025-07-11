#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RECORDS 1000

// defining structure using ty
typedef struct {
  // defining all the vars used
  char season[8];
  int age;
  char team[4];
  char league[4];
  char position[3];
  int games;
  int gamesStarted;
  float minutesPerGame;
  float fieldGoals;
  float fieldGoalAttempts;
  float fieldGoalPercentage;
  float threePoint;
  float threePointAttempts;
  float threePointPercentage;
  float twoPoint;
  float twoPointAttempts;
  float twoPointPercentage;
  float effectiveFieldGoalPercentage;
  float freeThrows;
  float freeThrowAttempts;
  float freeThrowPercentage;
  float offensiveRebounds;
  float defensiveRebounds;
  float totalRebounds;
  float assists;
  float steals;
  float blocks;
  float turnovers;
  float personalFouls;
  float points;
  char awards[100];
} Record;

// makes an array of records with 1000 spaces I was told this decleration of a
// var is ok during check in.
Record records[MAX_RECORDS];

// Function Declarations
// delete
void deleteRecord(int *recordCount);
// prints menu
void printMenu(void);
// reads file
void readRecordsFromFile(const char *filename, int *recordCount);
// writes to file
void writeRecordsToFile(const char *filename, int *recordCount);
// displays all stats in file
void displayAllRecords(int *recordCount);
// sorts the record
void sortRecords(int option, int *recordCount);
// searches the record either by season or age
int searchRecord(char *param, int *recordCount);
// deals with invalid input
void handleInvalidInput(void);
// prints record for search so I don't have 20 lines for each print
void printRecordDetails(int index, int *recordCount);
// adds a record
void addRecord(int *recordCount);

int main(void) {
  int recordCount = 0;
  int choice;
  // The user must call a file before anything can be done
  char filename[100];

  while (1) {
    printMenu();
    if (scanf("%d", &choice) != 1) {
      handleInvalidInput();
      continue;
    }
    int bob;
    switch (choice) {
    case 1:
      printf("If you would like to use default file LS.txt press 0. If you "
             "wish to use a personal file press 1.");
      scanf("%d", &bob);
      if (bob) {
        printf("Enter filename to load records from. (Please use non digit "
               "values for file names): ");
        scanf("%s", filename);
        readRecordsFromFile(filename, &recordCount);
      } else {
        readRecordsFromFile("Jokic.txt", &recordCount);
      }
      break;
    case 2:
      displayAllRecords(&recordCount);
      break;
    case 3:
      printf("Press 1 to sort by age, 2 to sort by points, and 3 to sort by "
             "team (Alphabetically)\n");
      int option;
      scanf("%d", &option);
      sortRecords(option, &recordCount);
      break;
    case 4:
      printf("Enter age or season to search (e.g., 22 or 2008-09): ");
      char searchParam[20];
      scanf("%s", searchParam);
      searchRecord(searchParam, &recordCount);
      break;
    case 5:
      printf("Enter filename to save records to: ");
      scanf("%s", filename);
      writeRecordsToFile(filename, &recordCount);
      break;
    case 6:
      addRecord(&recordCount);
      break;
    case 7:
      deleteRecord(&recordCount);
      break;
    case 0:
      printf("Exiting program.\n");
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}

// prints menu
void printMenu(void) {
  printf("\nAvailable options:\n");
  printf("1. Load Records\n");
  printf("2. Display All Records\n");
  printf("3. Sort Records\n");
  printf("4. Search Records by Age or Season.\n");
  printf("5. Save Records\n");
  printf("6. Add Records\n");
  printf("7. Delete Record\n");
  printf("0. Exit\n");
  printf("Select an option: ");
}

void readRecordsFromFile(const char *filename, int *recordCount) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  // Skip the header line
  char buffer[1024];
  fgets(buffer, sizeof(buffer), fp);
  int scannedForFile = 0;
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL &&
         *recordCount < MAX_RECORDS) {
    Record record;
    int scanned = sscanf(
        buffer,
        "%7[^,],%d,%3[^,],%3[^,],%2[^,],%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"
        "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%99[^\n]",
        record.season, &record.age, record.team, record.league, record.position,
        &record.games, &record.gamesStarted, &record.minutesPerGame,
        &record.fieldGoals, &record.fieldGoalAttempts,
        &record.fieldGoalPercentage, &record.threePoint,
        &record.threePointAttempts, &record.threePointPercentage,
        &record.twoPoint, &record.twoPointAttempts, &record.twoPointPercentage,
        &record.effectiveFieldGoalPercentage, &record.freeThrows,
        &record.freeThrowAttempts, &record.freeThrowPercentage,
        &record.offensiveRebounds, &record.defensiveRebounds,
        &record.totalRebounds, &record.assists, &record.steals, &record.blocks,
        &record.turnovers, &record.personalFouls, &record.points,
        record.awards);

    if (scanned < 30) { // Check if all fields were successfully read
      // printf("Error parsing record: invalid format\n");
      continue;
    }

    // Add the successfully parsed record to the array
    if (*recordCount < MAX_RECORDS) {
      records[(*recordCount)++] = record;
      scannedForFile++;
    } else {
      printf("Maximum number of records reached.\n");
    }
  }

  fclose(fp);
  printf("Loaded %d records from %s\n", scannedForFile, filename);
}

// iterates through away printing
void displayAllRecords(int *recordCount) {

  if (*recordCount == 0) {
    printf("No records to display.\n");
    return;
  }

  //
  int i;
  for (i = 0; i < *recordCount; i++) {

    printf("Season: %s\n", records[i].season);
    printf("Age: %d\n", records[i].age);
    printf("Team: %s\n", records[i].team);
    printf("League: %s\n", records[i].league);
    printf("Position: %s\n", records[i].position);
    printf("Games: %d, Games Started: %d\n", records[i].games,
           records[i].gamesStarted);
    printf("Minutes Per Game: %.1f\n", records[i].minutesPerGame);
    printf("FG: %.1f, FGA: %.1f, FG%%: %.3f\n", records[i].fieldGoals,
           records[i].fieldGoalAttempts, records[i].fieldGoalPercentage);
    printf("3P: %.1f, 3PA: %.1f, 3P%%: %.3f\n", records[i].threePoint,
           records[i].threePointAttempts, records[i].threePointPercentage);
    printf("2P: %.1f, 2PA: %.1f, 2P%%: %.3f\n", records[i].twoPoint,
           records[i].twoPointAttempts, records[i].twoPointPercentage);
    printf("eFG%%: %.3f\n", records[i].effectiveFieldGoalPercentage);
    printf("FT: %.1f, FTA: %.1f, FT%%: %.3f\n", records[i].freeThrows,
           records[i].freeThrowAttempts, records[i].freeThrowPercentage);
    printf("Offensive Rebounds: %.1f, Defensive Rebounds: %.1f, Total "
           "Rebounds: %.1f\n",
           records[i].offensiveRebounds, records[i].defensiveRebounds,
           records[i].totalRebounds);
    printf("Assists: %.1f, Steals: %.1f, Blocks: %.1f, Turnovers: %.1f, "
           "Personal Fouls: %.1f, Points: %.1f\n",
           records[i].assists, records[i].steals, records[i].blocks,
           records[i].turnovers, records[i].personalFouls, records[i].points);
    printf("Awards: %s\n", records[i].awards);
    // Adds a blank line
    printf("\n");
  }
}
// sorts records
void sortRecords(int option, int *recordCount) {
  int i, j;
  if (option == 1) { // Sort by age
    for (i = 0; i < *recordCount - 1; i++) {
      for (j = 0; j < *recordCount - i - 1; j++) {
        if (records[j].age > records[j + 1].age) {
          Record temp = records[j];
          records[j] = records[j + 1];
          records[j + 1] = temp;
        }
      }
    }
    printf("Records sorted by age.\n");
  } else if (option == 2) { // Sort by points
    for (i = 0; i < *recordCount - 1; i++) {
      for (j = 0; j < *recordCount - i - 1; j++) {
        if (records[j].points > records[j + 1].points) {
          Record temp = records[j];
          records[j] = records[j + 1];
          records[j + 1] = temp;
        }
      }
    }
    printf("Records sorted by points (lowest to highest).\n");
  } else if (option == 3) { // Sort by team
    for (i = 0; i < *recordCount - 1; i++) {
      for (j = 0; j < *recordCount - i - 1; j++) {
        if (strcmp(records[j].team, records[j + 1].team) > 0) {
          Record temp = records[j];
          records[j] = records[j + 1];
          records[j + 1] = temp;
        }
      }
    }
    printf("Records sorted by team name.\n");
  } else {
    printf("Invalid sorting option. Use 1 for age, 2 for points, or 3 for "
           "team.\n");
  }
}
// searches records
int searchRecord(char *param, int *recordCount) {
  int age;
  int found = 0;

  // Check if the input parameter contains a hyphen, indicating a potential
  if (strstr(param, "-") != NULL) {
    // S
    for (int i = 0; i < *recordCount; i++) {
      // Directly compare the season strings
      if (strcmp(records[i].season, param) == 0) {
        // no need for & as it enters the func an adress
        printRecordDetails(i, recordCount);
        found = 1;
      }
    }
  } else if (sscanf(param, "%d", &age) ==
             1) { // Try to parse the input as an integer for age
    // Age search logic
    for (int i = 0; i < *recordCount; i++) {
      if (records[i].age == age) {
        printRecordDetails(i, recordCount);
        found = 1;
      }
    }
  } else {
    printf("Invalid search parameter. Use format 'YYYY-YY' for seasons or an "
           "integer for age.\n");
    return -1;
  }

  if (!found) {
    printf("No records found for %s.\n", param);
    return -1;
  }
  return 0;
}
// prints records for search an delete
void printRecordDetails(int index, int *recordCount) {
  printf("\nRecord found:\n");
  printf("Season: %s\n", records[index].season);
  printf("Age: %d\n", records[index].age);
  printf("Team: %s\n", records[index].team);
  printf("League: %s\n", records[index].league);
  printf("Position: %s\n", records[index].position);
  printf("Games: %d\n", records[index].games);
  printf("Games Started: %d\n", records[index].gamesStarted);
  printf("Minutes Per Game: %.1f\n", records[index].minutesPerGame);
  printf("Field Goals: %.1f\n", records[index].fieldGoals);
  printf("Field Goal Attempts: %.1f\n", records[index].fieldGoalAttempts);
  printf("Field Goal Percentage: %.3f\n", records[index].fieldGoalPercentage);
  printf("Three Points: %.1f\n", records[index].threePoint);
  printf("Three Point Attempts: %.1f\n", records[index].threePointAttempts);
  printf("Three Point Percentage: %.3f\n", records[index].threePointPercentage);
  printf("Two Points: %.1f\n", records[index].twoPoint);
  printf("Two Point Attempts: %.1f\n", records[index].twoPointAttempts);
  printf("Two Point Percentage: %.3f\n", records[index].twoPointPercentage);
  printf("Effective Field Goal Percentage: %.3f\n",
         records[index].effectiveFieldGoalPercentage);
  printf("Free Throws: %.1f\n", records[index].freeThrows);
  printf("Free Throw Attempts: %.1f\n", records[index].freeThrowAttempts);
  printf("Free Throw Percentage: %.3f\n", records[index].freeThrowPercentage);
  printf("Offensive Rebounds: %.1f\n", records[index].offensiveRebounds);
  printf("Defensive Rebounds: %.1f\n", records[index].defensiveRebounds);
  printf("Total Rebounds: %.1f\n", records[index].totalRebounds);
  printf("Assists: %.1f\n", records[index].assists);
  printf("Steals: %.1f\n", records[index].steals);
  printf("Blocks: %.1f\n", records[index].blocks);
  printf("Turnovers: %.1f\n", records[index].turnovers);
  printf("Personal Fouls: %.1f\n", records[index].personalFouls);
  printf("Points: %.1f\n", records[index].points);
  printf("Awards: %s\n", records[index].awards);
  printf("\n");
}
// deals with invalid input
void handleInvalidInput(void) {
  char buffer[100];
  fgets(buffer, sizeof(buffer),
         stdin); // Read and discard characters from the input stream
  printf("Invalid input, please try again.\n");
}
// add record with input protection through out
void addRecord(int *recordCount) {
  if (*recordCount >= MAX_RECORDS) {
    printf("Cannot add more records. Maximum limit reached.\n");
    return;
  }

  printf("Enter record details:\n");

  // Input protection for each field
  printf("Season (YYYY-YY): ");
  while (scanf("%7s", records[*recordCount].season) != 1) {
    handleInvalidInput();
    printf("Season (YYYY-YY): ");
  }

  printf("Age: ");
  while (scanf("%d", &records[*recordCount].age) != 1) {
    handleInvalidInput();
    printf("Age: ");
  }

  printf("Team (Abbreviation, 3 chars): ");
  while (scanf("%3s", records[*recordCount].team) != 1) {
    handleInvalidInput();
    printf("Team (Abbreviation, 3 chars): ");
  }

  printf("League (Abbreviation, 3 chars): ");
  while (scanf("%3s", records[*recordCount].league) != 1) {
    handleInvalidInput();
    printf("League (Abbreviation, 3 chars): ");
  }

  printf("Position (Abbreviation, 2 chars): ");
  while (scanf("%2s", records[*recordCount].position) != 1) {
    handleInvalidInput();
    printf("Position (Abbreviation, 2 chars): ");
  }

  printf("Games Played: ");
  while (scanf("%d", &records[*recordCount].games) != 1) {
    handleInvalidInput();
    printf("Games Played: ");
  }

  printf("Games Started: ");
  while (scanf("%d", &records[*recordCount].gamesStarted) != 1) {
    handleInvalidInput();
    printf("Games Started: ");
  }

  printf("Minutes Per Game: ");
  while (scanf("%f", &records[*recordCount].minutesPerGame) != 1) {
    handleInvalidInput();
    printf("Minutes Per Game: ");
  }

  printf("Field Goals Made Per Game: ");
  while (scanf("%f", &records[*recordCount].fieldGoals) != 1) {
    handleInvalidInput();
    printf("Field Goals Made Per Game: ");
  }

  printf("Field Goal Attempts Per Game: ");
  while (scanf("%f", &records[*recordCount].fieldGoalAttempts) != 1) {
    handleInvalidInput();
    printf("Field Goal Attempts Per Game: ");
  }

  printf("Field Goal Percentage: ");
  while (scanf("%f", &records[*recordCount].fieldGoalPercentage) != 1) {
    handleInvalidInput();
    printf("Field Goal Percentage: ");
  }

  printf("Three Point Made Per Game: ");
  while (scanf("%f", &records[*recordCount].threePoint) != 1) {
    handleInvalidInput();
    printf("Three Point Made Per Game: ");
  }

  printf("Three Point Attempts Per Game: ");
  while (scanf("%f", &records[*recordCount].threePointAttempts) != 1) {
    handleInvalidInput();
    printf("Three Point Attempts Per Game: ");
  }

  printf("Three Point Percentage: ");
  while (scanf("%f", &records[*recordCount].threePointPercentage) != 1) {
    handleInvalidInput();
    printf("Three Point Percentage: ");
  }

  printf("Two Point Made Per Game: ");
  while (scanf("%f", &records[*recordCount].twoPoint) != 1) {
    handleInvalidInput();
    printf("Two Point Made Per Game: ");
  }

  printf("Two Point Attempts Per Game: ");
  while (scanf("%f", &records[*recordCount].twoPointAttempts) != 1) {
    handleInvalidInput();
    printf("Two Point Attempts Per Game: ");
  }

  printf("Two Point Percentage: ");
  while (scanf("%f", &records[*recordCount].twoPointPercentage) != 1) {
    handleInvalidInput();
    printf("Two Point Percentage: ");
  }

  printf("Effective Field Goal Percentage: ");
  while (scanf("%f", &records[*recordCount].effectiveFieldGoalPercentage) !=
         1) {
    handleInvalidInput();
    printf("Effective Field Goal Percentage: ");
  }

  printf("Free Throws Made Per Game: ");
  while (scanf("%f", &records[*recordCount].freeThrows) != 1) {
    handleInvalidInput();
    printf("Free Throws Made Per Game: ");
  }

  printf("Free Throw Attempts Per Game: ");
  while (scanf("%f", &records[*recordCount].freeThrowAttempts) != 1) {
    handleInvalidInput();
    printf("Free Throw Attempts Per Game: ");
  }

  printf("Free Throw Percentage: ");
  while (scanf("%f", &records[*recordCount].freeThrowPercentage) != 1) {
    handleInvalidInput();
    printf("Free Throw Percentage: ");
  }

  printf("Offensive Rebounds Per Game: ");
  while (scanf("%f", &records[*recordCount].offensiveRebounds) != 1) {
    handleInvalidInput();
  }
  // Input protection for Offensive Rebounds
  printf("Offensive Rebounds: ");
  while (scanf("%f", &records[*recordCount].offensiveRebounds) != 1) {
    handleInvalidInput();
    printf("Offensive Rebounds: ");
  }

  // Input protection for Defensive Rebounds
  printf("Defensive Rebounds: ");
  while (scanf("%f", &records[*recordCount].defensiveRebounds) != 1) {
    handleInvalidInput();
    printf("Defensive Rebounds: ");
  }

  // Input protection for Total Rebounds
  printf("Total Rebounds: ");
  while (scanf("%f", &records[*recordCount].totalRebounds) != 1) {
    handleInvalidInput();
    printf("Total Rebounds: ");
  }

  // Input protection for Assists
  printf("Assists: ");
  while (scanf("%f", &records[*recordCount].assists) != 1) {
    handleInvalidInput();
    printf("Assists: ");
  }

  // Input protection for Steals
  printf("Steals: ");
  while (scanf("%f", &records[*recordCount].steals) != 1) {
    handleInvalidInput();
    printf("Steals: ");
  }

  // Input protection for Blocks
  printf("Blocks: ");
  while (scanf("%f", &records[*recordCount].blocks) != 1) {
    handleInvalidInput();
    printf("Blocks: ");
  }

  // Input protection for Turnovers
  printf("Turnovers: ");
  while (scanf("%f", &records[*recordCount].turnovers) != 1) {
    handleInvalidInput();
    printf("Turnovers: ");
  }

  // Input protection for Personal Fouls
  printf("Personal Fouls: ");
  while (scanf("%f", &records[*recordCount].personalFouls) != 1) {
    handleInvalidInput();
    printf("Personal Fouls: ");
  }

  // Input protection for Points
  printf("Points: ");
  while (scanf("%f", &records[*recordCount].points) != 1) {
    handleInvalidInput();
    printf("Points: ");
  }

  // Input protection for Awards
  printf("Awards (up to 100 characters, no commas): ");
  while (scanf(" %99[^\n]", records[*recordCount].awards) != 1) {
    handleInvalidInput();
    printf("Awards (up to 100 characters, no commas): ");
  }

  (*recordCount)++;
  printf("Record added successfully.\n");
}

// writes to file
void writeRecordsToFile(const char *filename, int *recordCount) {
  FILE *file;
  char response;

  // Check if the file exists by trying to open it for reading
  file = fopen(filename, "r");
  if (file != NULL) {
    fclose(file); // Close the file if it was opened
    printf("File %s already exists. Overwrite? (y/n): ", filename);
    scanf(" %c", &response);
    if (response != 'y' && response != 'Y') {
      printf("Operation cancelled by the user.\n");
      return;
    }
  }

  // Open the file in write mode to overwrite or create a new file
  file = fopen(filename, "w");
  if (!file) {
    perror("Failed to open file for writing");
    return;
  }

  // Write the header first
  fprintf(file,
          "Season,Age,Tm,Lg,Pos,G,GS,MP,FG,FGA,FG%%,3P,3PA,3P%%,2P,2PA,2P%%,"
          "eFG%%,FT,FTA,FT%%,ORB,DRB,TRB,AST,STL,BLK,TOV,PF,PTS,Awards\n");

  // Write records to the file
  for (int i = 0; i < *recordCount; i++) {
    fprintf(file,
            "%s,%d,%s,%s,%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"
            "%f,%f,%f,%f,%f,%f,%f,%f,%s\n",
            records[i].season, records[i].age, records[i].team,
            records[i].league, records[i].position, records[i].games,
            records[i].gamesStarted, records[i].minutesPerGame,
            records[i].fieldGoals, records[i].fieldGoalAttempts,
            records[i].fieldGoalPercentage, records[i].threePoint,
            records[i].threePointAttempts, records[i].threePointPercentage,
            records[i].twoPoint, records[i].twoPointAttempts,
            records[i].twoPointPercentage,
            records[i].effectiveFieldGoalPercentage, records[i].freeThrows,
            records[i].freeThrowAttempts, records[i].freeThrowPercentage,
            records[i].offensiveRebounds, records[i].defensiveRebounds,
            records[i].totalRebounds, records[i].assists, records[i].steals,
            records[i].blocks, records[i].turnovers, records[i].personalFouls,
            records[i].points, records[i].awards);
  }

  fclose(file);
  printf("Records saved successfully to %s.\n", filename);
}
// Function to delete records
void deleteRecord(int *recordCount) {
  if (*recordCount == 0) {
    printf("No records available to delete.\n");
    return;
  }

  int age;
  printf("Enter age to search for deletion or -1 to exit: ");
  scanf("%d", &age);

  // Check if user wants to exit
  if (age == -1) {
    printf("Deletion process cancelled.\n");
    return;
  }

  int foundIndexes[MAX_RECORDS];
  int foundCount = 0;

  // Search for records by age
  for (int i = 0; i < *recordCount; i++) {
    if (records[i].age == age) {
      foundIndexes[foundCount++] = i;
    }
  }

  if (foundCount == 0) {
    printf("No records found for age %d.\n", age);
    return;
  }
  // Confirm deletion
  char confirm;
  printf("Found %d records with age %d. Do you want to proceed with deletion? "
         "(Y/N): ",
         foundCount, age);
  scanf(" %c", &confirm); // Notice the space before %c to consume any leftover
                          // newline characters

  if (confirm == 'Y' || confirm == 'y') {
    // Assuming deletion logic is implemented here
    printf("Records deleted successfully.\n");
  } else {
    printf("Deletion cancelled.\n");
  }

  printf("Select a record to delete:\n");
  for (int i = 0; i < foundCount; i++) {
    printf("%d: ", i + 1);
    printRecordDetails(foundIndexes[i], recordCount);
  }

  int choice;
  printf("Enter the number of the record to delete (1-%d): ", foundCount);
  scanf("%d", &choice);

  // input protection
  if (choice < 1 || choice > foundCount) {
    printf("Invalid choice.\n");
    return;
  }

  // Delete the selected record
  int indexToDelete = foundIndexes[choice - 1];
  for (int i = indexToDelete; i < *recordCount - 1; i++) {
    records[i] = records[i + 1];
  }
  (*recordCount)--;

  printf("Record deleted successfully.\n");
}
