# C-based Learning Assistant for Programming Education

A comprehensive learning management system built in C that simulates a personalized programming tutor. The system stores and analyzes learner interaction data from multiple content types and provides personalized recommendations and feedback.

## 🎯 Core Functionalities

### 1. Learner Profile & Content Management
- **Add, update, and remove learner profiles** with comprehensive validation
- **Store learner preferences** (learning styles, preferred content types)
- **Record skill levels** and current progress
- **Store and categorize programming learning resources** by type, difficulty, and topic
- **Full CRUD operations** with data persistence

### 2. Learning Interaction Logging
- **Store interaction data** (quiz results, code attempts, video view counts)
- **Maintain history** of learner activities in text files
- **Track multiple interaction types**: quizzes, code attempts, video views, reading activities, exercises
- **Comprehensive logging** with timestamps, scores, and feedback

### 3. Recommendation Engine
- **Suggest resources** based on learner profile and past interactions
- **Multiple recommendation scenarios** including mixed content recommendations
- **Weighted scoring system** considering skill level, learning style, and past performance
- **Personalized content suggestions** with relevance scoring

### 4. Feedback Generator & Evaluation
- **Automated hints** based on quiz results and code attempts
- **Flag repeated mistakes** and suggest specific resources
- **Generate summary reports** on learner progress
- **Performance analytics** and personalized feedback

## 🏗️ System Architecture

### Data Structures
- **LearnerProfile**: Complete learner information with preferences and statistics
- **Content**: Learning materials with categorization and metadata
- **Interaction**: Detailed interaction logging with timestamps and scores
- **Recommendation**: Personalized content suggestions with scoring
- **ProgressReport**: Comprehensive progress analysis

### File Organization
```
C-based-Learning-Assistant/
├── menu.c                    # Main program entry point
├── learner_profile.c         # Learner management system
├── content_management.c      # Content repository management
├── interaction_logging.c     # Interaction tracking system
├── recommendation_engine.c   # Personalized recommendations
├── feedback_reports.c        # Progress reports and analytics
├── file_operations.c         # Data persistence layer
├── constants.h               # System constants and validation
├── data_structures.h         # Data structure definitions
├── learner_profile.h         # Learner management headers
├── content_management.h      # Content management headers
├── interaction_logging.h     # Interaction logging headers
├── recommendation_engine.h   # Recommendation system headers
├── feedback_reports.h        # Feedback system headers
├── file_operations.h         # File I/O headers
├── Makefile                  # Build configuration
├── sample_data.c             # Sample data generator
└── README.md                 # This documentation
```

## 🚀 Getting Started

### Prerequisites
- GCC compiler with C99 support
- Make utility (optional but recommended)

### Compilation

#### Using Makefile (Recommended)
```bash
make
```

#### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -o learning_assistant \
    menu.c learner_profile.c file_operations.c content_management.c \
    interaction_logging.c recommendation_engine.c feedback_reports.c
```

### Running the Program
```bash
./learning_assistant
```

### Creating Sample Data
```bash
gcc -o sample_data sample_data.c file_operations.c -std=c99
./sample_data
```

## 📋 Usage Guide

### Main Menu Options
1. **Manage Learner Profiles** - Complete CRUD operations for learner data
2. **Log Learning Interaction** - Track various types of learning activities
3. **View Content Repository** - Browse and manage learning content
4. **Get Resource Recommendations** - Get personalized content suggestions
5. **Generate Feedback & Reports** - Create progress reports and analytics
6. **Exit** - Close the program

### Learner Profile Management
- **Add New Profile**: Auto-generated ID, validated inputs
- **View All Profiles**: Tabular display with statistics
- **Search by ID**: Quick learner lookup
- **Update Profile**: Modify existing learner information
- **Delete Profile**: Remove learner with confirmation

### Content Management
- **Add Content**: Create new learning materials with categorization
- **Browse Content**: View all available content
- **Search Functions**: Filter by topic, type, or difficulty
- **Statistics**: View content usage and performance metrics

### Interaction Logging
- **Quiz Attempts**: Log quiz results with scores and feedback
- **Code Attempts**: Track programming exercises with correctness scores
- **Video Views**: Record video consumption with duration
- **Reading Activities**: Log text-based learning sessions
- **Exercise Attempts**: Track practice exercises with performance data

### Recommendation System
- **Personalized Recommendations**: AI-like suggestions based on learner profile
- **Skill Level Matching**: Content recommendations by difficulty
- **Learning Style Matching**: Content type recommendations
- **Mixed Content Scenarios**: Structured learning paths (video + exercise + reading)

### Feedback & Reports
- **Progress Reports**: Comprehensive learner performance analysis
- **Performance Analytics**: System-wide statistics and insights
- **Personalized Feedback**: Individual learner guidance and encouragement

## 🔧 Technical Features

### Input Validation
- **Comprehensive validation** for all user inputs
- **Symbolic constants** for consistent validation rules
- **Error handling** with user-friendly messages
- **Data type validation** and range checking

### Data Persistence
- **Text file storage** for all data types
- **Structured data format** with delimited fields
- **Atomic operations** for data integrity
- **Backup and recovery** capabilities

### Modular Design
- **Separate modules** for each major functionality
- **Header files** for clean interface definitions
- **Function-based architecture** with clear responsibilities
- **No global variables** following best practices

### Programming Constructs Used
- ✅ **Control Structures**: if-else, switch-case, loops
- ✅ **Functions**: Modular function design with clear interfaces
- ✅ **Arrays**: Dynamic data management and processing
- ✅ **Pointers**: Efficient data manipulation and file operations
- ✅ **Structures**: Complex data organization and management
- ✅ **Unions**: Advanced data type handling (in data structures)
- ✅ **Files**: Comprehensive file I/O operations
- ✅ **Symbolic Constants**: System-wide configuration management

## 📊 Sample Data

The system includes sample data generation for testing:
- **4 Learner Profiles** with different learning styles and skill levels
- **6 Content Items** covering various topics and difficulty levels
- **7 Learning Interactions** demonstrating different activity types

## 🧪 Testing

### Test Cases Covered
- **Valid Input Testing**: All normal operation scenarios
- **Invalid Input Testing**: Error handling and validation
- **Edge Cases**: Boundary conditions and special cases
- **Data Integrity**: File operations and data consistency
- **User Interface**: Menu navigation and user experience

### Sample Test Scenarios
1. **Add Learner Profile**: Test with valid and invalid inputs
2. **Log Interactions**: Test different interaction types
3. **Generate Recommendations**: Test recommendation algorithms
4. **Create Reports**: Test report generation and formatting
5. **Data Persistence**: Test file operations and data recovery

## 🎓 Educational Value

This system demonstrates:
- **Advanced C Programming**: Complex data structures and algorithms
- **Software Engineering**: Modular design and best practices
- **Data Management**: File I/O and data persistence
- **User Interface Design**: Menu-driven console applications
- **System Analysis**: Requirements analysis and implementation
- **Testing Methodology**: Comprehensive testing strategies

## 📈 Future Enhancements

Potential improvements for extended functionality:
- **Database Integration**: Replace text files with SQLite
- **Web Interface**: HTML/CSS frontend for better UX
- **Machine Learning**: Advanced recommendation algorithms
- **Real-time Analytics**: Live performance monitoring
- **Multi-language Support**: Internationalization features
- **API Integration**: External learning resource integration

## 🤝 Contributing

This project serves as a comprehensive example of C programming best practices and can be extended for educational or practical purposes.

## 📄 License

This project is created for educational purposes as part of a programming assignment.
