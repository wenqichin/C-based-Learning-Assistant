#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "learner_profile.h"
#include "file_operations.h"
#include "constants.h"

// Function to add a new learner profile
void addLearnerProfile() {
    LearnerProfile learner;
    
    printf("\n--- Add New Learner Profile ---\n");
    
    // Get learner ID (auto-generated)
    learner.id = getNextLearnerId();
    printf("Auto-generated Learner ID: %d\n", learner.id);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get learner name with validation
    do {
        printf("Enter learner name (max %d characters): ", MAX_NAME_LENGTH - 1);
        fgets(learner.name, sizeof(learner.name), stdin);
        learner.name[strcspn(learner.name, "\n")] = 0;
        
        if (strlen(learner.name) == 0) {
            printf("Name cannot be empty. Please try again.\n");
        }
    } while (strlen(learner.name) == 0);
    
    // Get preferred learning style with validation
    do {
        printf("Enter preferred learning style (%s/%s/%s/%s): ", 
               LEARNING_STYLE_TEXT, LEARNING_STYLE_VIDEO, LEARNING_STYLE_CODE, LEARNING_STYLE_MIXED);
        fgets(learner.learningStyle, sizeof(learner.learningStyle), stdin);
        learner.learningStyle[strcspn(learner.learningStyle, "\n")] = 0;
        
        if (!isValidLearningStyle(learner.learningStyle)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidLearningStyle(learner.learningStyle));
    
    // Get current skill level with validation
    do {
        printf("Enter current skill level (%s/%s/%s): ", 
               SKILL_BEGINNER, SKILL_INTERMEDIATE, SKILL_ADVANCED);
        fgets(learner.skillLevel, sizeof(learner.skillLevel), stdin);
        learner.skillLevel[strcspn(learner.skillLevel, "\n")] = 0;
        
        if (!isValidSkillLevel(learner.skillLevel)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidSkillLevel(learner.skillLevel));
    
    // Get preferred content type
    do {
        printf("Enter preferred content type (%s/%s/%s/%s/%s): ", 
               CONTENT_TYPE_TUTORIAL, CONTENT_TYPE_VIDEO, CONTENT_TYPE_EXERCISE, 
               CONTENT_TYPE_QUIZ, CONTENT_TYPE_READING);
        fgets(learner.preferredContentType, sizeof(learner.preferredContentType), stdin);
        learner.preferredContentType[strcspn(learner.preferredContentType, "\n")] = 0;
        
        if (!isValidContentType(learner.preferredContentType)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidContentType(learner.preferredContentType));
    
    // Initialize other fields
    learner.totalInteractions = 0;
    learner.averageScore = 0.0;
    learner.lastActivity = getCurrentDate();
    
    // Save to file
    if (saveLearnerToFile(&learner)) {
        printf("\n%s\n", SUCCESS_LEARNER_ADDED);
        printf("ID: %d\n", learner.id);
        printf("Name: %s\n", learner.name);
        printf("Learning Style: %s\n", learner.learningStyle);
        printf("Skill Level: %s\n", learner.skillLevel);
        printf("Preferred Content: %s\n", learner.preferredContentType);
    } else {
        printf("Failed to save learner profile.\n");
    }
}

// Function to view all learner profiles
void viewAllLearnerProfiles() {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    
    printf("\n--- All Learner Profiles ---\n");
    
    if (!loadLearnersFromFile(learners, &count)) {
        printf("No learners found or error loading data.\n");
        return;
    }
    
    if (count == 0) {
        printf("No learner profiles found.\n");
        return;
    }
    
    printf("%-5s %-20s %-15s %-12s %-15s %-8s %-8s %-12s\n",
           "ID", "Name", "Learning Style", "Skill Level", "Content Type", 
           "Interactions", "Avg Score", "Last Activity");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-15s %-12s %-15s %-8d %-8.2f %02d-%02d-%04d\n",
               learners[i].id, learners[i].name, learners[i].learningStyle,
               learners[i].skillLevel, learners[i].preferredContentType,
               learners[i].totalInteractions, learners[i].averageScore,
               learners[i].lastActivity.day, learners[i].lastActivity.month,
               learners[i].lastActivity.year);
    }
}

// Function to update learner profile
void updateLearnerProfile() {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    int learnerId;
    int found = 0;
    
    printf("\n--- Update Learner Profile ---\n");
    
    if (!loadLearnersFromFile(learners, &count)) {
        printf("Error loading learner data.\n");
        return;
    }
    
    printf("Enter learner ID to update: ");
    scanf("%d", &learnerId);
    
    // Find the learner
    for (int i = 0; i < count; i++) {
        if (learners[i].id == learnerId) {
            found = 1;
            
            printf("\nCurrent Profile:\n");
            printf("Name: %s\n", learners[i].name);
            printf("Learning Style: %s\n", learners[i].learningStyle);
            printf("Skill Level: %s\n", learners[i].skillLevel);
            printf("Preferred Content: %s\n", learners[i].preferredContentType);
            
            // Clear input buffer
            while (getchar() != '\n');
            
            // Update name
            printf("\nEnter new name (or press Enter to keep current): ");
            char newName[MAX_NAME_LENGTH];
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = 0;
            if (strlen(newName) > 0) {
                strcpy(learners[i].name, newName);
            }
            
            // Update learning style
            printf("Enter new learning style (or press Enter to keep current): ");
            char newStyle[20];
            fgets(newStyle, sizeof(newStyle), stdin);
            newStyle[strcspn(newStyle, "\n")] = 0;
            if (strlen(newStyle) > 0 && isValidLearningStyle(newStyle)) {
                strcpy(learners[i].learningStyle, newStyle);
            }
            
            // Update skill level
            printf("Enter new skill level (or press Enter to keep current): ");
            char newLevel[20];
            fgets(newLevel, sizeof(newLevel), stdin);
            newLevel[strcspn(newLevel, "\n")] = 0;
            if (strlen(newLevel) > 0 && isValidSkillLevel(newLevel)) {
                strcpy(learners[i].skillLevel, newLevel);
            }
            
            // Update preferred content type
            printf("Enter new preferred content type (or press Enter to keep current): ");
            char newContent[20];
            fgets(newContent, sizeof(newContent), stdin);
            newContent[strcspn(newContent, "\n")] = 0;
            if (strlen(newContent) > 0 && isValidContentType(newContent)) {
                strcpy(learners[i].preferredContentType, newContent);
            }
            
            // Save updated profile
            if (updateLearnerInFile(&learners[i])) {
                printf("\n%s\n", SUCCESS_LEARNER_UPDATED);
            } else {
                printf("Failed to update learner profile.\n");
            }
            break;
        }
    }
    
    if (!found) {
        printf(ERROR_ID_NOT_FOUND "\n");
    }
}

// Function to delete learner profile
void deleteLearnerProfile() {
    int learnerId;
    char confirm;
    
    printf("\n--- Delete Learner Profile ---\n");
    printf("Enter learner ID to delete: ");
    scanf("%d", &learnerId);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    printf("Are you sure you want to delete learner ID %d? (y/n): ", learnerId);
    scanf("%c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        if (deleteLearnerFromFile(learnerId)) {
            printf("\n%s\n", SUCCESS_LEARNER_DELETED);
        } else {
            printf(ERROR_ID_NOT_FOUND "\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
}

// Function to search learner by ID
void searchLearnerById() {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    int learnerId;
    int found = 0;
    
    printf("\n--- Search Learner by ID ---\n");
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!loadLearnersFromFile(learners, &count)) {
        printf("Error loading learner data.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (learners[i].id == learnerId) {
            found = 1;
            printf("\n--- Learner Profile Found ---\n");
            printf("ID: %d\n", learners[i].id);
            printf("Name: %s\n", learners[i].name);
            printf("Learning Style: %s\n", learners[i].learningStyle);
            printf("Skill Level: %s\n", learners[i].skillLevel);
            printf("Preferred Content: %s\n", learners[i].preferredContentType);
            printf("Total Interactions: %d\n", learners[i].totalInteractions);
            printf("Average Score: %.2f\n", learners[i].averageScore);
            printf("Last Activity: %02d-%02d-%04d\n", 
                   learners[i].lastActivity.day, learners[i].lastActivity.month,
                   learners[i].lastActivity.year);
            break;
        }
    }
    
    if (!found) {
        printf(ERROR_ID_NOT_FOUND "\n");
    }
}

// Function to manage learner profiles (main menu for this module)
void manageLearnerProfiles() {
    int choice;
    
    while (1) {
        printf("\n--- Manage Learner Profiles ---\n");
        printf("1. Add New Learner Profile\n");
        printf("2. View All Learner Profiles\n");
        printf("3. Search Learner by ID\n");
        printf("4. Update Learner Profile\n");
        printf("5. Delete Learner Profile\n");
        printf("6. Back to Main Menu\n");
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addLearnerProfile();
                break;
            case 2:
                viewAllLearnerProfiles();
                break;
            case 3:
                searchLearnerById();
                break;
            case 4:
                updateLearnerProfile();
                break;
            case 5:
                deleteLearnerProfile();
                break;
            case 6:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-6.\n");
                break;
        }
    }
}
