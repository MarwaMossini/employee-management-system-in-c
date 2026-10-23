#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>  // Required for atof()

// Define a structure for employee
typedef struct
{
    string name;
    string id;
    int salary;
    string department;
    string qualification;
    string work_experience;
    string rank;
} Employee;

// Function to display the menu
void displayMenu(void)
{
    printf("\nWhich of these options do you want:\n");
    printf("1. Add Employee Record\n");
    printf("2. Delete Employee Record\n");
    printf("3. Search Employee by ID\n");
    printf("4. Search Employee by Name\n");
    printf("5. Update Employee Salary\n");
    printf("6. List All Employees in a Department\n");
    printf("7. Promote Employee\n");
    printf("8. Count Total Employees\n");
    printf("9. Show Updated List of Employees\n");
}

// Function to assign department based on qualification
string assignDepartment(string qualification)
{
    if (strstr(qualification, "English") != NULL)
    {
        return "English";
    }
    else if (strstr(qualification, "Persian") != NULL)
    {
        return "Persian";
    }
    else if (strstr(qualification, "French") != NULL)
    {
        return "French";
    }
    else if (strstr(qualification, "Deutsch") != NULL)
    {
        return "Deutsch";
    }
    else if (strstr(qualification, "Portuguese") != NULL)
    {
        return "Portuguese";
    }
    return "Unknown";
}

// Function to assign rank based on work experience
string assignRank(float work_exp)
{
    if (work_exp > 4)
    {
        return "Principal";
    }
    else if (work_exp >= 2 && work_exp <= 4)
    {
        return "Lead Teacher";
    }
    else if (work_exp >= 1 && work_exp < 2)
    {
        return "Entry Level";
    }
    return "Unknown";
}

// Function to promote employee based on experience
void promoteEmployee(Employee *emp)
{
    float work_exp = atof(emp->work_experience); // Converting work experience to float
    emp->rank = assignRank(work_exp); // Update the rank based on work experience

    if (strcmp(emp->rank, "Principal") == 0)
    {
        emp->salary = 400;  // Promote to Principal
        printf("%s is promoted to Principal\n", emp->name);
    }
    else if (strcmp(emp->rank, "Lead Teacher") == 0)
    {
        emp->salary = 350;  // Promote to Lead Teacher
        printf("%s is promoted to Lead Teacher\n", emp->name);
    }
    else if (strcmp(emp->rank, "Entry Level") == 0)
    {
        emp->salary = 300;  // Entry Level remains the same
        printf("%s is promoted to Entry Level\n", emp->name);
    }
}

// Function to display the updated list of employees in a two-line format
void displayUpdatedList(Employee employees[], int n)
{
    printf("\nUpdated List of Employees:\n");
    for (int i = 0; i < n; i++)
    {
        // First line: Basic info
        printf("%d. %s, ID: %s\n", i + 1, employees[i].name, employees[i].id);

        // Second line: Detailed info
        printf("   Department: %s, Qualification: %s, Work Experience: %s, Rank: %s, Salary: %d$\n",
               employees[i].department, employees[i].qualification, employees[i].work_experience,
               employees[i].rank, employees[i].salary);
    }
}

