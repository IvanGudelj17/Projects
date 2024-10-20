// To-Do List Application
// Each user has access to a menu after logging in, allowing them to manage their tasks effectively.
// Users are identified by their email, password, secure password, and a vector that stores their tasks.
// By default, tasks are marked as uncompleted, but users can change their completion status at any time.
// The secure password is specifically used for accessing private tasks (optional feature).
// The application is structured around the following classes: ToDoList, User, and Task.



#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task
{
private:
	string TaskName;
	bool IsTaskCompleted;
	bool IsTaskPrivate;

public:
	// Constructor
	Task() : TaskName(""), IsTaskCompleted(false), IsTaskPrivate(false) {}

	

	// Get methods to access private variables
	string GetTaskName() const { return TaskName; }
	bool GetCompletedStatus() const { return IsTaskCompleted; }
	bool GetPrivateStatus() const { return IsTaskPrivate; }


	// Set methods to modify private variables
	void SetTaskName(const string& name) { TaskName = name; }
	void SetCompletedStatus(bool completed) { IsTaskCompleted = completed; }
	void SetPrivateStatus(bool isPrivate) { IsTaskPrivate = isPrivate; }
};
class UserOfList 
{
private:
	string UserEmail;          
	string UserPassword;       
	string UserSafePassword;   // User's safe password for additional security
	vector<Task> UserTasks;    // List of tasks associated with the user

public:
	 // Get methods to access private variables
	string GetUserEmail() const{ return UserEmail; }
	string GetUserPassword() { return UserPassword; }
	string GetUserSafePassword() { return UserSafePassword;; }

	// Set methods to modify private variables
	void SetUserEmail(const string& email) {UserEmail = email;}
	void SetUserPassword(const string& password) {UserPassword = password;}
	void SetUserSafePassword(const string& safePassword) {UserSafePassword = safePassword;}

	UserOfList() { UserEmail = "";  UserPassword = ""; UserSafePassword = "";}// Constructor initializes user data with default values
	

	// Method to create a new task for the user
	void CreateNewTask( UserOfList* CurrentUser)
	{
		string NewTaskName;
		bool IsPrivate=false;
		
		Task NewTask;// Creating a new Task

		// Setting the task name and privacy status
		cout << "Unesite ime novog zadatka!: ";
		cin.ignore(); 
		getline(cin, NewTaskName);//name
		cout << "Is this Task private?(1-YES/0-NO): ";
		cin >> IsPrivate;//Private status

		// Set task properties
		NewTask.SetPrivateStatus(IsPrivate);
		NewTask.SetTaskName(NewTaskName);

		// Add the task to the user's task list
		CurrentUser->UserTasks.push_back(NewTask);
		cout << "Task is added succesfully!\n";
		
	
	}

	// Method to delete a task 
	void DeleteTaskFromListByNumber(UserOfList* CurrentUser)
	{
		int NumberOfTaskToDelete;
		int SizeOfTasksAlreaadyExistings = CurrentUser->UserTasks.size();
		bool GoodEntrenceFlag = false;

		while (GoodEntrenceFlag == false)
		{
			int SecureDecision;
			cout << "\t\t Do you want to enter Secure Status?(1-YES, 2-NO)-> "; cin >> SecureDecision;
			if (SecureDecision != 1 && SecureDecision != 2)
			{
				cout << "Invalid decision.\n";
				break;
			}
			PrintToDoList(CurrentUser, SecureDecision);
			cout << "\nEnter the number of the task you want to delete: "; cin >> NumberOfTaskToDelete;
			
			// Check if the entered number is within the range of existing tasks
				if (NumberOfTaskToDelete > 0 && NumberOfTaskToDelete <= SizeOfTasksAlreaadyExistings)
				{
					GoodEntrenceFlag = true;
					CurrentUser->UserTasks.erase(CurrentUser->UserTasks.begin() + (NumberOfTaskToDelete-1));
					return;
				}
				else 
				{
					cout << "Invalid number chosen, not in range...\n";
				}
	
		}

	}

	void ChangeCompletedStatus(UserOfList* CurrentUser)
	{
		int TaskNumber;
		int SecureDecision;
		
		cout << "\tDo you want to enter Secure Status?(1-Yes, 2-No)"; cin >> SecureDecision;
		if (SecureDecision != 2 && SecureDecision != 1) { cout << "Invalid decision."; return; }
		PrintToDoList(CurrentUser, SecureDecision);
		cout << "Enter by Number Which Task Completed Status you want to change: "; cin >> TaskNumber;cin.ignore();

		CurrentUser->UserTasks[TaskNumber-1].SetCompletedStatus(true);

	}

	// Method to print the user's  list
	void PrintToDoList(UserOfList* CurrentUser, int SecureDecision)
	{
		int counter = 1;
		cout << "Your To-Do List Tasks:\n";

		// Check if the user has no tasks
		if (CurrentUser->UserTasks.empty())
		{
			cout << "You still don't have any tasks. Try adding some first.\n";
			return;
		}

		// 	 Based on Secure Descion we decide will we print the Priavte Task or not.
		if (SecureDecision == 1)
		{
				for (const Task& task : CurrentUser->UserTasks)
				{
					//print only Public tasks
					if (task.GetPrivateStatus() == false)
					{
						cout << counter << ". " << task.GetTaskName()
							<< " [Task Status: " << (task.GetCompletedStatus() ? "Completed" : "Not Completed") << "]\n";
						counter++;
					}
				}
		}
		else {
			for (const Task& task : CurrentUser->UserTasks)
			{
				//print all tasks!
					cout << counter << ". " << task.GetTaskName()
						<< " [Task Status: " << (task.GetCompletedStatus() ? "Completed" : "Not Completed") << "]\n";
					counter++;
			}
		}
	}
};
class ToDoList
{
private:
	vector <UserOfList> ListUser;// List of all useres that has beeen registred in app

public:
	//data user enter while sign Up
	string EnteredEmail;
	string EnteredPassword;

