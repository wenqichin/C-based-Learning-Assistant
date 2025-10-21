#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_operations.h"

// Save learner profile to file
int saveLearnerToFile(const LearnerProfile* learner) {
    FILE *file = fopen(LEARNERS_FILE, "a");
    if (file == NULL) {
        printf(ERROR_FILE_NOT_FOUND "\n");
        return 0;
    }
    
    fprintf(file, "%d|%s|%s|%s|%s|%d|%.2f|%d-%d-%d\n",
            learner->id, learner->name, learner->learningStyle,
            learner->skillLevel, learner->preferredContentType,
            learner->totalInteractions, learner->averageScore,
            learner->lastActivity.day, learner->lastActivity.month,
            learner->lastActivity.year);
    
    fclose(file);
    return 1;
}

// Load all learners from file
int loadLearnersFromFile(LearnerProfile learners[], int* count) {
    FILE *file = fopen(LEARNERS_FILE, "r");
    if (file == NULL) {
        *count = 0;
        return 0;
    }
    
    *count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && *count < MAX_LEARNERS) {
        if (sscanf(line, "%d|%49[^|]|%19[^|]|%19[^|]|%19[^|]|%d|%f|%d-%d-%d",
                   &learners[*count].id, learners[*count].name,
                   learners[*count].learningStyle, learners[*count].skillLevel,
                   learners[*count].preferredContentType, &learners[*count].totalInteractions,
                   &learners[*count].averageScore, &learners[*count].lastActivity.day,
                   &learners[*count].lastActivity.month, &learners[*count].lastActivity.year) == 10) {
            (*count)++;
        }
    }
    
    fclose(file);
    return 1;
}

// Update learner in file
int updateLearnerInFile(const LearnerProfile* learner) {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    
    if (!loadLearnersFromFile(learners, &count)) {
        return 0;
    }
    
    // Find and update the learner
    for (int i = 0; i < count; i++) {
        if (learners[i].id == learner->id) {
            learners[i] = *learner;
            break;
        }
    }
    
    // Rewrite the entire file
    FILE *file = fopen(LEARNERS_FILE, "w");
    if (file == NULL) {
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%d|%.2f|%d-%d-%d\n",
                learners[i].id, learners[i].name, learners[i].learningStyle,
                learners[i].skillLevel, learners[i].preferredContentType,
                learners[i].totalInteractions, learners[i].averageScore,
                learners[i].lastActivity.day, learners[i].lastActivity.month,
                learners[i].lastActivity.year);
    }
    
    fclose(file);
    return 1;
}

// Delete learner from file
int deleteLearnerFromFile(int learnerId) {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    
    if (!loadLearnersFromFile(learners, &count)) {
        return 0;
    }
    
    // Find and remove the learner
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (learners[i].id == learnerId) {
            // Shift remaining learners
            for (int j = i; j < count - 1; j++) {
                learners[j] = learners[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }
    
    if (!found) {
        return 0;
    }
    
    // Rewrite the file
    FILE *file = fopen(LEARNERS_FILE, "w");
    if (file == NULL) {
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%d|%.2f|%d-%d-%d\n",
                learners[i].id, learners[i].name, learners[i].learningStyle,
                learners[i].skillLevel, learners[i].preferredContentType,
                learners[i].totalInteractions, learners[i].averageScore,
                learners[i].lastActivity.day, learners[i].lastActivity.month,
                learners[i].lastActivity.year);
    }
    
    fclose(file);
    return 1;
}

// Save content to file
int saveContentToFile(const Content* content) {
    FILE *file = fopen(CONTENT_FILE, "a");
    if (file == NULL) {
        printf(ERROR_FILE_NOT_FOUND "\n");
        return 0;
    }
    
    fprintf(file, "%d|%s|%s|%s|%s|%s|%d|%d|%.2f\n",
            content->contentId, content->title, content->type,
            content->topic, content->difficulty, content->description,
            content->estimatedDuration, content->viewCount, content->averageRating);
    
    fclose(file);
    return 1;
}

// Load all content from file
int loadContentFromFile(Content content[], int* count) {
    FILE *file = fopen(CONTENT_FILE, "r");
    if (file == NULL) {
        *count = 0;
        return 0;
    }
    
    *count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && *count < MAX_CONTENT) {
        if (sscanf(line, "%d|%49[^|]|%19[^|]|%29[^|]|%19[^|]|%199[^|]|%d|%d|%f",
                   &content[*count].contentId, content[*count].title,
                   content[*count].type, content[*count].topic,
                   content[*count].difficulty, content[*count].description,
                   &content[*count].estimatedDuration, &content[*count].viewCount,
                   &content[*count].averageRating) == 9) {
            (*count)++;
        }
    }
    
    fclose(file);
    return 1;
}

