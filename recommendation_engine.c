#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "recommendation_engine.h"
#include "file_operations.h"
#include "constants.h"

// Function to generate personalized recommendations
void generatePersonalizedRecommendations() {
    LearnerProfile learners[MAX_LEARNERS];
    Content content[MAX_CONTENT];
    Interaction interactions[MAX_INTERACTIONS];
    int learnerCount, contentCount, interactionCount;
    int learnerId;
    int found = 0;
    
    printf("\n--- Generate Personalized Recommendations ---\n");
    
    // Load data
    if (!loadLearnersFromFile(learners, &learnerCount) ||
        !loadContentFromFile(content, &contentCount) ||
        !loadInteractionsFromFile(interactions, &interactionCount)) {
        printf("Error loading data for recommendations.\n");
        return;
    }
    
    // Get learner ID
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    // Find the learner
    LearnerProfile* learner = NULL;
    for (int i = 0; i < learnerCount; i++) {
        if (learners[i].id == learnerId) {
            learner = &learners[i];
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf(ERROR_ID_NOT_FOUND "\n");
        return;
    }
    
    printf("\n--- Personalized Recommendations for %s ---\n", learner->name);
    printf("Learning Style: %s\n", learner->learningStyle);
    printf("Skill Level: %s\n", learner->skillLevel);
    printf("Preferred Content: %s\n", learner->preferredContentType);
    
    // Get learner's past interactions
    Interaction learnerInteractions[MAX_INTERACTIONS];
    int learnerInteractionCount;
    if (!getLearnerInteractions(learnerId, learnerInteractions, &learnerInteractionCount)) {
        learnerInteractionCount = 0;
    }
    
    // Calculate recommendation scores
    Recommendation recommendations[MAX_CONTENT];
    int recCount = 0;
    
    for (int i = 0; i < contentCount && recCount < MAX_CONTENT; i++) {
        float score = 0.0;
        char reason[200] = "";
        
        // Skill level matching (40% weight)
        if (strcmp(learner->skillLevel, SKILL_BEGINNER) == 0 && 
            strcmp(content[i].difficulty, DIFFICULTY_EASY) == 0) {
            score += WEIGHT_SKILL_LEVEL * 100;
            strcat(reason, "Matches beginner skill level. ");
        } else if (strcmp(learner->skillLevel, SKILL_INTERMEDIATE) == 0 && 
                   strcmp(content[i].difficulty, DIFFICULTY_MEDIUM) == 0) {
            score += WEIGHT_SKILL_LEVEL * 100;
            strcat(reason, "Matches intermediate skill level. ");
        } else if (strcmp(learner->skillLevel, SKILL_ADVANCED) == 0 && 
                   strcmp(content[i].difficulty, DIFFICULTY_HARD) == 0) {
            score += WEIGHT_SKILL_LEVEL * 100;
            strcat(reason, "Matches advanced skill level. ");
        }
        
        // Learning style matching (30% weight)
        if (strcmp(learner->learningStyle, LEARNING_STYLE_VIDEO) == 0 && 
            strcmp(content[i].type, CONTENT_TYPE_VIDEO) == 0) {
            score += WEIGHT_LEARNING_STYLE * 100;
            strcat(reason, "Matches video learning preference. ");
        } else if (strcmp(learner->learningStyle, LEARNING_STYLE_TEXT) == 0 && 
                   strcmp(content[i].type, CONTENT_TYPE_READING) == 0) {
            score += WEIGHT_LEARNING_STYLE * 100;
            strcat(reason, "Matches text learning preference. ");
        } else if (strcmp(learner->learningStyle, LEARNING_STYLE_CODE) == 0 && 
                   strcmp(content[i].type, CONTENT_TYPE_EXERCISE) == 0) {
            score += WEIGHT_LEARNING_STYLE * 100;
            strcat(reason, "Matches hands-on learning preference. ");
        }
        
        // Past performance analysis (30% weight)
        float avgScore = 0.0;
        int scoredInteractions = 0;
        for (int j = 0; j < learnerInteractionCount; j++) {
            if (learnerInteractions[j].score > 0) {
                avgScore += learnerInteractions[j].score;
                scoredInteractions++;
            }
        }
        
        if (scoredInteractions > 0) {
            avgScore /= scoredInteractions;
            if (avgScore >= QUIZ_EXCELLENT_THRESHOLD) {
                // High performer - recommend challenging content
                if (strcmp(content[i].difficulty, DIFFICULTY_HARD) == 0) {
                    score += WEIGHT_PAST_PERFORMANCE * 100;
                    strcat(reason, "Based on excellent past performance. ");
                }
            } else if (avgScore >= QUIZ_PASS_THRESHOLD) {
                // Good performer - recommend medium content
                if (strcmp(content[i].difficulty, DIFFICULTY_MEDIUM) == 0) {
                    score += WEIGHT_PAST_PERFORMANCE * 100;
                    strcat(reason, "Based on good past performance. ");
                }
            } else {
                // Struggling learner - recommend easy content
                if (strcmp(content[i].difficulty, DIFFICULTY_EASY) == 0) {
                    score += WEIGHT_PAST_PERFORMANCE * 100;
                    strcat(reason, "Based on learning needs. ");
                }
            }
        }
        
        // Only add recommendations with meaningful scores
        if (score > 20.0) {
            recommendations[recCount].learnerId = learnerId;
            recommendations[recCount].contentId = content[i].contentId;
            recommendations[recCount].relevanceScore = score;
            strcpy(recommendations[recCount].reason, reason);
            recCount++;
        }
    }
    
    // Sort recommendations by score (simple bubble sort)
    for (int i = 0; i < recCount - 1; i++) {
        for (int j = 0; j < recCount - i - 1; j++) {
            if (recommendations[j].relevanceScore < recommendations[j + 1].relevanceScore) {
                Recommendation temp = recommendations[j];
                recommendations[j] = recommendations[j + 1];
                recommendations[j + 1] = temp;
            }
        }
    }
    
    // Display top recommendations
    printf("\n--- Top Recommendations ---\n");
    int displayCount = (recCount > 5) ? 5 : recCount;
    
    if (displayCount == 0) {
        printf("No suitable recommendations found.\n");
        return;
    }
    
    printf("%-5s %-25s %-12s %-8s %-8s %-8s %s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Score", "Reason");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < displayCount; i++) {
        // Find content details
        Content* recommendedContent = NULL;
        for (int j = 0; j < contentCount; j++) {
            if (content[j].contentId == recommendations[i].contentId) {
                recommendedContent = &content[j];
                break;
            }
        }
        
        if (recommendedContent) {
            printf("%-5d %-25s %-12s %-8s %-8s %-8.1f %s\n",
                   recommendedContent->contentId, recommendedContent->title,
                   recommendedContent->type, recommendedContent->topic,
                   recommendedContent->difficulty, recommendations[i].relevanceScore,
                   recommendations[i].reason);
        }
    }
}

