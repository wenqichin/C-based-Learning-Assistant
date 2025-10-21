#ifndef CONSTANTS_H
#define CONSTANTS_H

// System Constants
#define MAX_LEARNERS 100
#define MAX_CONTENT 200
#define MAX_INTERACTIONS 1000
#define MAX_NAME_LENGTH 50
#define MAX_TOPIC_LENGTH 30
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_FILENAME_LENGTH 100

// File Names
#define LEARNERS_FILE "learners.txt"
#define CONTENT_FILE "content.txt"
#define INTERACTIONS_FILE "interactions.txt"
#define REPORTS_FILE "reports.txt"

// Learning Styles
#define LEARNING_STYLE_TEXT "text"
#define LEARNING_STYLE_VIDEO "video"
#define LEARNING_STYLE_CODE "code"
#define LEARNING_STYLE_MIXED "mixed"

// Skill Levels
#define SKILL_BEGINNER "beginner"
#define SKILL_INTERMEDIATE "intermediate"
#define SKILL_ADVANCED "advanced"

// Content Types
#define CONTENT_TYPE_TUTORIAL "tutorial"
#define CONTENT_TYPE_VIDEO "video"
#define CONTENT_TYPE_EXERCISE "exercise"
#define CONTENT_TYPE_QUIZ "quiz"
#define CONTENT_TYPE_READING "reading"

// Difficulty Levels
#define DIFFICULTY_EASY "easy"
#define DIFFICULTY_MEDIUM "medium"
#define DIFFICULTY_HARD "hard"

// Interaction Types
#define INTERACTION_QUIZ "quiz"
#define INTERACTION_CODE_ATTEMPT "code_attempt"
#define INTERACTION_VIDEO_VIEW "video_view"
#define INTERACTION_READING "reading"
#define INTERACTION_EXERCISE "exercise"

// Quiz Results
#define QUIZ_PASS_THRESHOLD 70
#define QUIZ_EXCELLENT_THRESHOLD 90

// Recommendation Weights
#define WEIGHT_SKILL_LEVEL 0.4
#define WEIGHT_LEARNING_STYLE 0.3
#define WEIGHT_PAST_PERFORMANCE 0.3

// Error Messages
#define ERROR_INVALID_INPUT "Invalid input. Please try again."
#define ERROR_FILE_NOT_FOUND "File not found or could not be opened."
#define ERROR_MEMORY_ALLOCATION "Memory allocation failed."
#define ERROR_DUPLICATE_ID "Learner ID already exists."
#define ERROR_ID_NOT_FOUND "Learner ID not found."

// Success Messages
#define SUCCESS_LEARNER_ADDED "Learner profile added successfully."
#define SUCCESS_LEARNER_UPDATED "Learner profile updated successfully."
#define SUCCESS_LEARNER_DELETED "Learner profile deleted successfully."
#define SUCCESS_CONTENT_ADDED "Content added successfully."
#define SUCCESS_INTERACTION_LOGGED "Interaction logged successfully."

#endif