	ToDoList() {}//Constructor 
	
	// Method for user signup
	UserOfList* SignUp() {
		cout << "****************\n";
		cout << "Enter Email->"; cin >> EnteredEmail;
		cout << "Enter Password->"; cin >> EnteredPassword;
		cout << "****************\n";
		return CheckExistence( EnteredEmail,  EnteredPassword);
	}

	// Method to check if the user already exists
	UserOfList* CheckExistence(string EnteredEmail, string EnteredPassword)
	{
		for (UserOfList& element : ListUser)
		{
			if (element.GetUserEmail() == EnteredEmail && element.GetUserPassword() == EnteredPassword)
			{
				//if we find same data for one user in vector, we retun that element and return him to main.
				cout << " Succesfully Signed Up!\n";
				return &element; break;
			}
			
		}
		return nullptr;// Return nullptr if signup fails

	}

	// Method to display the user menu after successful Login
	void UserMenu(UserOfList* CurrentUser)
	{
		int MenuDecision = 0;
		while (MenuDecision != 5)
		{
			cout << "****************\n";
			cout << "Choose an option:\n";
			cout << "1. Create New Task\n";
			cout << "2. Print List\n";
			cout << "3. Delete Task From List\n";
			cout << "4. Change Completed status of your task\n";
			cout << "5. Log Out\n";
			cin >> MenuDecision;
			cout << "****************\n";

			switch (MenuDecision)
			{
			case 1: CurrentUser->CreateNewTask(CurrentUser); break;
			case 2:
				int SecureDecision;
				cout << "\t\t Do you want to enter Secure Status?(1-Yes, 2-No)-> "; cin >> SecureDecision;
				if (SecureDecision != 1 && SecureDecision != 2)
				{
					cout << "Invalid decision.\n";
					break;
				}
				CurrentUser->PrintToDoList(CurrentUser, SecureDecision); break;
			case 3: CurrentUser->DeleteTaskFromListByNumber(CurrentUser); break;
			case 4: CurrentUser->ChangeCompletedStatus(CurrentUser); break;
			case 5: cout << "Logging out...\n"; break;
			default: cout << "Invalid choice. Try again.\n"; break;
			}
		}
	}

	// Method to create a new account
	void CreateNewAccount()
	{
		//while creating new account we will worry about 1. Is email already existing!,2. is password bigger then 3 letters!
		string NewUserEmail=" ";
		string NewUserPassword = "";
		string NewPrivatePassword = "";
		bool NewUserValidation = false;
		

		while (NewUserValidation ==false)
		{
			cout << "Enter Email->"; cin >> NewUserEmail;
			cout << "Enter Password->"; cin >> NewUserPassword;
			cout << "Enter Private Password"; cin >> NewPrivatePassword;

			// Check conditions for account creation
			bool MailExistAlready = false;
			for (UserOfList element : ListUser)
			{
				if (element.GetUserEmail() == NewUserEmail )
				{
					
					MailExistAlready = true;
					break;
				}
			}
			if (MailExistAlready || NewUserPassword.length() < 3)
			{
				cout << "*** Email already exists, try again or sign up. Also, your password must be at least 3 characters long! ***\n";
			}

			else
			{
				//Create and pushBack NewUser in vector, cause registration is accepted as Valid!
				UserOfList NewUser;
				NewUser.SetUserEmail(NewUserEmail);
				NewUser.SetUserPassword(NewUserPassword);
				NewUser.SetUserSafePassword(NewPrivatePassword);
				ListUser.push_back(NewUser);
				NewUserValidation = true;
				cout << "Account created successfully!\n";
				return;
			}
		}
	}

	// Method to print the list of users
	void PrintToDoUsers()
	{
		cout << "****************\n";
		int counter = 1;
		for (const auto& element : ListUser)
		{
			cout << counter << ". " << element.GetUserEmail()<<endl;
			counter++;
		}
		cout << "****************\n";
		return;
	}
};
int main() {
	int InitialDecision = 0;
	ToDoList app; // Create an object of ToDoList

	while (InitialDecision != 3) {
		// Display the main menu
		cout << "\n***** TO DO LIST *****\n";
		cout << "1. Create New Account\n";
		cout << "2. Sign In\n";
		cout << "3. Exit\n";
		cout << "4. Show all To-Do List users\n";
		cout << "Choose an option: ";
		cin >> InitialDecision;

		switch (InitialDecision)
		{
		case 1:
			// Create a new account
			app.CreateNewAccount();
			break;

		case 2: 
		{
			UserOfList* CurrentUser = app.SignUp();
			if (CurrentUser)
				{
					// Display the user menu only if the sign-in is successful
					app.UserMenu(CurrentUser);
				}
			else
				{
					cout << "Invalid user data. Please try again or exit the app.\n";
				}
			break;
		}

		case 3:
			cout << "Exiting the application...\n";
			return 0; // Exit the program

		case 4:
			// Show all registered users
			cout << "*** LIST OF APP USERS ***\n";
			app.PrintToDoUsers();
			break;
		default:
			cout << "Invalid choice. Please select an option from 1 to 4.\n";
			break;
		}
	}
	return 0;
}



