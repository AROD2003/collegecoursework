#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

// structure to hold course information
struct Course {
    // id of the course
    std::string courseId;  

    // title of the course                 
    std::string title;    

    // array of prerequisites                  
    std::string prerequisites[10];          

    // the amount of prereqs
    int prereqCount;                        

    // pointer to next course
    Course* next;                           

    // constructor
    Course() {
        prereqCount = 0;
        next = nullptr;
    }
};

// class to manage the linked list of courses
class CourseList {
private:
   // pointer to the first course in the list
    Course* head;

    // pointer to the last course in the list
    Course* tail;   

public:
    // constructor
    CourseList() {
        head = nullptr;
        tail = nullptr;
    }

    // destructor, cleans list
    ~CourseList() {
        Course* current = head;
        while (current != nullptr) {
            Course* nextCourse = current->next;
            delete current;
            current = nextCourse;
        }
    }

    // method to add a course to the list
    void append(Course* course) {
        if (head == nullptr) {
            head = course;
            tail = course;
        } else {
            tail->next = course;
            tail = course;
        }
    }

    // method to sort the courses alphanumerically
    void sort() {
        if (head == nullptr || head->next == nullptr) {
             // list is empty or has only one element
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Course* current = head;
            Course* prev = nullptr;

            while (current->next != nullptr) {
                if (current->courseId > current->next->courseId) {
                    // swap the nodes
                    Course* temp = current->next;
                    current->next = temp->next;
                    temp->next = current;

                    if (prev == nullptr) {
                        head = temp;
                    } else {
                        prev->next = temp;
                    }

                    swapped = true;
                    prev = temp;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);
    }

    // method to print the course list
    void printCourseList() {
        if (head == nullptr) {
            std::cout << "No courses available." << std::endl;
            return;
        }

        std::cout << "Here is a sample schedule:" << std::endl;

        Course* current = head;
        while (current != nullptr) {
            std::cout << current->courseId << ", " << current->title << std::endl;
            current = current->next;
        }
    }

    // method to print information about a specific course
    void printCourseInformation(const std::string& courseId) {
        Course* course = findCourse(courseId);
        if (course != nullptr) {
            std::cout << course->courseId << ", " << course->title << std::endl;

            if (course->prereqCount > 0) {
                std::cout << "Prerequisites: ";
                for (int i = 0; i < course->prereqCount; ++i) {
                    std::cout << course->prerequisites[i];
                    if (i < course->prereqCount - 1)
                        std::cout << ", ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "Prerequisites: None" << std::endl;
            }
        } else {
            std::cout << "Course not found." << std::endl;
        }
    }

    // method to find a course in the list
    Course* findCourse(const std::string& courseId) {
        Course* current = head;
        while (current != nullptr) {
            if (current->courseId == courseId) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // method to check if the list is empty
    bool isEmpty() {
        return head == nullptr;
    }
};

 // loads courses from a file into the provided course list.
void loadCourses(CourseList& courseList) {
    std::string filename;
    std::cout << "Enter the name of the data file: ";
    std::cin >> filename;
    std::ifstream infile(filename);

    // check if the file was opened successfully
    if (!infile.is_open()) {
        std::cout << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;

    // read the file line by line
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string item;

        Course* course = new Course();

        // get courseID
        if (!std::getline(ss, item, ',')) continue;
        std::transform(item.begin(), item.end(), item.begin(), ::toupper);
        course->courseId = item;

        // get title
        if (!std::getline(ss, item, ',')) continue;
        course->title = item;

        // get prerequisites
        while (std::getline(ss, item, ',')) {
            std::transform(item.begin(), item.end(), item.begin(), ::toupper);
            course->prerequisites[course->prereqCount++] = item;
        }

        // add course to the list
        courseList.append(course);
    }

    infile.close();
    std::cout << "Courses loaded successfully." << std::endl;
}

// method to handle user input and run the program
int main() {
    CourseList courseList;
    int choice = 0;

    std::cout << "Welcome to the course planner." << std::endl;

    // loop until the user chooses to exit
    while (choice != 9) {
        std::cout << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";

        std::cin >> choice;

        // handle invalid input
        if (std::cin.fail()) {
            // clear the error flag
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            
            // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                loadCourses(courseList);
                break;
            case 2:
                if (courseList.isEmpty()) {
                    std::cout << "No courses loaded. Please load the data structure first." << std::endl;
                } else {
                    courseList.sort();
                    courseList.printCourseList();
                }
                break;
            case 3:
                if (courseList.isEmpty()) {
                    std::cout << "No courses loaded. Please load the data structure first." << std::endl;
                } else {
                    std::string courseId;
                    std::cout << "What course do you want to know about? ";
                    std::cin >> courseId;
                    std::transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
                    courseList.printCourseInformation(courseId);
                }
                break;
            case 9:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
        }
    }

    return 0;
}
