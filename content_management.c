#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "content_management.h"
#include "file_operations.h"
#include "constants.h"

// Function to add new content
void addContent() {
    Content content;
    
    printf("\n--- Add New Content ---\n");
    
    // Auto-generate content ID
    content.contentId = getNextContentId();
    printf("Auto-generated Content ID: %d\n", content.contentId);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    // Get content title with validation
    do {
        printf("Enter content title (max %d characters): ", MAX_NAME_LENGTH - 1);
        fgets(content.title, sizeof(content.title), stdin);
        content.title[strcspn(content.title, "\n")] = 0;
        
        if (strlen(content.title) == 0) {
            printf("Title cannot be empty. Please try again.\n");
        }
    } while (strlen(content.title) == 0);
    
    // Get content type with validation
    do {
        printf("Enter content type (%s/%s/%s/%s/%s): ", 
               CONTENT_TYPE_TUTORIAL, CONTENT_TYPE_VIDEO, CONTENT_TYPE_EXERCISE, 
               CONTENT_TYPE_QUIZ, CONTENT_TYPE_READING);
        fgets(content.type, sizeof(content.type), stdin);
        content.type[strcspn(content.type, "\n")] = 0;
        
        if (!isValidContentType(content.type)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidContentType(content.type));
    
    // Get topic
    do {
        printf("Enter topic (max %d characters): ", MAX_TOPIC_LENGTH - 1);
        fgets(content.topic, sizeof(content.topic), stdin);
        content.topic[strcspn(content.topic, "\n")] = 0;
        
        if (strlen(content.topic) == 0) {
            printf("Topic cannot be empty. Please try again.\n");
        }
    } while (strlen(content.topic) == 0);
    
    // Get difficulty with validation
    do {
        printf("Enter difficulty level (%s/%s/%s): ", 
               DIFFICULTY_EASY, DIFFICULTY_MEDIUM, DIFFICULTY_HARD);
        fgets(content.difficulty, sizeof(content.difficulty), stdin);
        content.difficulty[strcspn(content.difficulty, "\n")] = 0;
        
        if (!isValidDifficulty(content.difficulty)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidDifficulty(content.difficulty));
    
    // Get description
    do {
        printf("Enter description (max %d characters): ", MAX_DESCRIPTION_LENGTH - 1);
        fgets(content.description, sizeof(content.description), stdin);
        content.description[strcspn(content.description, "\n")] = 0;
        
        if (strlen(content.description) == 0) {
            printf("Description cannot be empty. Please try again.\n");
        }
    } while (strlen(content.description) == 0);
    
    // Get estimated duration
    do {
        printf("Enter estimated duration in minutes: ");
        scanf("%d", &content.estimatedDuration);
        
        if (content.estimatedDuration <= 0) {
            printf("Duration must be positive. Please try again.\n");
        }
    } while (content.estimatedDuration <= 0);
    
    // Initialize other fields
    content.viewCount = 0;
    content.averageRating = 0.0;
    
    // Save to file
    if (saveContentToFile(&content)) {
        printf("\n%s\n", SUCCESS_CONTENT_ADDED);
        printf("Content ID: %d\n", content.contentId);
        printf("Title: %s\n", content.title);
        printf("Type: %s\n", content.type);
        printf("Topic: %s\n", content.topic);
        printf("Difficulty: %s\n", content.difficulty);
        printf("Duration: %d minutes\n", content.estimatedDuration);
    } else {
        printf("Failed to save content.\n");
    }
}

// Function to view all content
void viewAllContent() {
    Content content[MAX_CONTENT];
    int count;
    
    printf("\n--- All Content ---\n");
    
    if (!loadContentFromFile(content, &count)) {
        printf("No content found or error loading data.\n");
        return;
    }
    
    if (count == 0) {
        printf("No content found.\n");
        return;
    }
    
    printf("%-5s %-25s %-12s %-15s %-8s %-8s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration", "Views", "Rating");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-12s %-15s %-8s %-8d %-8d %-8.2f\n",
               content[i].contentId, content[i].title, content[i].type,
               content[i].topic, content[i].difficulty, content[i].estimatedDuration,
               content[i].viewCount, content[i].averageRating);
    }
}

// Function to search content by topic
void searchContentByTopic() {
    Content content[MAX_CONTENT];
    int count;
    char searchTopic[MAX_TOPIC_LENGTH];
    int found = 0;
    
    printf("\n--- Search Content by Topic ---\n");
    
    if (!loadContentFromFile(content, &count)) {
        printf("Error loading content data.\n");
        return;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    printf("Enter topic to search: ");
    fgets(searchTopic, sizeof(searchTopic), stdin);
    searchTopic[strcspn(searchTopic, "\n")] = 0;
    
    printf("\n--- Search Results ---\n");
    printf("%-5s %-25s %-12s %-15s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (strstr(content[i].topic, searchTopic) != NULL) {
            found = 1;
            printf("%-5d %-25s %-12s %-15s %-8s %-8d\n",
                   content[i].contentId, content[i].title, content[i].type,
                   content[i].topic, content[i].difficulty, content[i].estimatedDuration);
        }
    }
    
    if (!found) {
        printf("No content found for topic: %s\n", searchTopic);
    }
}