// Main function
int main(void)
{
    int n = 5; // Initial employee count
    Employee employees[100]; // Array to store employees
    employees[0] = (Employee){"Marwa Mossini", "222200", 300, "English", "BA in English language", "1.2", "Entry Level"};
    employees[1] = (Employee){"Sara Sadat", "229567", 300, "Persian", "MA in Persian Language", "4", "Lead Teacher"};
    employees[2] = (Employee){"Hawa Azimi", "203345", 300, "Portuguese", "BA in Portuguese language", "0.25", "Entry Level"};
    employees[3] = (Employee){"Ali Fani", "223244", 400, "French", "MA in French language", "2.4", "Lead Teacher"};
    employees[4] = (Employee){"Mustafa Ahmadi", "23789", 400, "German", "MA in German language", "5", "Principal"};

    while (true)
    {
        displayMenu();
        int choice = get_int("Choose an option: ");

        if (choice == 1) // Add Employee Record
        {
            string name = get_string("Enter Name: ");
            string id = get_string("Enter ID: ");
            string qualification = get_string("Qualification (BA/MA/PHD in X Language): ");
            string work_experience = get_string("Work Experience (in years): ");

            employees[n].name = name;
            employees[n].id = id;
            employees[n].qualification = qualification;
            employees[n].work_experience = work_experience;
            employees[n].department = assignDepartment(qualification);
            employees[n].rank = assignRank(atof(work_experience)); // Assign rank based on work experience
            employees[n].salary = (strcmp(employees[n].rank, "Principal") == 0) ? 400 : (strcmp(employees[n].rank, "Lead Teacher") == 0) ? 350 : 300;

            printf("Employee added: %s, ID: %s, Department: %s, Rank: %s, Salary: %d$\n",
                    employees[n].name, employees[n].id, employees[n].department, employees[n].rank, employees[n].salary);
            displayUpdatedList(employees, ++n);
            break;
        }

        else if (choice == 2) // Delete Employee Record
        {
            string id = get_string("Enter Employee ID to delete: ");
            bool found = false; // check if it matches
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].id, id) == 0)
                {
                    for (int j = i; j < n - 1; j++) // shift the rest to the left
                    {
                        employees[j] = employees[j + 1];
                    }
                    n--;
                    printf("Employee with ID %s deleted.\n", id);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("Employee with ID %s not found in the list.\n", id);
            }
            displayUpdatedList(employees, n);
            break;
        }

        else if (choice == 3) // Search Employee by ID
        {
            string id = get_string("Enter Employee ID to search: ");
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].id, id) == 0)
                {
                    printf("Employee Found: %s, ID: %s, Department: %s, Qualification: %s, Work Experience: %s, Rank: %s, Salary: %d$\n",
                            employees[i].name, employees[i].id, employees[i].department, employees[i].qualification,
                            employees[i].work_experience, employees[i].rank, employees[i].salary);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("Employee with ID %s not found in the list.\n", id);
            }
            break;
        }

        else if (choice == 4) // Search Employee by Name
        {
            string name = get_string("Enter Employee Name to search: ");
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].name, name) == 0)
                {
                    printf("Employee Found: %s, ID: %s, Department: %s, Qualification: %s, Work Experience: %s, Rank: %s, Salary: %d$\n",
                            employees[i].name, employees[i].id, employees[i].department, employees[i].qualification,
                            employees[i].work_experience, employees[i].rank, employees[i].salary);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("Employee with Name %s not found in the list.\n", name);
            }
            break;
        }

        else if (choice == 5) // Update Employee Salary
        {
            string id = get_string("Enter Employee ID to update salary: ");
            int hoursWorked = get_int("How many extra hours have you worked this month? ");
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].id, id) == 0)
                {
                    employees[i].salary += hoursWorked * 30;  // Increase salary based on extra hours worked
                    printf("The updated salary for %s is: %d$\n", employees[i].name, employees[i].salary);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("Employee with ID %s not found in the list.\n", id);
            }
            displayUpdatedList(employees, n);
            break;
        }

        else if (choice == 6) // List All Employees in a Department
        {
            string department = get_string("Enter Department to list employees: ");
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].department, department) == 0)
                {
                    printf("%s, ID: %s, Qualification: %s, Work Experience: %s, Rank: %s, Salary: %d$\n",
                            employees[i].name, employees[i].id, employees[i].qualification,
                            employees[i].work_experience, employees[i].rank, employees[i].salary);
                    found = true;
                }
            }
            if (!found)
            {
                printf("No employees found in the %s department.\n", department);
            }
            break;
        }

        else if (choice == 7) // Promote Employee
        {
            string name = get_string("Enter the name of the employee to promote: ");
            bool found = false;  // We haven't found anyone yet

            for (int i = 0; i < n; i++)
            {
                if (strcmp(employees[i].name, name) == 0)
                {
                    string work_exp = get_string("Enter the updated work experience in years: ");
                    employees[i].work_experience = work_exp; // Update work experience
                    promoteEmployee(&employees[i]); // Promote employee based on updated experience
                    found = true; if (strcmp(employees[i].name, name) == 0) {
                        found = true;  // YES! We found a match
                        // Update experience and promote
                        break;
                    }

                    break;
                }
            }
            if (!found)
            {
                printf("Employee with Name %s not found in the list.\n", name);
            }
            displayUpdatedList(employees, n);
            break;
        }

        else if (choice == 8) // Count Total Employees
        {
            printf("Total Employees: %d\n", n);
            break;
        }

        else if (choice == 9) // Show Updated List of Employees
        {
            displayUpdatedList(employees, n);
            break;
        }
    }

    return 0;
}
