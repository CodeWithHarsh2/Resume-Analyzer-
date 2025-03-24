#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 40
#define MAX_LENGTH 5000

// Function to convert string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

// Function to check if a keyword is present in the resume
int keywordExists(char *resume, char *keyword) {
    return strstr(resume, keyword) != NULL;
}

// Function to analyze resume and generate a report
void analyzeResume(char *filename, char *keywords[], int keywordCount, char *categories[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open resume file.\n");
        return;
    }

    char *resume = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (!resume) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(resume, sizeof(char), MAX_LENGTH, file);
    fclose(file);
    toLowerCase(resume);

    int foundKeywords = 0;
    int categoryMatch[MAX_KEYWORDS] = {0};

    printf("\n🔍 **Resume Analysis Report** 🔍\n");
    printf("--------------------------------\n");

    for (int i = 0; i < keywordCount; i++) {
        if (keywordExists(resume, keywords[i])) {
            printf("✅ Found (%s): %s\n", categories[i], keywords[i]);
            foundKeywords++;
            categoryMatch[i] = 1;
        } else {
            printf("❌ Missing (%s): %s\n", categories[i], keywords[i]);
        }
    }

    float matchPercentage = ((float)foundKeywords / keywordCount) * 100;
    printf("\n📊 **Match Percentage:** %.2f%%\n", matchPercentage);

    if (matchPercentage < 70) {
        printf("\n⚠️ **Suggestions for Improvement:**\n");
        for (int i = 0; i < keywordCount; i++) {
            if (!categoryMatch[i]) {
                printf("- Consider adding '%s' (%s) to improve your resume.\n", keywords[i], categories[i]);
            }
        }
    } else {
        printf("\n🎉 Your resume is well-optimized for this job!\n");
    }
    free(resume);
}

int main() {
    char *keywords[MAX_KEYWORDS] = {
        "c programming", "data structures", "algorithms", "problem solving", "software development",
        "debugging", "computer science", "system design", "object-oriented programming", "linux",
        "multithreading", "memory management", "file handling", "optimization", "operating systems",
        "networking", "databases", "shell scripting", "api development", "performance tuning",
        "machine learning", "deep learning", "artificial intelligence", "big data", "cloud computing",
        "agile development", "version control", "git", "docker", "kubernetes",
        "leadership", "teamwork", "communication", "critical thinking", "project management",
        "presentation skills", "time management", "adaptability", "creativity", "emotional intelligence"
    };

    char *categories[MAX_KEYWORDS] = {
        "Programming", "Programming", "Programming", "Problem-Solving", "Development",
        "Debugging", "Computer Science", "System Design", "OOP", "Operating System",
        "Multithreading", "Memory Management", "File Handling", "Optimization", "Operating System",
        "Networking", "Databases", "Scripting", "Development", "Performance",
        "AI/ML", "AI/ML", "AI/ML", "Big Data", "Cloud Computing",
        "Software Development", "Version Control", "Version Control", "DevOps", "DevOps",
        "Soft Skills", "Soft Skills", "Soft Skills", "Soft Skills", "Soft Skills",
        "Soft Skills", "Soft Skills", "Soft Skills", "Soft Skills", "Soft Skills"
    };

    int keywordCount = MAX_KEYWORDS;
    char filename[100];

    printf("Enter the resume file name (e.g., resume.txt): ");
    scanf("%s", filename);

    analyzeResume(filename, keywords, keywordCount, categories);

    return 0;
}