// Function to search content by type
void searchContentByType() {
    Content content[MAX_CONTENT];
    int count;
    char searchType[20];
    int found = 0;
    
    printf("\n--- Search Content by Type ---\n");
    
    if (!loadContentFromFile(content, &count)) {
        printf("Error loading content data.\n");
        return;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    do {
        printf("Enter content type (%s/%s/%s/%s/%s): ", 
               CONTENT_TYPE_TUTORIAL, CONTENT_TYPE_VIDEO, CONTENT_TYPE_EXERCISE, 
               CONTENT_TYPE_QUIZ, CONTENT_TYPE_READING);
        fgets(searchType, sizeof(searchType), stdin);
        searchType[strcspn(searchType, "\n")] = 0;
        
        if (!isValidContentType(searchType)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidContentType(searchType));
    
    printf("\n--- Search Results ---\n");
    printf("%-5s %-25s %-12s %-15s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (strcmp(content[i].type, searchType) == 0) {
            found = 1;
            printf("%-5d %-25s %-12s %-15s %-8s %-8d\n",
                   content[i].contentId, content[i].title, content[i].type,
                   content[i].topic, content[i].difficulty, content[i].estimatedDuration);
        }
    }
    
    if (!found) {
        printf("No content found for type: %s\n", searchType);
    }
}

// Function to search content by difficulty
void searchContentByDifficulty() {
    Content content[MAX_CONTENT];
    int count;
    char searchDifficulty[20];
    int found = 0;
    
    printf("\n--- Search Content by Difficulty ---\n");
    
    if (!loadContentFromFile(content, &count)) {
        printf("Error loading content data.\n");
        return;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    do {
        printf("Enter difficulty level (%s/%s/%s): ", 
               DIFFICULTY_EASY, DIFFICULTY_MEDIUM, DIFFICULTY_HARD);
        fgets(searchDifficulty, sizeof(searchDifficulty), stdin);
        searchDifficulty[strcspn(searchDifficulty, "\n")] = 0;
        
        if (!isValidDifficulty(searchDifficulty)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidDifficulty(searchDifficulty));
    
    printf("\n--- Search Results ---\n");
    printf("%-5s %-25s %-12s %-15s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (strcmp(content[i].difficulty, searchDifficulty) == 0) {
            found = 1;
            printf("%-5d %-25s %-12s %-15s %-8s %-8d\n",
                   content[i].contentId, content[i].title, content[i].type,
                   content[i].topic, content[i].difficulty, content[i].estimatedDuration);
        }
    }
    
    if (!found) {
        printf("No content found for difficulty: %s\n", searchDifficulty);
    }
}

// Function to view content statistics
void viewContentStatistics() {
    Content content[MAX_CONTENT];
    int count;
    int typeCount[5] = {0}; // tutorial, video, exercise, quiz, reading
    int difficultyCount[3] = {0}; // easy, medium, hard
    int totalViews = 0;
    float totalRating = 0.0;
    int ratedContent = 0;
    
    printf("\n--- Content Statistics ---\n");
    
    if (!loadContentFromFile(content, &count)) {
        printf("Error loading content data.\n");
        return;
    }
    
    if (count == 0) {
        printf("No content available for statistics.\n");
        return;
    }
    
    // Calculate statistics
    for (int i = 0; i < count; i++) {
        // Count by type
        if (strcmp(content[i].type, CONTENT_TYPE_TUTORIAL) == 0) typeCount[0]++;
        else if (strcmp(content[i].type, CONTENT_TYPE_VIDEO) == 0) typeCount[1]++;
        else if (strcmp(content[i].type, CONTENT_TYPE_EXERCISE) == 0) typeCount[2]++;
        else if (strcmp(content[i].type, CONTENT_TYPE_QUIZ) == 0) typeCount[3]++;
        else if (strcmp(content[i].type, CONTENT_TYPE_READING) == 0) typeCount[4]++;
        
        // Count by difficulty
        if (strcmp(content[i].difficulty, DIFFICULTY_EASY) == 0) difficultyCount[0]++;
        else if (strcmp(content[i].difficulty, DIFFICULTY_MEDIUM) == 0) difficultyCount[1]++;
        else if (strcmp(content[i].difficulty, DIFFICULTY_HARD) == 0) difficultyCount[2]++;
        
        // Calculate totals
        totalViews += content[i].viewCount;
        if (content[i].averageRating > 0) {
            totalRating += content[i].averageRating;
            ratedContent++;
        }
    }
    
    // Display statistics
    printf("Total Content Items: %d\n", count);
    printf("\nContent by Type:\n");
    printf("  Tutorials: %d\n", typeCount[0]);
    printf("  Videos: %d\n", typeCount[1]);
    printf("  Exercises: %d\n", typeCount[2]);
    printf("  Quizzes: %d\n", typeCount[3]);
    printf("  Reading Materials: %d\n", typeCount[4]);
    
    printf("\nContent by Difficulty:\n");
    printf("  Easy: %d\n", difficultyCount[0]);
    printf("  Medium: %d\n", difficultyCount[1]);
    printf("  Hard: %d\n", difficultyCount[2]);
    
    printf("\nOverall Statistics:\n");
    printf("  Total Views: %d\n", totalViews);
    if (ratedContent > 0) {
        printf("  Average Rating: %.2f\n", totalRating / ratedContent);
    } else {
        printf("  Average Rating: No ratings available\n");
    }
}

// Function to manage content repository (main menu for this module)
void manageContentRepository() {
    int choice;
    
    while (1) {
        printf("\n--- Manage Content Repository ---\n");
        printf("1. Add New Content\n");
        printf("2. View All Content\n");
        printf("3. Search by Topic\n");
        printf("4. Search by Type\n");
        printf("5. Search by Difficulty\n");
        printf("6. View Content Statistics\n");
        printf("7. Back to Main Menu\n");
        printf("\nEnter your choice (1-7): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addContent();
                break;
            case 2:
                viewAllContent();
                break;
            case 3:
                searchContentByTopic();
                break;
            case 4:
                searchContentByType();
                break;
            case 5:
                searchContentByDifficulty();
                break;
            case 6:
                viewContentStatistics();
                break;
            case 7:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-7.\n");
                break;
        }
    }
}
