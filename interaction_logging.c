#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interaction_logging.h"
#include "file_operations.h"
#include "constants.h"

// Function to log quiz attempt
void logQuizAttempt() {
    Interaction interaction;
    int learnerId, contentId;
    float score;
    int attempts;
    char feedback[200];
    
    printf("\n--- Log Quiz Attempt ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get content ID
    printf("Enter content ID: ");
    scanf("%d", &contentId);
    
    if (!isValidContentId(contentId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get quiz score
    do {
        printf("Enter quiz score (0-100): ");
        scanf("%f", &score);
        
        if (score < 0 || score > 100) {
            printf("Score must be between 0 and 100. Please try again.\n");
        }
    } while (score < 0 || score > 100);
    
    // Get number of attempts
    do {
        printf("Enter number of attempts: ");
        scanf("%d", &attempts);
        
        if (attempts <= 0) {
            printf("Attempts must be positive. Please try again.\n");
        }
    } while (attempts <= 0);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get feedback
    printf("Enter feedback (optional): ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;
    
    // Fill interaction structure
    interaction.interactionId = getNextInteractionId();
    interaction.learnerId = learnerId;
    interaction.contentId = contentId;
    strcpy(interaction.type, INTERACTION_QUIZ);
    interaction.date = getCurrentDate();
    interaction.time = getCurrentTime();
    interaction.score = score;
    interaction.attempts = attempts;
    strcpy(interaction.feedback, feedback);
    interaction.duration = 0; // Quiz duration not tracked in this example
    
    // Save interaction
    if (saveInteractionToFile(&interaction)) {
        printf("\n%s\n", SUCCESS_INTERACTION_LOGGED);
        printf("Interaction ID: %d\n", interaction.interactionId);
        printf("Learner ID: %d\n", interaction.learnerId);
        printf("Content ID: %d\n", interaction.contentId);
        printf("Score: %.2f\n", interaction.score);
        printf("Attempts: %d\n", interaction.attempts);
    } else {
        printf("Failed to log interaction.\n");
    }
}

// Function to log code attempt
void logCodeAttempt() {
    Interaction interaction;
    int learnerId, contentId;
    float score;
    int attempts;
    int duration;
    char feedback[200];
    
    printf("\n--- Log Code Attempt ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get content ID
    printf("Enter content ID: ");
    scanf("%d", &contentId);
    
    if (!isValidContentId(contentId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get score (for code correctness)
    do {
        printf("Enter code correctness score (0-100): ");
        scanf("%f", &score);
        
        if (score < 0 || score > 100) {
            printf("Score must be between 0 and 100. Please try again.\n");
        }
    } while (score < 0 || score > 100);
    
    // Get number of attempts
    do {
        printf("Enter number of attempts: ");
        scanf("%d", &attempts);
        
        if (attempts <= 0) {
            printf("Attempts must be positive. Please try again.\n");
        }
    } while (attempts <= 0);
    
    // Get duration
    do {
        printf("Enter time spent in minutes: ");
        scanf("%d", &duration);
        
        if (duration <= 0) {
            printf("Duration must be positive. Please try again.\n");
        }
    } while (duration <= 0);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get feedback
    printf("Enter feedback (optional): ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;
    
    // Fill interaction structure
    interaction.interactionId = getNextInteractionId();
    interaction.learnerId = learnerId;
    interaction.contentId = contentId;
    strcpy(interaction.type, INTERACTION_CODE_ATTEMPT);
    interaction.date = getCurrentDate();
    interaction.time = getCurrentTime();
    interaction.score = score;
    interaction.attempts = attempts;
    strcpy(interaction.feedback, feedback);
    interaction.duration = duration;
    
    // Save interaction
    if (saveInteractionToFile(&interaction)) {
        printf("\n%s\n", SUCCESS_INTERACTION_LOGGED);
        printf("Interaction ID: %d\n", interaction.interactionId);
        printf("Learner ID: %d\n", interaction.learnerId);
        printf("Content ID: %d\n", interaction.contentId);
        printf("Score: %.2f\n", interaction.score);
        printf("Attempts: %d\n", interaction.attempts);
        printf("Duration: %d minutes\n", interaction.duration);
    } else {
        printf("Failed to log interaction.\n");
    }
}

// Function to log video view
void logVideoView() {
    Interaction interaction;
    int learnerId, contentId;
    int duration;
    char feedback[200];
    
    printf("\n--- Log Video View ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get content ID
    printf("Enter content ID: ");
    scanf("%d", &contentId);
    
    if (!isValidContentId(contentId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get viewing duration
    do {
        printf("Enter viewing duration in minutes: ");
        scanf("%d", &duration);
        
        if (duration <= 0) {
            printf("Duration must be positive. Please try again.\n");
        }
    } while (duration <= 0);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get feedback
    printf("Enter feedback (optional): ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;
    
    // Fill interaction structure
    interaction.interactionId = getNextInteractionId();
    interaction.learnerId = learnerId;
    interaction.contentId = contentId;
    strcpy(interaction.type, INTERACTION_VIDEO_VIEW);
    interaction.date = getCurrentDate();
    interaction.time = getCurrentTime();
    interaction.score = 0; // No score for video views
    interaction.attempts = 1; // Single view
    strcpy(interaction.feedback, feedback);
    interaction.duration = duration;
    
    // Save interaction
    if (saveInteractionToFile(&interaction)) {
        printf("\n%s\n", SUCCESS_INTERACTION_LOGGED);
        printf("Interaction ID: %d\n", interaction.interactionId);
        printf("Learner ID: %d\n", interaction.learnerId);
        printf("Content ID: %d\n", interaction.contentId);
        printf("Duration: %d minutes\n", interaction.duration);
    } else {
        printf("Failed to log interaction.\n");
    }
}

// Function to log reading activity
void logReadingActivity() {
    Interaction interaction;
    int learnerId, contentId;
    int duration;
    char feedback[200];
    
    printf("\n--- Log Reading Activity ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get content ID
    printf("Enter content ID: ");
    scanf("%d", &contentId);
    
    if (!isValidContentId(contentId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get reading duration
    do {
        printf("Enter reading duration in minutes: ");
        scanf("%d", &duration);
        
        if (duration <= 0) {
            printf("Duration must be positive. Please try again.\n");
        }
    } while (duration <= 0);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get feedback
    printf("Enter feedback (optional): ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;
    
    // Fill interaction structure
    interaction.interactionId = getNextInteractionId();
    interaction.learnerId = learnerId;
    interaction.contentId = contentId;
    strcpy(interaction.type, INTERACTION_READING);
    interaction.date = getCurrentDate();
    interaction.time = getCurrentTime();
    interaction.score = 0; // No score for reading
    interaction.attempts = 1; // Single reading
    strcpy(interaction.feedback, feedback);
    interaction.duration = duration;
    
    // Save interaction
    if (saveInteractionToFile(&interaction)) {
        printf("\n%s\n", SUCCESS_INTERACTION_LOGGED);
        printf("Interaction ID: %d\n", interaction.interactionId);
        printf("Learner ID: %d\n", interaction.learnerId);
        printf("Content ID: %d\n", interaction.contentId);
        printf("Duration: %d minutes\n", interaction.duration);
    } else {
        printf("Failed to log interaction.\n");
    }
}

// Function to log exercise attempt
void logExerciseAttempt() {
    Interaction interaction;
    int learnerId, contentId;
    float score;
    int attempts;
    int duration;
    char feedback[200];
    
    printf("\n--- Log Exercise Attempt ---\n");
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get content ID
    printf("Enter content ID: ");
    scanf("%d", &contentId);
    
    if (!isValidContentId(contentId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    // Get exercise score
    do {
        printf("Enter exercise score (0-100): ");
        scanf("%f", &score);
        
        if (score < 0 || score > 100) {
            printf("Score must be between 0 and 100. Please try again.\n");
        }
    } while (score < 0 || score > 100);
    
    // Get number of attempts
    do {
        printf("Enter number of attempts: ");
        scanf("%d", &attempts);
        
        if (attempts <= 0) {
            printf("Attempts must be positive. Please try again.\n");
        }
    } while (attempts <= 0);
    
    // Get duration
    do {
        printf("Enter time spent in minutes: ");
        scanf("%d", &duration);
        
        if (duration <= 0) {
            printf("Duration must be positive. Please try again.\n");
        }
    } while (duration <= 0);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get feedback
    printf("Enter feedback (optional): ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;
    
    // Fill interaction structure
    interaction.interactionId = getNextInteractionId();
    interaction.learnerId = learnerId;
    interaction.contentId = contentId;
    strcpy(interaction.type, INTERACTION_EXERCISE);
    interaction.date = getCurrentDate();
    interaction.time = getCurrentTime();
    interaction.score = score;
    interaction.attempts = attempts;
    strcpy(interaction.feedback, feedback);
    interaction.duration = duration;
    
    // Save interaction
    if (saveInteractionToFile(&interaction)) {
        printf("\n%s\n", SUCCESS_INTERACTION_LOGGED);
        printf("Interaction ID: %d\n", interaction.interactionId);
        printf("Learner ID: %d\n", interaction.learnerId);
        printf("Content ID: %d\n", interaction.contentId);
        printf("Score: %.2f\n", interaction.score);
        printf("Attempts: %d\n", interaction.attempts);
        printf("Duration: %d minutes\n", interaction.duration);
    } else {
        printf("Failed to log interaction.\n");
    }
}

// Function to view interaction history
void viewInteractionHistory() {
    Interaction interactions[MAX_INTERACTIONS];
    int count;
    
    printf("\n--- All Interactions ---\n");
    
    if (!loadInteractionsFromFile(interactions, &count)) {
        printf("No interactions found or error loading data.\n");
        return;
    }
    
    if (count == 0) {
        printf("No interactions found.\n");
        return;
    }
    
    printf("%-5s %-8s %-8s %-15s %-12s %-8s %-8s %-8s %-8s\n",
           "ID", "Learner", "Content", "Type", "Date", "Time", "Score", "Attempts", "Duration");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-8d %-8d %-15s %02d-%02d-%04d %02d:%02d:%02d %-8.2f %-8d %-8d\n",
               interactions[i].interactionId, interactions[i].learnerId, interactions[i].contentId,
               interactions[i].type, interactions[i].date.day, interactions[i].date.month,
               interactions[i].date.year, interactions[i].time.hour, interactions[i].time.minute,
               interactions[i].time.second, interactions[i].score, interactions[i].attempts,
               interactions[i].duration);
    }
}

// Function to view interactions for a specific learner
void viewLearnerInteractions() {
    Interaction interactions[MAX_INTERACTIONS];
    int count;
    int learnerId;
    
    printf("\n--- View Learner Interactions ---\n");
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    if (!isValidLearnerId(learnerId)) {
        printf(ERROR_INVALID_INPUT "\n");
        return;
    }
    
    if (!getLearnerInteractions(learnerId, interactions, &count)) {
        printf("Error loading interactions for learner %d.\n", learnerId);
        return;
    }
    
    if (count == 0) {
        printf("No interactions found for learner %d.\n", learnerId);
        return;
    }
    
    printf("\n--- Interactions for Learner %d ---\n", learnerId);
    printf("%-5s %-8s %-15s %-12s %-8s %-8s %-8s %-8s\n",
           "ID", "Content", "Type", "Date", "Time", "Score", "Attempts", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-8d %-15s %02d-%02d-%04d %02d:%02d:%02d %-8.2f %-8d %-8d\n",
               interactions[i].interactionId, interactions[i].contentId,
               interactions[i].type, interactions[i].date.day, interactions[i].date.month,
               interactions[i].date.year, interactions[i].time.hour, interactions[i].time.minute,
               interactions[i].time.second, interactions[i].score, interactions[i].attempts,
               interactions[i].duration);
    }
}

// Function to view interaction statistics
void viewInteractionStatistics() {
    Interaction interactions[MAX_INTERACTIONS];
    int count;
    int typeCount[5] = {0}; // quiz, code_attempt, video_view, reading, exercise
    float totalScore = 0.0;
    int scoredInteractions = 0;
    int totalDuration = 0;
    int totalAttempts = 0;
    
    printf("\n--- Interaction Statistics ---\n");
    
    if (!loadInteractionsFromFile(interactions, &count)) {
        printf("Error loading interaction data.\n");
        return;
    }
    
    if (count == 0) {
        printf("No interactions available for statistics.\n");
        return;
    }
    
    // Calculate statistics
    for (int i = 0; i < count; i++) {
        // Count by type
        if (strcmp(interactions[i].type, INTERACTION_QUIZ) == 0) typeCount[0]++;
        else if (strcmp(interactions[i].type, INTERACTION_CODE_ATTEMPT) == 0) typeCount[1]++;
        else if (strcmp(interactions[i].type, INTERACTION_VIDEO_VIEW) == 0) typeCount[2]++;
        else if (strcmp(interactions[i].type, INTERACTION_READING) == 0) typeCount[3]++;
        else if (strcmp(interactions[i].type, INTERACTION_EXERCISE) == 0) typeCount[4]++;
        
        // Calculate totals
        if (interactions[i].score > 0) {
            totalScore += interactions[i].score;
            scoredInteractions++;
        }
        totalDuration += interactions[i].duration;
        totalAttempts += interactions[i].attempts;
    }
    
    // Display statistics
    printf("Total Interactions: %d\n", count);
    printf("\nInteractions by Type:\n");
    printf("  Quizzes: %d\n", typeCount[0]);
    printf("  Code Attempts: %d\n", typeCount[1]);
    printf("  Video Views: %d\n", typeCount[2]);
    printf("  Reading Activities: %d\n", typeCount[3]);
    printf("  Exercise Attempts: %d\n", typeCount[4]);
    
    printf("\nOverall Statistics:\n");
    if (scoredInteractions > 0) {
        printf("  Average Score: %.2f\n", totalScore / scoredInteractions);
    } else {
        printf("  Average Score: No scored interactions\n");
    }
    printf("  Total Duration: %d minutes\n", totalDuration);
    printf("  Total Attempts: %d\n", totalAttempts);
    printf("  Average Duration per Interaction: %.2f minutes\n", 
           count > 0 ? (float)totalDuration / count : 0);
}

// Function to log learning interaction (main menu for this module)
void logLearningInteraction() {
    int choice;
    
    while (1) {
        printf("\n--- Log Learning Interaction ---\n");
        printf("1. Log Quiz Attempt\n");
        printf("2. Log Code Attempt\n");
        printf("3. Log Video View\n");
        printf("4. Log Reading Activity\n");
        printf("5. Log Exercise Attempt\n");
        printf("6. View All Interactions\n");
        printf("7. View Learner Interactions\n");
        printf("8. View Interaction Statistics\n");
        printf("9. Back to Main Menu\n");
        printf("\nEnter your choice (1-9): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                logQuizAttempt();
                break;
            case 2:
                logCodeAttempt();
                break;
            case 3:
                logVideoView();
                break;
            case 4:
                logReadingActivity();
                break;
            case 5:
                logExerciseAttempt();
                break;
            case 6:
                viewInteractionHistory();
                break;
            case 7:
                viewLearnerInteractions();
                break;
            case 8:
                viewInteractionStatistics();
                break;
            case 9:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-9.\n");
                break;
        }
    }
}
