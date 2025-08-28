#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Task class
class Task {
public:
    string description;
    string category;
    bool completed;

    Task(string desc, string cat = "General", bool done = false) {
        description = desc;
        category = cat;
        completed = done;
    }
};

// Task Manager class
class TaskManager {
private:
    vector<Task> tasks;

public:
    // Add a task
    void addTask(string desc, string category = "General") {
        tasks.push_back(Task(desc, category));
        cout << "Task added successfully!\n";
    }

    // Show tasks
    void viewTasks(bool showCompleted = false) {
        bool found = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].completed == showCompleted) {
                cout << i + 1 << ". [" 
                     << (tasks[i].completed ? "Done" : "Pending") << "] "
                     << tasks[i].description 
                     << " (Category: " << tasks[i].category << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No " << (showCompleted ? "completed" : "pending") << " tasks.\n";
        }
    }

    // Mark task completed
    void markCompleted(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }
        tasks[index - 1].completed = true;
        cout << "Task marked as completed!\n";
    }

    // Save tasks to file
    void saveToFile(string filename) {
        ofstream file(filename);
        for (Task &t : tasks) {
            file << t.description << ";" 
                 << t.category << ";" 
                 << t.completed << "\n";
        }
        file.close();
        cout << "Tasks saved to file.\n";
    }

    // Load tasks from file
    void loadFromFile(string filename) {
        ifstream file(filename);
        tasks.clear();
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(';');
            size_t pos2 = line.find(';', pos1 + 1);
            string desc = line.substr(0, pos1);
            string cat = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool done = (line.substr(pos2 + 1) == "1");
            tasks.push_back(Task(desc, cat, done));
        }
        file.close();
    }
};

// Main Program
int main() {
    TaskManager manager;
    int choice;
    string desc, category;
    int index;

    manager.loadFromFile("tasks.txt");

    do {
        cout << "\n--- TASK MANAGER ---\n";
        cout << "1. ➕ Add Task\n";
        cout << "2. 📋 View Pending Tasks\n";
        cout << "3. ✅ View Completed Tasks\n";
        cout << "4. ✔️ Mark Task as Completed\n";
        cout << "5. 💾 Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter task description: ";
            getline(cin, desc);
            cout << "Enter category (optional, press enter for 'General'): ";
            getline(cin, category);
            if (category.empty()) category = "General";
            manager.addTask(desc, category);
            break;
        case 2:
            manager.viewTasks(false);
            break;
        case 3:
            manager.viewTasks(true);
            break;
        case 4:
            cout << "Enter task number: ";
            cin >> index;
            manager.markCompleted(index);
            break;
        case 5:
            manager.saveToFile("tasks.txt");
            cout << "Exiting... Bye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
