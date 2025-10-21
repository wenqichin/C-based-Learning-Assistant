#include <stdio.h>
#include <string.h>
#include "learner_profile.h"

// Structure to store learner profile information
struct LearnerProfile {
    int id;
    char name[100];
    char learningStyle[20];
    char skillLevel[20];
};

// Function to add a new learner profile
void addLearnerProfile() {
    struct LearnerProfile learner;
    
    printf("\n--- Add New Learner Profile ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learner.id);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get learner name
    printf("Enter learner name: ");
    fgets(learner.name, sizeof(learner.name), stdin);
    // Remove newline character
    learner.name[strcspn(learner.name, "\n")] = 0;
    
    // Get preferred learning style
    printf("Enter preferred learning style (text/video/code): ");
    fgets(learner.learningStyle, sizeof(learner.learningStyle), stdin);
    learner.learningStyle[strcspn(learner.learningStyle, "\n")] = 0;
    
    // Get current skill level
    printf("Enter current skill level (beginner/intermediate/advanced): ");
    fgets(learner.skillLevel, sizeof(learner.skillLevel), stdin);
    learner.skillLevel[strcspn(learner.skillLevel, "\n")] = 0;
    
    // Display confirmation
    printf("\nLearner profile added successfully.\n");
    printf("ID: %d\n", learner.id);
    printf("Name: %s\n", learner.name);
    printf("Learning Style: %s\n", learner.learningStyle);
    printf("Skill Level: %s\n", learner.skillLevel);
}

// Function to manage learner profiles (main menu for this module)
void manageLearnerProfiles() {
    int choice;
    
    while (1) {
        printf("\n--- Manage Learner Profiles ---\n");
        printf("1. Add New Learner Profile\n");
        printf("2. View All Learner Profiles\n");
        printf("3. Update Learner Profile\n");
        printf("4. Delete Learner Profile\n");
        printf("5. Back to Main Menu\n");
        printf("\nEnter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addLearnerProfile();
                break;
            case 2:
                printf("\nViewing all learner profiles...\n");
                // TODO: Implement view all profiles
                break;
            case 3:
                printf("\nUpdating learner profile...\n");
                // TODO: Implement update profile
                break;
            case 4:
                printf("\nDeleting learner profile...\n");
                // TODO: Implement delete profile
                break;
            case 5:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-5.\n");
                break;
        }
    }
}
