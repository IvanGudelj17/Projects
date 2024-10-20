# To-Do List Application

## Overview

The To-Do List Application is a simple yet effective tool for managing tasks. Users can create,
delete, and update the status of their tasks after logging in with their email and password. 
Each user has a secure password for additional security when accessing private tasks.
The application is designed using C++ and follows an object-oriented approach, with key classes such as `ToDoList`, `UserOfList`, and `Task`.

## Features

- User authentication via email and password.
- Ability to create and manage tasks.
- Tasks can be marked as completed or uncompleted.
- Option to set tasks as private, requiring a secure password for access.
- User-friendly menu for easy navigation and task management.

## Classes

### Task

- **Attributes:**
  - `TaskName`: The name of the task.
  - `IsTaskCompleted`: Status of the task (completed or not).
  - `IsTaskPrivate`: Indicates if the task is private.

- **Methods:**
  - Getters and setters for task attributes.

### UserOfList

- **Attributes:**
  - `UserEmail`: User's email for identification.
  - `UserPassword`: User's password for authentication.
  - `UserSafePassword`: Secure password for accessing private tasks.
  - `UserTasks`: Vector storing tasks associated with the user.

- **Methods:**
  - User account management (create new task, delete task, change task status).
  - Print user's task list with options for secure viewing.

### ToDoList

- **Attributes:**
  - `ListUser`: A vector containing all registered users.

- **Methods:**
  - User account creation and authentication.
  - Display user menu for task management.
