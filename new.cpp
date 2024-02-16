#include <bits/stdc++.h>

using namespace std;

// Structure to represent a task
struct Task {
    string description;
    bool completed;

    Task(const string& desc, bool status) : description(desc), completed(status) {}
};

// Function to display pending tasks
void displayPendingTasks(const vector<Task>& tasks) {
    cout << "\nPending Tasks:" << endl;
    int count = 1;
    for (const auto& task : tasks) {
        if (!task.completed) {
            cout << count << ". " << task.description << endl;
            count++;
        }
    }
    if (count == 1) {
        cout << "No pending tasks!" << endl;
    }
}

// Function to mark a task as completed
void markAsCompleted(vector<Task>& tasks) {
    displayPendingTasks(tasks);
    if (!tasks.empty()) {
        int taskIndex;
        cout << "Enter the task number to mark as completed: ";
        cin >> taskIndex;
        if (taskIndex > 0 && taskIndex <= tasks.size()) {
            tasks[taskIndex - 1].completed = true;
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task number entered." << endl;
        }
    }
}

// Function to add a new task
void addTask(vector<Task>& tasks) {
    string description;
    cout << "Enter the task description: ";
    cin.ignore();
    getline(cin, description);
    Task newTask(description, false);
    tasks.push_back(newTask);
    cout << "Task added!" << endl;
}

// Function to save tasks to a file
void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.description << ',' << task.completed << endl;
        }
        file.close();
    } else {
        cout << "Error opening the file!" << endl;
    }
}

// Function to load tasks from a file
void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            string desc = line.substr(0, pos);
            bool status = line.substr(pos + 1) == "1" ? true : false;
            Task task(desc, status);
            tasks.push_back(task);
        }
        file.close();
    } else {
        cout << "Error opening the file!" << endl;
    }
}

int main() {
    string filename = "tasks.txt"; // File to store tasks
    vector<Task> tasks;

    // Load tasks from the file
    loadTasksFromFile(tasks, filename);

    int choice;
    bool invalidInput;
    do {
        invalidInput = false;
        cout << "\nTo-Do List Management\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. View Pending Tasks\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                markAsCompleted(tasks);
                break;
            case 3:
                displayPendingTasks(tasks);
                break;
            case 4:
                saveTasksToFile(tasks, filename);
                cout << "Tasks saved. Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                invalidInput = true; // Set flag for invalid input
                // Clear input stream
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != 4 || invalidInput);

    return 0;
}