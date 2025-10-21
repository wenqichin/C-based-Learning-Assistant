#include <stdio.h>
#include <stdlib.h>
#include "learner_profile.h"
#include "interaction_logging.h"
#include "content_management.h"
#include "recommendation_engine.h"
#include "feedback_reports.h"

int main() {
    int choice;
    
    while (1) {
        // Display header
        printf("\n--- Learning Assistant for Programming Education ---\n\n");
        
        // Display menu options
        printf("1. Manage Learner Profiles\n");
        printf("2. Log Learning Interaction\n");
        printf("3. View Content Repository\n");
        printf("4. Get Resource Recommendations\n");
        printf("5. Generate Feedback & Reports\n");
        printf("6. Exit\n\n");
        
        // Get user choice
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        
        // Route to appropriate function based on choice
        switch (choice) {
            case 1:
                manageLearnerProfiles();
                break;
            case 2:
                logLearningInteraction();
                break;
            case 3:
                manageContentRepository();
                break;
            case 4:
                getResourceRecommendations();
                break;
            case 5:
                generateFeedbackReports();
                break;
            case 6:
                printf("\nThank you for using Learning Assistant for Programming Education!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please enter a number between 1-6.\n");
                break;
        }
    }
    
    return 0;
}

// Function implementations (these will call functions from other files)
// manageLearnerProfiles() is now implemented in learner_profile.c

// Function implementations are now in their respective .c files
// These functions are declared in the other source files