// Function to recommend by skill level
void recommendBySkillLevel() {
    Content content[MAX_CONTENT];
    int contentCount;
    char skillLevel[20];
    
    printf("\n--- Recommend by Skill Level ---\n");
    
    if (!loadContentFromFile(content, &contentCount)) {
        printf("Error loading content data.\n");
        return;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    do {
        printf("Enter skill level (%s/%s/%s): ", 
               SKILL_BEGINNER, SKILL_INTERMEDIATE, SKILL_ADVANCED);
        fgets(skillLevel, sizeof(skillLevel), stdin);
        skillLevel[strcspn(skillLevel, "\n")] = 0;
        
        if (!isValidSkillLevel(skillLevel)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidSkillLevel(skillLevel));
    
    // Determine appropriate difficulty
    char targetDifficulty[20];
    if (strcmp(skillLevel, SKILL_BEGINNER) == 0) {
        strcpy(targetDifficulty, DIFFICULTY_EASY);
    } else if (strcmp(skillLevel, SKILL_INTERMEDIATE) == 0) {
        strcpy(targetDifficulty, DIFFICULTY_MEDIUM);
    } else {
        strcpy(targetDifficulty, DIFFICULTY_HARD);
    }
    
    printf("\n--- Recommended Content for %s Level ---\n", skillLevel);
    printf("%-5s %-25s %-12s %-15s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < contentCount; i++) {
        if (strcmp(content[i].difficulty, targetDifficulty) == 0) {
            found = 1;
            printf("%-5d %-25s %-12s %-15s %-8s %-8d\n",
                   content[i].contentId, content[i].title, content[i].type,
                   content[i].topic, content[i].difficulty, content[i].estimatedDuration);
        }
    }
    
    if (!found) {
        printf("No content found for %s skill level.\n", skillLevel);
    }
}

// Function to recommend by learning style
void recommendByLearningStyle() {
    Content content[MAX_CONTENT];
    int contentCount;
    char learningStyle[20];
    
    printf("\n--- Recommend by Learning Style ---\n");
    
    if (!loadContentFromFile(content, &contentCount)) {
        printf("Error loading content data.\n");
        return;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    do {
        printf("Enter learning style (%s/%s/%s/%s): ", 
               LEARNING_STYLE_TEXT, LEARNING_STYLE_VIDEO, LEARNING_STYLE_CODE, LEARNING_STYLE_MIXED);
        fgets(learningStyle, sizeof(learningStyle), stdin);
        learningStyle[strcspn(learningStyle, "\n")] = 0;
        
        if (!isValidLearningStyle(learningStyle)) {
            printf(ERROR_INVALID_INPUT "\n");
        }
    } while (!isValidLearningStyle(learningStyle));
    
    printf("\n--- Recommended Content for %s Learning Style ---\n", learningStyle);
    printf("%-5s %-25s %-12s %-15s %-8s %-8s\n",
           "ID", "Title", "Type", "Topic", "Difficulty", "Duration");
    printf("--------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < contentCount; i++) {
        if (strcmp(learningStyle, LEARNING_STYLE_MIXED) == 0 ||
            (strcmp(learningStyle, LEARNING_STYLE_VIDEO) == 0 && strcmp(content[i].type, CONTENT_TYPE_VIDEO) == 0) ||
            (strcmp(learningStyle, LEARNING_STYLE_TEXT) == 0 && strcmp(content[i].type, CONTENT_TYPE_READING) == 0) ||
            (strcmp(learningStyle, LEARNING_STYLE_CODE) == 0 && strcmp(content[i].type, CONTENT_TYPE_EXERCISE) == 0)) {
            found = 1;
            printf("%-5d %-25s %-12s %-15s %-8s %-8d\n",
                   content[i].contentId, content[i].title, content[i].type,
                   content[i].topic, content[i].difficulty, content[i].estimatedDuration);
        }
    }
    
    if (!found) {
        printf("No content found for %s learning style.\n", learningStyle);
    }
}

// Function to recommend mixed content (scenario-based)
void recommendMixedContent() {
    LearnerProfile learners[MAX_LEARNERS];
    Content content[MAX_CONTENT];
    int learnerCount, contentCount;
    int learnerId;
    int found = 0;
    
    printf("\n--- Recommend Mixed Content Scenario ---\n");
    
    if (!loadLearnersFromFile(learners, &learnerCount) ||
        !loadContentFromFile(content, &contentCount)) {
        printf("Error loading data.\n");
        return;
    }
    
    printf("Enter learner ID: ");
    scanf("%d", &learnerId);
    
    // Find the learner
    LearnerProfile* learner = NULL;
    for (int i = 0; i < learnerCount; i++) {
        if (learners[i].id == learnerId) {
            learner = &learners[i];
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf(ERROR_ID_NOT_FOUND "\n");
        return;
    }
    
    printf("\n--- Mixed Content Recommendation for %s ---\n", learner->name);
    printf("Learning Path: Video + Code Exercise + Reading Material\n\n");
    
    // Find one content of each type
    Content videoContent = {0}, exerciseContent = {0}, readingContent = {0};
    int videoFound = 0, exerciseFound = 0, readingFound = 0;
    
    for (int i = 0; i < contentCount; i++) {
        if (!videoFound && strcmp(content[i].type, CONTENT_TYPE_VIDEO) == 0 &&
            strcmp(content[i].difficulty, learner->skillLevel) == 0) {
            videoContent = content[i];
            videoFound = 1;
        }
        if (!exerciseFound && strcmp(content[i].type, CONTENT_TYPE_EXERCISE) == 0 &&
            strcmp(content[i].difficulty, learner->skillLevel) == 0) {
            exerciseContent = content[i];
            exerciseFound = 1;
        }
        if (!readingFound && strcmp(content[i].type, CONTENT_TYPE_READING) == 0 &&
            strcmp(content[i].difficulty, learner->skillLevel) == 0) {
            readingContent = content[i];
            readingFound = 1;
        }
    }
    
    printf("1. START WITH VIDEO TUTORIAL:\n");
    if (videoFound) {
        printf("   ID: %d\n", videoContent.contentId);
        printf("   Title: %s\n", videoContent.title);
        printf("   Topic: %s\n", videoContent.topic);
        printf("   Duration: %d minutes\n", videoContent.estimatedDuration);
    } else {
        printf("   No suitable video content found.\n");
    }
    
    printf("\n2. PRACTICE WITH CODE EXERCISE:\n");
    if (exerciseFound) {
        printf("   ID: %d\n", exerciseContent.contentId);
        printf("   Title: %s\n", exerciseContent.title);
        printf("   Topic: %s\n", exerciseContent.topic);
        printf("   Duration: %d minutes\n", exerciseContent.estimatedDuration);
    } else {
        printf("   No suitable exercise content found.\n");
    }
    
    printf("\n3. REINFORCE WITH READING MATERIAL:\n");
    if (readingFound) {
        printf("   ID: %d\n", readingContent.contentId);
        printf("   Title: %s\n", readingContent.title);
        printf("   Topic: %s\n", readingContent.topic);
        printf("   Duration: %d minutes\n", readingContent.estimatedDuration);
    } else {
        printf("   No suitable reading content found.\n");
    }
    
    printf("\nTotal Estimated Learning Time: %d minutes\n",
           (videoFound ? videoContent.estimatedDuration : 0) +
           (exerciseFound ? exerciseContent.estimatedDuration : 0) +
           (readingFound ? readingContent.estimatedDuration : 0));
}

// Function to get resource recommendations (main menu for this module)
void getResourceRecommendations() {
    int choice;
    
    while (1) {
        printf("\n--- Get Resource Recommendations ---\n");
        printf("1. Generate Personalized Recommendations\n");
        printf("2. Recommend by Skill Level\n");
        printf("3. Recommend by Learning Style\n");
        printf("4. Recommend Mixed Content Scenario\n");
        printf("5. Back to Main Menu\n");
        printf("\nEnter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                generatePersonalizedRecommendations();
                break;
            case 2:
                recommendBySkillLevel();
                break;
            case 3:
                recommendByLearningStyle();
                break;
            case 4:
                recommendMixedContent();
                break;
            case 5:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-5.\n");
                break;
        }
    }
}
