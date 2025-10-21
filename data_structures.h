#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "constants.h"

// Date structure for tracking interactions
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Time structure for detailed logging
typedef struct {
    int hour;
    int minute;
    int second;
} Time;

// Learner Profile Structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char learningStyle[20];
    char skillLevel[20];
    char preferredContentType[20];
    int totalInteractions;
    float averageScore;
    Date lastActivity;
} LearnerProfile;

// Content Structure
typedef struct {
    int contentId;
    char title[MAX_NAME_LENGTH];
    char type[20];
    char topic[MAX_TOPIC_LENGTH];
    char difficulty[20];
    char description[MAX_DESCRIPTION_LENGTH];
    int estimatedDuration; // in minutes
    int viewCount;
    float averageRating;
} Content;

// Interaction Structure
typedef struct {
    int interactionId;
    int learnerId;
    int contentId;
    char type[20];
    Date date;
    Time time;
    float score; // for quizzes and exercises
    int attempts; // number of attempts
    char feedback[200];
    int duration; // time spent in minutes
} Interaction;

// Recommendation Structure
typedef struct {
    int learnerId;
    int contentId;
    float relevanceScore;
    char reason[200];
} Recommendation;

// Progress Report Structure
typedef struct {
    int learnerId;
    char learnerName[MAX_NAME_LENGTH];
    int totalInteractions;
    float averageScore;
    int completedContent;
    char strengths[200];
    char weaknesses[200];
    char recommendations[200];
    Date reportDate;
} ProgressReport;

// System Statistics Structure
typedef struct {
    int totalLearners;
    int totalContent;
    int totalInteractions;
    float systemAverageScore;
    char mostPopularContent[MAX_NAME_LENGTH];
    char mostActiveLearner[MAX_NAME_LENGTH];
} SystemStats;

#endif
