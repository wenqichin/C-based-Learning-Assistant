#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "feedback_reports.h"
#include "file_operations.h"
#include "constants.h"

// Function to generate progress report for a learner
void generateProgressReport() {
    LearnerProfile learners[MAX_LEARNERS];
    Interaction interactions[MAX_INTERACTIONS];
    Content content[MAX_CONTENT];
    int learnerCount, interactionCount, contentCount;
    int learnerId;
    int found = 0;
    
    printf("\n--- Generate Progress Report ---\n");
    
    // Load data
    if (!loadLearnersFromFile(learners, &learnerCount) ||
        !loadInteractionsFromFile(interactions, &interactionCount) ||
        !loadContentFromFile(content, &contentCount)) {
        printf("Error loading data for report generation.\n");
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
    
    // Get learner's interactions
    Interaction learnerInteractions[MAX_INTERACTIONS];
    int learnerInteractionCount;
    if (!getLearnerInteractions(learnerId, learnerInteractions, &learnerInteractionCount)) {
        learnerInteractionCount = 0;
    }
    
    // Calculate statistics
    float totalScore = 0.0;
    int scoredInteractions = 0;
    int totalDuration = 0;
    int completedContent = 0;
    int typeCount[5] = {0}; // quiz, code_attempt, video_view, reading, exercise
    
    for (int i = 0; i < learnerInteractionCount; i++) {
        if (learnerInteractions[i].score > 0) {
            totalScore += learnerInteractions[i].score;
            scoredInteractions++;
        }
        totalDuration += learnerInteractions[i].duration;
        completedContent++;
        
        // Count by type
        if (strcmp(learnerInteractions[i].type, INTERACTION_QUIZ) == 0) typeCount[0]++;
        else if (strcmp(learnerInteractions[i].type, INTERACTION_CODE_ATTEMPT) == 0) typeCount[1]++;
        else if (strcmp(learnerInteractions[i].type, INTERACTION_VIDEO_VIEW) == 0) typeCount[2]++;
        else if (strcmp(learnerInteractions[i].type, INTERACTION_READING) == 0) typeCount[3]++;
        else if (strcmp(learnerInteractions[i].type, INTERACTION_EXERCISE) == 0) typeCount[4]++;
    }
    
    float averageScore = scoredInteractions > 0 ? totalScore / scoredInteractions : 0.0;
    
    // Generate report
    printf("\n=== PROGRESS REPORT ===\n");
    printf("Learner: %s (ID: %d)\n", learner->name, learner->id);
    printf("Learning Style: %s\n", learner->learningStyle);
    printf("Skill Level: %s\n", learner->skillLevel);
    printf("Report Date: %02d-%02d-%04d\n", 
           getCurrentDate().day, getCurrentDate().month, getCurrentDate().year);
    
    printf("\n--- ACTIVITY SUMMARY ---\n");
    printf("Total Interactions: %d\n", learnerInteractionCount);
    printf("Completed Content Items: %d\n", completedContent);
    printf("Total Learning Time: %d minutes (%.1f hours)\n", 
           totalDuration, totalDuration / 60.0);
    
    printf("\n--- PERFORMANCE METRICS ---\n");
    printf("Average Score: %.2f\n", averageScore);
    if (averageScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("Performance Level: EXCELLENT\n");
    } else if (averageScore >= QUIZ_PASS_THRESHOLD) {
        printf("Performance Level: GOOD\n");
    } else {
        printf("Performance Level: NEEDS IMPROVEMENT\n");
    }
    
    printf("\n--- ACTIVITY BREAKDOWN ---\n");
    printf("Quizzes Attempted: %d\n", typeCount[0]);
    printf("Code Exercises: %d\n", typeCount[1]);
    printf("Video Views: %d\n", typeCount[2]);
    printf("Reading Activities: %d\n", typeCount[3]);
    printf("Exercise Attempts: %d\n", typeCount[4]);
    
    // Generate strengths and weaknesses
    printf("\n--- STRENGTHS ---\n");
    if (averageScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("- Consistently high performance across all activities\n");
        printf("- Strong understanding of concepts\n");
    } else if (averageScore >= QUIZ_PASS_THRESHOLD) {
        printf("- Solid performance in most areas\n");
        printf("- Good engagement with learning materials\n");
    } else {
        printf("- Active participation in learning activities\n");
        printf("- Willingness to attempt challenging content\n");
    }
    
    if (typeCount[1] > typeCount[0]) {
        printf("- Strong preference for hands-on coding practice\n");
    }
    if (typeCount[2] > typeCount[3]) {
        printf("- Good engagement with video content\n");
    }
    
    printf("\n--- AREAS FOR IMPROVEMENT ---\n");
    if (averageScore < QUIZ_PASS_THRESHOLD) {
        printf("- Focus on fundamental concepts before advancing\n");
        printf("- Consider additional practice with easier content\n");
    }
    if (typeCount[0] < 2) {
        printf("- Increase quiz participation for better assessment\n");
    }
    if (totalDuration < 60) {
        printf("- Increase learning time for better retention\n");
    }
    
    printf("\n--- RECOMMENDATIONS ---\n");
    if (averageScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("- Consider advancing to more challenging content\n");
        printf("- Explore advanced topics in your area of interest\n");
    } else if (averageScore >= QUIZ_PASS_THRESHOLD) {
        printf("- Continue with current learning pace\n");
        printf("- Mix different content types for comprehensive learning\n");
    } else {
        printf("- Focus on foundational concepts\n");
        printf("- Practice with easier content before advancing\n");
        printf("- Consider seeking additional help or resources\n");
    }
    
    // Save report to file
    ProgressReport report;
    report.learnerId = learnerId;
    strcpy(report.learnerName, learner->name);
    report.totalInteractions = learnerInteractionCount;
    report.averageScore = averageScore;
    report.completedContent = completedContent;
    report.reportDate = getCurrentDate();
    
    // Generate strengths and weaknesses strings
    strcpy(report.strengths, "See detailed report above");
    strcpy(report.weaknesses, "See detailed report above");
    strcpy(report.recommendations, "See detailed report above");
    
    printf("\nReport generated successfully!\n");
}

// Function to generate performance analytics
void generatePerformanceAnalytics() {
    LearnerProfile learners[MAX_LEARNERS];
    Interaction interactions[MAX_INTERACTIONS];
    int learnerCount, interactionCount;
    
    printf("\n--- Performance Analytics ---\n");
    
    if (!loadLearnersFromFile(learners, &learnerCount) ||
        !loadInteractionsFromFile(interactions, &interactionCount)) {
        printf("Error loading data for analytics.\n");
        return;
    }
    
    if (learnerCount == 0 || interactionCount == 0) {
        printf("Insufficient data for analytics.\n");
        return;
    }
    
    // Calculate system-wide statistics
    float totalScore = 0.0;
    int scoredInteractions = 0;
    int totalDuration = 0;
    int typeCount[5] = {0};
    float learnerScores[MAX_LEARNERS];
    int activeLearners = 0;
    
    for (int i = 0; i < interactionCount; i++) {
        if (interactions[i].score > 0) {
            totalScore += interactions[i].score;
            scoredInteractions++;
        }
        totalDuration += interactions[i].duration;
        
        // Count by type
        if (strcmp(interactions[i].type, INTERACTION_QUIZ) == 0) typeCount[0]++;
        else if (strcmp(interactions[i].type, INTERACTION_CODE_ATTEMPT) == 0) typeCount[1]++;
        else if (strcmp(interactions[i].type, INTERACTION_VIDEO_VIEW) == 0) typeCount[2]++;
        else if (strcmp(interactions[i].type, INTERACTION_READING) == 0) typeCount[3]++;
        else if (strcmp(interactions[i].type, INTERACTION_EXERCISE) == 0) typeCount[4]++;
    }
    
    // Calculate per-learner statistics
    for (int i = 0; i < learnerCount; i++) {
        Interaction learnerInteractions[MAX_INTERACTIONS];
        int learnerInteractionCount;
        
        if (getLearnerInteractions(learners[i].id, learnerInteractions, &learnerInteractionCount)) {
            float learnerScore = 0.0;
            int learnerScoredInteractions = 0;
            
            for (int j = 0; j < learnerInteractionCount; j++) {
                if (learnerInteractions[j].score > 0) {
                    learnerScore += learnerInteractions[j].score;
                    learnerScoredInteractions++;
                }
            }
            
            if (learnerScoredInteractions > 0) {
                learnerScores[activeLearners] = learnerScore / learnerScoredInteractions;
                activeLearners++;
            }
        }
    }
    
    float systemAverageScore = scoredInteractions > 0 ? totalScore / scoredInteractions : 0.0;
    
    printf("\n=== SYSTEM PERFORMANCE ANALYTICS ===\n");
    printf("Report Date: %02d-%02d-%04d\n", 
           getCurrentDate().day, getCurrentDate().month, getCurrentDate().year);
    
    printf("\n--- OVERALL STATISTICS ---\n");
    printf("Total Learners: %d\n", learnerCount);
    printf("Active Learners: %d\n", activeLearners);
    printf("Total Interactions: %d\n", interactionCount);
    printf("System Average Score: %.2f\n", systemAverageScore);
    printf("Total Learning Time: %d minutes (%.1f hours)\n", 
           totalDuration, totalDuration / 60.0);
    
    printf("\n--- ACTIVITY DISTRIBUTION ---\n");
    printf("Quizzes: %d (%.1f%%)\n", typeCount[0], 
           interactionCount > 0 ? (float)typeCount[0] / interactionCount * 100 : 0);
    printf("Code Attempts: %d (%.1f%%)\n", typeCount[1], 
           interactionCount > 0 ? (float)typeCount[1] / interactionCount * 100 : 0);
    printf("Video Views: %d (%.1f%%)\n", typeCount[2], 
           interactionCount > 0 ? (float)typeCount[2] / interactionCount * 100 : 0);
    printf("Reading Activities: %d (%.1f%%)\n", typeCount[3], 
           interactionCount > 0 ? (float)typeCount[3] / interactionCount * 100 : 0);
    printf("Exercise Attempts: %d (%.1f%%)\n", typeCount[4], 
           interactionCount > 0 ? (float)typeCount[4] / interactionCount * 100 : 0);
    
    printf("\n--- PERFORMANCE DISTRIBUTION ---\n");
    int excellentCount = 0, goodCount = 0, needsImprovementCount = 0;
    
    for (int i = 0; i < activeLearners; i++) {
        if (learnerScores[i] >= QUIZ_EXCELLENT_THRESHOLD) {
            excellentCount++;
        } else if (learnerScores[i] >= QUIZ_PASS_THRESHOLD) {
            goodCount++;
        } else {
            needsImprovementCount++;
        }
    }
    
    printf("Excellent Performance (≥90%%): %d learners (%.1f%%)\n", 
           excellentCount, activeLearners > 0 ? (float)excellentCount / activeLearners * 100 : 0);
    printf("Good Performance (70-89%%): %d learners (%.1f%%)\n", 
           goodCount, activeLearners > 0 ? (float)goodCount / activeLearners * 100 : 0);
    printf("Needs Improvement (<70%%): %d learners (%.1f%%)\n", 
           needsImprovementCount, activeLearners > 0 ? (float)needsImprovementCount / activeLearners * 100 : 0);
    
    printf("\n--- INSIGHTS ---\n");
    if (typeCount[2] > typeCount[3]) {
        printf("- Video content is more popular than reading materials\n");
    }
    if (typeCount[1] > typeCount[0]) {
        printf("- Hands-on coding practice is preferred over quizzes\n");
    }
    if (systemAverageScore >= QUIZ_PASS_THRESHOLD) {
        printf("- Overall system performance is satisfactory\n");
    } else {
        printf("- System performance indicates need for content improvement\n");
    }
}

// Function to generate personalized feedback
void generatePersonalizedFeedback() {
    LearnerProfile learners[MAX_LEARNERS];
    Interaction interactions[MAX_INTERACTIONS];
    int learnerCount, interactionCount;
    int learnerId;
    int found = 0;
    
    printf("\n--- Generate Personalized Feedback ---\n");
    
    if (!loadLearnersFromFile(learners, &learnerCount) ||
        !loadInteractionsFromFile(interactions, &interactionCount)) {
        printf("Error loading data for feedback generation.\n");
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
    
    // Get learner's recent interactions
    Interaction learnerInteractions[MAX_INTERACTIONS];
    int learnerInteractionCount;
    if (!getLearnerInteractions(learnerId, learnerInteractions, &learnerInteractionCount)) {
        learnerInteractionCount = 0;
    }
    
    if (learnerInteractionCount == 0) {
        printf("No interactions found for learner %d. Start learning to receive feedback!\n", learnerId);
        return;
    }
    
    // Analyze recent performance
    float recentScore = 0.0;
    int recentScoredInteractions = 0;
    int recentAttempts = 0;
    char commonMistakes[200] = "";
    
    // Look at last 5 interactions
    int startIndex = (learnerInteractionCount > 5) ? learnerInteractionCount - 5 : 0;
    
    for (int i = startIndex; i < learnerInteractionCount; i++) {
        if (learnerInteractions[i].score > 0) {
            recentScore += learnerInteractions[i].score;
            recentScoredInteractions++;
        }
        recentAttempts += learnerInteractions[i].attempts;
        
        // Check for repeated mistakes
        if (learnerInteractions[i].score < QUIZ_PASS_THRESHOLD && 
            learnerInteractions[i].attempts > 2) {
            strcat(commonMistakes, "Multiple attempts needed for content. ");
        }
    }
    
    float averageRecentScore = recentScoredInteractions > 0 ? recentScore / recentScoredInteractions : 0.0;
    
    printf("\n=== PERSONALIZED FEEDBACK FOR %s ===\n", learner->name);
    printf("Generated on: %02d-%02d-%04d\n", 
           getCurrentDate().day, getCurrentDate().month, getCurrentDate().year);
    
    printf("\n--- RECENT PERFORMANCE ---\n");
    printf("Recent Average Score: %.2f\n", averageRecentScore);
    printf("Recent Attempts: %d\n", recentAttempts);
    
    if (averageRecentScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("Performance Trend: EXCELLENT! Keep up the great work!\n");
    } else if (averageRecentScore >= QUIZ_PASS_THRESHOLD) {
        printf("Performance Trend: GOOD! You're making steady progress.\n");
    } else {
        printf("Performance Trend: NEEDS ATTENTION. Let's work on improvement.\n");
    }
    
    printf("\n--- PERSONALIZED FEEDBACK ---\n");
    
    // Generate specific feedback based on performance
    if (averageRecentScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("🌟 Outstanding work! Your consistent high performance shows excellent understanding.\n");
        printf("💡 Consider challenging yourself with more advanced content.\n");
        printf("🎯 You're ready to explore complex programming concepts.\n");
    } else if (averageRecentScore >= QUIZ_PASS_THRESHOLD) {
        printf("👍 Good progress! You're demonstrating solid understanding of the material.\n");
        printf("📚 Continue practicing to reinforce your knowledge.\n");
        printf("🔄 Try mixing different types of content for comprehensive learning.\n");
    } else {
        printf("📖 Let's focus on building a stronger foundation.\n");
        printf("🎯 Consider reviewing fundamental concepts before advancing.\n");
        printf("💪 Don't give up - every expert was once a beginner!\n");
    }
    
    // Learning style specific feedback
    if (strcmp(learner->learningStyle, LEARNING_STYLE_VIDEO) == 0) {
        printf("🎥 Since you prefer video learning, try to supplement with hands-on practice.\n");
    } else if (strcmp(learner->learningStyle, LEARNING_STYLE_CODE) == 0) {
        printf("💻 Your hands-on approach is great! Consider adding some theoretical reading.\n");
    } else if (strcmp(learner->learningStyle, LEARNING_STYLE_TEXT) == 0) {
        printf("📖 Your reading preference is excellent for deep understanding.\n");
    }
    
    // Attempt-based feedback
    if (recentAttempts > learnerInteractionCount * 2) {
        printf("🔄 You're persistent! Consider taking breaks between attempts to avoid frustration.\n");
    }
    
    // Common mistakes feedback
    if (strlen(commonMistakes) > 0) {
        printf("\n--- AREAS TO FOCUS ON ---\n");
        printf("%s\n", commonMistakes);
        printf("💡 Try breaking down complex problems into smaller steps.\n");
        printf("🤔 Take time to understand the concepts before attempting exercises.\n");
    }
    
    printf("\n--- NEXT STEPS ---\n");
    if (averageRecentScore >= QUIZ_EXCELLENT_THRESHOLD) {
        printf("1. Explore advanced topics in your area of interest\n");
        printf("2. Try teaching others what you've learned\n");
        printf("3. Work on real-world projects\n");
    } else if (averageRecentScore >= QUIZ_PASS_THRESHOLD) {
        printf("1. Continue with current learning pace\n");
        printf("2. Practice with different content types\n");
        printf("3. Set specific learning goals\n");
    } else {
        printf("1. Review fundamental concepts\n");
        printf("2. Practice with easier content first\n");
        printf("3. Consider seeking additional help or resources\n");
    }
    
    printf("\nRemember: Learning is a journey, not a race. Keep going! 🚀\n");
}

// Function to generate feedback and reports (main menu for this module)
void generateFeedbackReports() {
    int choice;
    
    while (1) {
        printf("\n--- Generate Feedback & Reports ---\n");
        printf("1. Generate Progress Report\n");
        printf("2. Generate Performance Analytics\n");
        printf("3. Generate Personalized Feedback\n");
        printf("4. Back to Main Menu\n");
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                generateProgressReport();
                break;
            case 2:
                generatePerformanceAnalytics();
                break;
            case 3:
                generatePersonalizedFeedback();
                break;
            case 4:
                return; // Go back to main menu
            default:
                printf("\nInvalid choice! Please enter a number between 1-4.\n");
                break;
        }
    }
}
