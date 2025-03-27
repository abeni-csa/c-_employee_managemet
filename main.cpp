// rewrite everything in rust bro

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Employee
{
    int id;
    string name;
    float salary;

public:
    Employee() : id(0), name("Not Given"), salary(0.0f) {}

    Employee(int id, const string& name, float salary) : id(id), name(name), salary(salary) {}

    void display() const
    {
        cout << "\n************************************";
        cout << "\nEmployee ID: " << id;
        cout << "\nName: " << name;
        cout << "\nSalary: " << salary;
        cout << "\n************************************";
    }

    int getId() const { return id; }
    const string& getName() const { return name; }
    float getSalary() const { return salary; }

    void setId(int newId) { id = newId; }
    void setName(const string& newName) { name = newName; }
    void setSalary(float newSalary) { salary = newSalary; }
};

class Node
{
    Employee data;
    shared_ptr<Node> next;

public:
    Node(const Employee& employee) : data(employee), next(nullptr) {}

    Employee getData() const { return data; }
    shared_ptr<Node> getNext() const { return next; }

    void setData(const Employee& employee) { data = employee; }
    void setNext(shared_ptr<Node> nextNode) { next = nextNode; }
};

class Company
{
    shared_ptr<Node> head;

public:
    Company() : head(nullptr) {}

    void addEmployee(const Employee& employee)
    {
        auto newNode = make_shared<Node>(employee);
        newNode->setNext(head);
        head = newNode;
    }

    void removeEmployeeById(int id)
    {
        if (!head)
        {
            cout << "\nNo employee data available.";
            return;
        }

        if (head->getData().getId() == id)
        {
            auto nodeToDelete = head;
            head = head->getNext();
            nodeToDelete->getData().display();
            cout << "\nEmployee deleted.";
            return;
        }

        auto current = head;
        while (current->getNext() && current->getNext()->getData().getId() != id)
        {
            current = current->getNext();
        }

        if (current->getNext())
        {
            auto nodeToDelete = current->getNext();
            current->setNext(nodeToDelete->getNext());
            nodeToDelete->getData().display();
            cout << "\nEmployee deleted.";
        }
        else
        {
            cout << "\nEmployee not found.";
        }
    }

    void editEmployee(int id)
    {
        auto current = head;
        while (current)
        {
            if (current->getData().getId() == id)
            {
                Employee employee = current->getData();
                char choice;
                string newName;
                float newSalary;

                cout << "\nDo you want to change the name? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    cout << "\nEnter new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    employee.setName(newName);
                }

                cout << "\nDo you want to change the salary? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    cout << "\nEnter new salary: ";
                    cin >> newSalary;
                    employee.setSalary(newSalary);
                }

                current->setData(employee);
                return;
            }
            current = current->getNext();
        }

        cout << "\nEmployee record not found.";
    }

    void searchEmployeeById(int id) const
    {
        auto current = head;
        while (current)
        {
            if (current->getData().getId() == id)
            {
                cout << "\nEmployee found:";
                current->getData().display();
                return;
            }
            current = current->getNext();
        }
        cout << "\nEmployee not found.";
    }

    void displayAllEmployees() const
    {
        if (!head)
        {
            cout << "\nNo employee data available.";
            return;
        }

        auto current = head;
        while (current)
        {
            current->getData().display();
            current = current->getNext();
        }
    }
};

int main()
{
    Company company;
    int choice = 0;

    while (choice != 6)
    {
        cout << "\n\n*************************************";
        cout << "\n\t1. Add Employee";
        cout << "\n\t2. Display Employees";
        cout << "\n\t3. Search Employee by ID";
        cout << "\n\t4. Remove Employee by ID";
        cout << "\n\t5. Edit Employee Data";
        cout << "\n\t6. Exit";
        cout << "\n*************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name;
            float salary;
            cout << "\nEnter the ID: ";
            cin >> id;
            cout << "Enter the name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the salary: ";
            cin >> salary;
            Employee employee(id, name, salary);
            company.addEmployee(employee);
            break;
        }
        case 2:
            company.displayAllEmployees();
            break;
        case 3:
        {
            int id;
            cout << "\nEnter the ID to search: ";
            cin >> id;
            company.searchEmployeeById(id);
            break;
        }
        case 4:
        {
            int id;
            cout << "\nEnter the ID to remove: ";
            cin >> id;
            company.removeEmployeeById(id);
            break;
        }
        case 5:
        {
            int id;
            cout << "\nEnter the ID to edit: ";
            cin >> id;
            company.editEmployee(id);
            break;
        }
        case 6:
            cout << "\nExiting the program.";
            break;
        default:
            cout << "\nInvalid choice.";
            break;
        }
    }

    return 0;
}
