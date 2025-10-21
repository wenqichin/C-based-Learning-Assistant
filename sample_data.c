#include <stdio.h>
#include <string.h>
#include "file_operations.h"
#include "constants.h"

// Function to create sample data for testing
void createSampleData() {
    printf("Creating sample data for testing...\n");
    
    // Create sample learners
    LearnerProfile learners[] = {
        {1, "Alice Johnson", LEARNING_STYLE_VIDEO, SKILL_BEGINNER, CONTENT_TYPE_VIDEO, 0, 0.0, {15, 12, 2024}},
        {2, "Bob Smith", LEARNING_STYLE_CODE, SKILL_INTERMEDIATE, CONTENT_TYPE_EXERCISE, 0, 0.0, {15, 12, 2024}},
        {3, "Carol Davis", LEARNING_STYLE_TEXT, SKILL_ADVANCED, CONTENT_TYPE_READING, 0, 0.0, {15, 12, 2024}},
        {4, "David Wilson", LEARNING_STYLE_MIXED, SKILL_BEGINNER, CONTENT_TYPE_TUTORIAL, 0, 0.0, {15, 12, 2024}}
    };
    
    // Create sample content
    Content content[] = {
        {1, "Introduction to C Programming", CONTENT_TYPE_VIDEO, "C Basics", DIFFICULTY_EASY, "Learn the fundamentals of C programming", 30, 0, 0.0},
        {2, "Variables and Data Types", CONTENT_TYPE_TUTORIAL, "C Basics", DIFFICULTY_EASY, "Understanding variables and data types in C", 25, 0, 0.0},
        {3, "Control Structures", CONTENT_TYPE_EXERCISE, "C Control Flow", DIFFICULTY_MEDIUM, "Practice with if-else and loops", 45, 0, 0.0},
        {4, "Functions in C", CONTENT_TYPE_READING, "C Functions", DIFFICULTY_MEDIUM, "Comprehensive guide to functions", 35, 0, 0.0},
        {5, "Pointers and Memory", CONTENT_TYPE_VIDEO, "C Advanced", DIFFICULTY_HARD, "Advanced concepts of pointers", 50, 0, 0.0},
        {6, "C Programming Quiz", CONTENT_TYPE_QUIZ, "C Basics", DIFFICULTY_EASY, "Test your knowledge of C basics", 15, 0, 0.0}
    };
    
    // Create sample interactions
    Interaction interactions[] = {
        {1, 1, 1, INTERACTION_VIDEO_VIEW, {10, 12, 2024}, {14, 30, 0}, 0.0, 1, "Great video!", 30},
        {2, 1, 6, INTERACTION_QUIZ, {10, 12, 2024}, {15, 0, 0}, 85.0, 1, "Good understanding", 15},
        {3, 2, 3, INTERACTION_CODE_ATTEMPT, {11, 12, 2024}, {10, 15, 0}, 92.0, 2, "Excellent work", 45},
        {4, 2, 4, INTERACTION_READING, {11, 12, 2024}, {16, 0, 0}, 0.0, 1, "Very helpful", 35},
        {5, 3, 5, INTERACTION_VIDEO_VIEW, {12, 12, 2024}, {9, 0, 0}, 0.0, 1, "Challenging but good", 50},
        {6, 4, 2, INTERACTION_READING, {12, 12, 2024}, {11, 30, 0}, 0.0, 1, "Clear explanation", 25},
        {7, 4, 6, INTERACTION_QUIZ, {12, 12, 2024}, {12, 0, 0}, 78.0, 1, "Needs more practice", 15}
    };
    
    // Save sample data
    for (int i = 0; i < 4; i++) {
        saveLearnerToFile(&learners[i]);
    }
    
    for (int i = 0; i < 6; i++) {
        saveContentToFile(&content[i]);
    }
    
    for (int i = 0; i < 7; i++) {
        saveInteractionToFile(&interactions[i]);
    }
    
    printf("Sample data created successfully!\n");
    printf("- 4 learner profiles\n");
    printf("- 6 content items\n");
    printf("- 7 learning interactions\n");
}

// Function to run sample data creation
int main() {
    createSampleData();
    return 0;
}
