# C-based Learning Assistant

A comprehensive learning management system built in C for programming education.

## Features

- **Manage Learner Profiles**: Add, view, update, and delete learner profiles with learning preferences
- **Log Learning Interactions**: Track learning sessions and progress
- **View Content Repository**: Browse and search learning materials
- **Get Resource Recommendations**: Personalized learning resource suggestions
- **Generate Feedback & Reports**: Create progress reports and analytics

## Compilation

### Using Makefile (Recommended)
```bash
make
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -o learning_assistant menu.c learner_profile.c interaction_log.c view_content_repo.c resource_recommendations.c feedback_report.c
```

## Running the Program
```bash
./learning_assistant
```

## Program Structure

- `menu.c` - Main menu system and program entry point
- `learner_profile.c` - Learner profile management functionality
- `interaction_log.c` - Learning interaction logging
- `view_content_repo.c` - Content repository browsing
- `resource_recommendations.c` - Resource recommendation system
- `feedback_report.c` - Feedback and report generation
- `learner_profile.h` - Header file for learner profile functions

## Usage

1. Run the program using the commands above
2. Select from the main menu options (1-6)
3. Follow the submenu prompts for each feature
4. Use option 6 to exit the program

## Example Usage

The program matches the interface shown in the image, where you can:
- Add new learner profiles with ID, name, learning style, and skill level
- Navigate through different modules using numbered menus
- Return to the main menu from any submenu