// Save interaction to file
int saveInteractionToFile(const Interaction* interaction) {
    FILE *file = fopen(INTERACTIONS_FILE, "a");
    if (file == NULL) {
        printf(ERROR_FILE_NOT_FOUND "\n");
        return 0;
    }
    
    fprintf(file, "%d|%d|%d|%s|%d-%d-%d|%d:%d:%d|%.2f|%d|%s|%d\n",
            interaction->interactionId, interaction->learnerId, interaction->contentId,
            interaction->type, interaction->date.day, interaction->date.month,
            interaction->date.year, interaction->time.hour, interaction->time.minute,
            interaction->time.second, interaction->score, interaction->attempts,
            interaction->feedback, interaction->duration);
    
    fclose(file);
    return 1;
}

// Load all interactions from file
int loadInteractionsFromFile(Interaction interactions[], int* count) {
    FILE *file = fopen(INTERACTIONS_FILE, "r");
    if (file == NULL) {
        *count = 0;
        return 0;
    }
    
    *count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && *count < MAX_INTERACTIONS) {
        if (sscanf(line, "%d|%d|%d|%19[^|]|%d-%d-%d|%d:%d:%d|%f|%d|%199[^|]|%d",
                   &interactions[*count].interactionId, &interactions[*count].learnerId,
                   &interactions[*count].contentId, interactions[*count].type,
                   &interactions[*count].date.day, &interactions[*count].date.month,
                   &interactions[*count].date.year, &interactions[*count].time.hour,
                   &interactions[*count].time.minute, &interactions[*count].time.second,
                   &interactions[*count].score, &interactions[*count].attempts,
                   interactions[*count].feedback, &interactions[*count].duration) == 14) {
            (*count)++;
        }
    }
    
    fclose(file);
    return 1;
}

// Get interactions for a specific learner
int getLearnerInteractions(int learnerId, Interaction interactions[], int* count) {
    Interaction allInteractions[MAX_INTERACTIONS];
    int totalCount;
    
    if (!loadInteractionsFromFile(allInteractions, &totalCount)) {
        *count = 0;
        return 0;
    }
    
    *count = 0;
    for (int i = 0; i < totalCount; i++) {
        if (allInteractions[i].learnerId == learnerId) {
            interactions[*count] = allInteractions[i];
            (*count)++;
        }
    }
    
    return 1;
}

// Utility functions
int getNextLearnerId() {
    LearnerProfile learners[MAX_LEARNERS];
    int count;
    int maxId = 0;
    
    if (loadLearnersFromFile(learners, &count)) {
        for (int i = 0; i < count; i++) {
            if (learners[i].id > maxId) {
                maxId = learners[i].id;
            }
        }
    }
    
    return maxId + 1;
}

int getNextContentId() {
    Content content[MAX_CONTENT];
    int count;
    int maxId = 0;
    
    if (loadContentFromFile(content, &count)) {
        for (int i = 0; i < count; i++) {
            if (content[i].contentId > maxId) {
                maxId = content[i].contentId;
            }
        }
    }
    
    return maxId + 1;
}

int getNextInteractionId() {
    Interaction interactions[MAX_INTERACTIONS];
    int count;
    int maxId = 0;
    
    if (loadInteractionsFromFile(interactions, &count)) {
        for (int i = 0; i < count; i++) {
            if (interactions[i].interactionId > maxId) {
                maxId = interactions[i].interactionId;
            }
        }
    }
    
    return maxId + 1;
}

Date getCurrentDate() {
    Date currentDate;
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    currentDate.day = ltm->tm_mday;
    currentDate.month = ltm->tm_mon + 1;
    currentDate.year = ltm->tm_year + 1900;
    
    return currentDate;
}

Time getCurrentTime() {
    Time currentTime;
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    currentTime.hour = ltm->tm_hour;
    currentTime.minute = ltm->tm_min;
    currentTime.second = ltm->tm_sec;
    
    return currentTime;
}

// Validation functions
int isValidLearnerId(int id) {
    return id > 0;
}

int isValidContentId(int id) {
    return id > 0;
}

int isValidLearningStyle(const char* style) {
    return (strcmp(style, LEARNING_STYLE_TEXT) == 0 ||
            strcmp(style, LEARNING_STYLE_VIDEO) == 0 ||
            strcmp(style, LEARNING_STYLE_CODE) == 0 ||
            strcmp(style, LEARNING_STYLE_MIXED) == 0);
}

int isValidSkillLevel(const char* level) {
    return (strcmp(level, SKILL_BEGINNER) == 0 ||
            strcmp(level, SKILL_INTERMEDIATE) == 0 ||
            strcmp(level, SKILL_ADVANCED) == 0);
}

int isValidContentType(const char* type) {
    return (strcmp(type, CONTENT_TYPE_TUTORIAL) == 0 ||
            strcmp(type, CONTENT_TYPE_VIDEO) == 0 ||
            strcmp(type, CONTENT_TYPE_EXERCISE) == 0 ||
            strcmp(type, CONTENT_TYPE_QUIZ) == 0 ||
            strcmp(type, CONTENT_TYPE_READING) == 0);
}

int isValidDifficulty(const char* difficulty) {
    return (strcmp(difficulty, DIFFICULTY_EASY) == 0 ||
            strcmp(difficulty, DIFFICULTY_MEDIUM) == 0 ||
            strcmp(difficulty, DIFFICULTY_HARD) == 0);
}
