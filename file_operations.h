#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "data_structures.h"

// Function declarations for file operations
int saveLearnerToFile(const LearnerProfile* learner);
int loadLearnersFromFile(LearnerProfile learners[], int* count);
int updateLearnerInFile(const LearnerProfile* learner);
int deleteLearnerFromFile(int learnerId);

int saveContentToFile(const Content* content);
int loadContentFromFile(Content content[], int* count);
int updateContentInFile(const Content* content);
int deleteContentFromFile(int contentId);

int saveInteractionToFile(const Interaction* interaction);
int loadInteractionsFromFile(Interaction interactions[], int* count);
int getLearnerInteractions(int learnerId, Interaction interactions[], int* count);

int saveReportToFile(const ProgressReport* report);
int loadReportsFromFile(ProgressReport reports[], int* count);

// Utility functions
int getNextLearnerId();
int getNextContentId();
int getNextInteractionId();
Date getCurrentDate();
Time getCurrentTime();

// Validation functions
int isValidLearnerId(int id);
int isValidContentId(int id);
int isValidLearningStyle(const char* style);
int isValidSkillLevel(const char* level);
int isValidContentType(const char* type);
int isValidDifficulty(const char* difficulty);

#endif
