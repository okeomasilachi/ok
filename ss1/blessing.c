#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_POSTS 100

struct User {
    char username[50];
    char password[50];
    int active;
};

struct Post {
    char content[100];
    char author[50];
};

struct User users[MAX_USERS];
struct Post posts[MAX_POSTS];
int userCount = 0;
int postCount = 0;

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return;
    }

    struct User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    newUser.active = 1;

    users[userCount++] = newUser;

    printf("Registration successful!\n");
}

void loginUser() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            users[i].active = 1;
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password.\n");
}

void logoutUser() {
    char username[50];

    printf("Enter username: ");
    scanf("%s", username);

    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0) {
            users[i].active = 0;
            printf("Logout successful!\n");
            return;
        }
    }

    printf("User not found.\n");
}

void createPost() {
    if (postCount >= MAX_POSTS) {
        printf("Maximum post limit reached.\n");
        return;
    }

    char content[100];
    char author[50];

    printf("Enter your username: ");
    scanf("%s", author);

    printf("Enter post content: ");
    scanf(" %[^\n]s", content);

    struct Post newPost;
    strcpy(newPost.author, author);
    strcpy(newPost.content, content);

    posts[postCount++] = newPost;

    printf("Post created!\n");
}

void displayPosts() {
    printf("Posts:\n");
    int i;
    for (i = 0; i < postCount; i++) {
        printf("Author: %s\n", posts[i].author);
        printf("Content: %s\n\n", posts[i].content);
    }
}

int main() {
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Logout\n");
        printf("4. Create Post\n");
        printf("5. Display Posts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                logoutUser();
                break;
            case 4:
                createPost();
                break;
            case 5:
                displayPosts();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
 
