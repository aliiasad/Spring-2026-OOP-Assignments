# include <iostream>

class Project;
class Department;

class Name {
    private:
        std :: string f_name;
        std :: string l_name;
    public:
        // constructor
        Name(std :: string, std :: string);

        // helper
        void displayName();
};

Name :: Name(std :: string f_name, std :: string l_name)    {
    this->f_name = f_name;
    this->l_name = l_name;
}

void Name :: displayName()  {
    std :: cout << "Name: " << f_name <<  " " << l_name << std :: endl;
    return;
}

class Address   {
    private:
        int houseNo;
        char block;
        int streetNo;
        std :: string city;
    public:
        // constructor
        Address(int, char, int , std :: string);

        // helper
        void displayAddress();
};

Address :: Address(int houseNo, char block, int streetNo, std :: string city)  {
    this->houseNo = houseNo;
    this->block = block;
    this->streetNo = streetNo;
    this->city = city;
}

void Address :: displayAddress() {
    std :: cout << "Address: " << houseNo << "-" << block << " streetNo." <<
    streetNo << ", " << city << std :: endl;
    return;
}

class Employee  {
    private:
        int ID;
        Name name;  // composition by value
        Address permanantAddr;  // coposition by value
        bool assignedToDept;
        Project* project[3];    // Aggregation
        int projectCount;
        Department* Dept; // Aggregation
    public:
        Employee(int, std :: string, std :: string, int, char, int, std :: string);
        int getID();
        void displayEmployeeInfo();
        bool AddProject(Project* proj);
        bool RemoveProject(int projectID);
        void displayAllProjects();
        void SetAssignedToDept(bool value);
        bool GetAssignedToDept();
        void SetDept(Department* dept);
        void displayDept();
};

// since no default constructors for Name and Address, member initializer list is used :-)
Employee :: Employee(int ID, std :: string f_name, std :: string l_name,
    int houseNo, char block, int streetNo, std :: string city) : 
    name(f_name, l_name), permanantAddr(houseNo, block, streetNo, city)    {
        
        this->ID = ID;

        this->projectCount = 0;

        this->assignedToDept = 0;

        for (int i = 0; i < 3; i++) {
            project[i] = nullptr;
        }

        Dept = nullptr;
}

int Employee :: getID() {
    return ID;
}

void Employee :: displayEmployeeInfo()  {
    name.displayName();
    permanantAddr.displayAddress();
    return;
}

bool Employee :: AddProject(Project* project)  {
    if (projectCount < 3) {
        this->project[projectCount++] = project;
        return true;
    }
    return false;
}

// moved two function definitions 

void Employee :: SetAssignedToDept(bool value)  {
    this->assignedToDept = value;
    return;
}

bool Employee :: GetAssignedToDept()    {
    return this->assignedToDept;
}

void Employee :: SetDept(Department* dept)    {
    this->Dept = dept;
    return;
}

// moved one function

class Project {
        int ID;
        std :: string projectDescription;
        int employeesWorkingOn;
        Employee* employee[10]; // aggregation
    public:
        // constructor
        Project(int, std :: string);

        int getID();
        void displayProjectInfo();
        void IncEmployeesWorkingOn();
        void DecEmployeeWorkingOn();
        bool AddEmployee(Employee*);
        bool RemoveEmployee(Employee*);
        void DisplayAllEmployees();
};

Project :: Project(int ID, std :: string projectDescription)    {
    this->ID = ID;
    this->projectDescription = projectDescription;
    this->employeesWorkingOn = 0;
    for (int i = 0; i < 10; i++)
        employee[i] = nullptr;
}

int Project :: getID()  {
    return ID;
}

void Project :: displayProjectInfo()   {
    std :: cout << "Project ID: " << ID << std :: endl;
    std :: cout << "Project Description: " << projectDescription << std :: endl;
    std :: cout << "Employees Working: " << employeesWorkingOn << std :: endl;
    return;
}

void Project :: IncEmployeesWorkingOn() {
        if (employeesWorkingOn < 10) employeesWorkingOn++;
        return;
    }
    
void Project :: DecEmployeeWorkingOn() {
    if (employeesWorkingOn > 0) employeesWorkingOn--;
    return;
}

bool Project :: AddEmployee(Employee* employee)  {
    if (employeesWorkingOn < 10) {
        this->employee[employeesWorkingOn++] = employee;
        return true;
    }
    return false;
}

bool Project :: RemoveEmployee(Employee* employee)  {
    for (int i = 0; i < employeesWorkingOn; i++)    {
        if (this->employee[i] == employee)  {
            for (int j = i; j < employeesWorkingOn - 1; j++)    {
                this->employee[j] = this->employee[j + 1];
            }
            this->employee[employeesWorkingOn - 1] = nullptr;
            employeesWorkingOn--;
            return true;
        }
    }
    return false;
}

void Project :: DisplayAllEmployees()   {
    for (int i = 0; i < employeesWorkingOn; i++)    {
        employee[i]->displayEmployeeInfo();
        std :: cout << std :: endl;
    }
    return;
}

class Department {
    int ID;
    std :: string name;
    Employee* employee[50];   // aggregation
    int employeeCount;
public:
    Department(int, std :: string);
    int getID();
    void displayDeptInfo();
    bool AddEmployee(Employee* emp);
    bool RemoveEmployee(int employeeID);
    void DisplayAllEmployees();
};

Department :: Department(int ID, std :: string name)    : ID(ID), name(name), employeeCount(0) {
    for (int i = 0; i < 50; i++) 
        employee[i] = nullptr;
}
 
int Department :: getID() { 
    return ID; 
}
 
    // Display department info
void Department :: displayDeptInfo() {
    std :: cout << "Department ID: " << ID << std :: endl << "Name: " << name << std :: endl << "Employees: " << employeeCount << std :: endl;
    }
 
    // Add employee to department (one-dept rule enforced at Company level)
bool Department :: AddEmployee(Employee* emp) {
    if (emp == nullptr) return false;
    if (employeeCount >= 50) {
        std :: cout << "Department " << name << " is full (max 50 employees)." << std :: endl;
        return false;
    }
    for (int i = 0; i < employeeCount; i++) {
        if (employee[i] == emp) return false;   // already in dept
    }
    employee[employeeCount++] = emp;
    return true;
    }
 
    // Remove employee by ID
bool Department :: RemoveEmployee(int employeeID)   {   // defined after Employee
    for (int i = 0; i < employeeCount; i++) {
        if (employee[i]->getID() == employeeID) {
            for (int j = i; j < employeeCount - 1; j++) {
                employee[j] = employee[j + 1];
            }
            employee[--employeeCount] = nullptr;
            return true;
        }
    }
    return false;
}   
 
    // Display all employees in this department
void Department :: DisplayAllEmployees()  {
        if (employeeCount == 0) {
            std :: cout << "Department " << name << " has no employees." << std :: endl;
            return;
        }
        std :: cout << "Employees in department " << name << ":" << std :: endl;
        for (int i = 0; i < employeeCount; i++) {
            std :: cout << "  Employee ID: " << employee[i]->getID() << std :: endl;
        }
}

// added two definitions
bool Employee :: RemoveProject(int ID)  {
    for (int i = 0; i < projectCount; i++)    {
        if (project[i]->getID() == ID)  {
            for (int j = i; j < projectCount - 1; j++)    {
                project[j] = project[j + 1];
            }
            project[projectCount - 1] = nullptr;
            projectCount--;
            return true;
        }
    }
    return false;
}

void Employee :: displayAllProjects()   {
    for (int i = 0; i < projectCount; i++)  {
        project[i]->displayProjectInfo();
    }
    return;
}

// added third function

void Employee :: displayDept()  {
    if (Dept != nullptr)
    Dept->displayDeptInfo();
    return;
}

class Company {
    static int count;
    Employee* employees[100]; int ecount;
    Project* projects[20];   int pcount;
    Department* departments[4]; int dcount;

    Company();

    // Private helpers
    Employee* findEmployee(int id);
    Project* findProject(int id);
    Department* findDepartment(int id);

public:
    static Company* construct();

    void createDepartment(int, std :: string);
    void createProject(int, std :: string);
    void createEmployee(int, std :: string, std :: string,
                        int, char, int, std :: string);

    void displayDeptID(int);
    void displayProjID(int);
    void displayEmpID(int);
    void displayEmpDept(int);

    bool addEmpInDep(int, int);
    bool addEmpInProj(int, int);
    bool displayAllProj(int);
    bool displayAllEmpInDep(int);
    bool displayAllEmpInProj(int);
    bool displayDep(int);
    bool removeEmpFromDep(int, int);
    bool removeEmpFromProj(int, int);

    ~Company();
};

// static member definition
int Company::count = 0;

// pvt constructor
Company::Company() : ecount(0), pcount(0), dcount(0) {
    for (int i = 0; i < 100; i++) employees[i] = nullptr;
    for (int i = 0; i < 20;  i++) projects[i] = nullptr;
    for (int i = 0; i < 4;   i++) departments[i] = nullptr;
    count++;
}

// pvt helpers
Employee* Company :: findEmployee(int id) {
    for (int i = 0; i < ecount; i++)
        if (employees[i]->getID() == id) return employees[i];
    return nullptr;
}

Project* Company :: findProject(int id) {
    for (int i = 0; i < pcount; i++)
        if (projects[i]->getID() == id) return projects[i];
    return nullptr;
}

Department* Company :: findDepartment(int id) {
    for (int i = 0; i < dcount; i++)
        if (departments[i]->getID() == id) return departments[i];
    return nullptr;
}

// singleton validation
Company* Company :: construct() {
    if (count >= 1) {
        std :: cout << "Company already exists. Only one instance allowed." << std :: endl;
        return nullptr;
    }
    return new Company();
}

// method functios
void Company :: createDepartment(int ID, std :: string name) {
    if (dcount >= 4) { 
        std :: cout << "Max 4 departments reached." << std :: endl; 
        return; 
    }
    departments[dcount++] = new Department(ID, name);
}

void Company :: createProject(int ID, std :: string description) {
    if (pcount >= 20) { 
        std :: cout << "Max 20 projects reached." << std :: endl; 
        return; 
    }
    projects[pcount++] = new Project(ID, description);
}

void Company :: createEmployee(int ID, std::string fn, std::string ln,
                              int HN, char B, int SN, std::string city) {
    if (ecount >= 100) { 
        std :: cout << "Max 100 employees reached." << std :: endl; 
        return; 
    }
    employees[ecount++] = new Employee(ID, fn, ln, HN, B, SN, city);
}

// display using id
void Company :: displayDeptID(int id) {
    Department* d = findDepartment(id);
    if (d) d->displayDeptInfo();
    else   std :: cout << "Department " << id << " not found." << std :: endl;
}

void Company :: displayProjID(int id) {
    Project* p = findProject(id);
    if (p) p->displayProjectInfo();
    else   std :: cout << "Project " << id << " not found." << std :: endl;
}

void Company :: displayEmpID(int id) {
    Employee* e = findEmployee(id);
    if (e) e->displayEmployeeInfo();
    else   std :: cout << "Employee " << id << " not found." << std :: endl;
}

// assign emo to dept
bool Company::addEmpInDep(int idE, int idD) {
    Employee* e = findEmployee(idE);
    Department* d = findDepartment(idD);
    if (!e || !d) {
        std :: cout << "Employee or Department not found." << std :: endl;
        return false;
    }
    if (e->GetAssignedToDept()) {
        std :: cout << "Employee " << idE << " is already assigned to a department." << std :: endl;
        return false;
    }
    if (d->AddEmployee(e)) {
        e->SetDept(d);
        e->SetAssignedToDept(true);
        return true;
    }
    return false;
}

// assign emp to proj
bool Company :: addEmpInProj(int idE, int idP) {
    Employee* e = findEmployee(idE);
    Project* p = findProject(idP);
    if (!e || !p) {
        std :: cout << "Employee or Project not found." << std :: endl;
        return false;
    }
    if (!e->AddProject(p)) return false;
    if (!p->AddEmployee(e)) {
        e->RemoveProject(idP);
        return false;
    }
    return true;
}

// display all projs for emp 
bool Company :: displayAllProj(int id) {
    Employee* e = findEmployee(id);
    if (!e) {
         std :: cout << "Employee " << id << " not found." << std :: endl; 
         return false; 
        }
    e->displayAllProjects();
    return true;
}

// display all emps in dept
bool Company :: displayAllEmpInDep(int id) {
    Department* d = findDepartment(id);
    if (!d) { 
        std :: cout << "Department " << id << " not found." << std :: endl; 
        return false; 
    }
    d->DisplayAllEmployees();
    return true;
}

// dislay all emps in a proj
bool Company :: displayAllEmpInProj(int id) {
    Project* p = findProject(id);
    if (!p) { 
        std :: cout << "Project " << id << " not found." << std :: endl; 
        return false; 
    }
    p->DisplayAllEmployees();
    return true;
}

// display dept info
bool Company :: displayDep(int id) {
    Department* d = findDepartment(id);
    if (!d) { 
        std :: cout << "Department " << id << " not found." << std :: endl; 
        return false; }
    d->displayDeptInfo();
    return true;
}

void Company :: displayEmpDept(int id) {
    Employee* e = findEmployee(id);
    if (!e) { 
        std :: cout << "Employee " << id << " not found." << std :: endl; 
        return; 
    }
    e->displayDept();
}

// remove emp from dept
bool Company :: removeEmpFromDep(int idE, int idD) {
    Employee* e = findEmployee(idE);
    Department* d = findDepartment(idD);
    if (!e || !d) { 
        std :: cout << "Employee or Department not found." << std :: endl; 
        return false; 
    }
    if (d->RemoveEmployee(idE)) {
        e->SetDept(nullptr);
        e->SetAssignedToDept(false);
        return true;
    }
    std :: cout << "Employee " << idE << " not in department " << idD << "." << std :: endl;
    return false;
}

// remove emp from proj
bool Company :: removeEmpFromProj(int idE, int idP) {
    Employee* e = findEmployee(idE);
    Project* p = findProject(idP);
    if (!e || !p) { 
        std :: cout << "Employee or Project not found." << std :: endl; 
        return false; }
    bool removedFromEmp = e->RemoveProject(idP);
    bool removedFromProj = p->RemoveEmployee(e);
    return removedFromEmp && removedFromProj;
}

// destructor
Company :: ~Company() {
    for (int i = 0; i < ecount; i++) { 
        delete employees[i];   
        employees[i] = nullptr; 
    }
    for (int i = 0; i < pcount; i++) { 
        delete projects[i];    
        projects[i] = nullptr; 
    }
    for (int i = 0; i < dcount; i++) {
        delete departments[i]; 
        departments[i] = nullptr; 
    }
    count--;
}

int main() {
    Company* company = Company::construct();
    if (!company) return 1;

    int choice;

    while (true) {
        std :: cout << "\n===== Company Management System =====" << std :: endl;
        std :: cout << "0.  Exit" << std :: endl;
        std :: cout << "1.  Create Department" << std :: endl;
        std :: cout << "2.  Create Employee" << std :: endl;
        std :: cout << "3.  Create Project" << std :: endl;
        std :: cout << "4.  Display Department by ID" << std :: endl;
        std :: cout << "5.  Display Employee by ID" << std :: endl;
        std :: cout << "6.  Display Project by ID" << std :: endl;
        std :: cout << "7.  Add Employee to Department" << std :: endl;
        std :: cout << "8.  Add Employee to Project" << std :: endl;
        std :: cout << "9.  Display all Projects of an Employee" << std :: endl;
        std :: cout << "10. Display all Employees in a Department" << std :: endl;
        std :: cout << "11. Remove Employee from Department" << std :: endl;
        std :: cout << "12. Remove Employee from Project" << std :: endl;
        std :: cout << "13. Display all Employees in a Project" << std :: endl;
        std :: cout << "14. Display Department of an Employee" << std :: endl;
        std :: cout << "Enter choice: ";
        std :: cin >> choice;

        if (choice == 0) {
            delete company;
            return 0;
        }
        else if (choice == 1) {
            int id;
            std::string name;
            std :: cout << "Enter Department ID: ";
            std :: cin >> id;
            std :: cout << "Enter Department Name: ";
            std :: cin >> name;
            company->createDepartment(id, name);
        }
        else if (choice == 2) {
            int id, hn, sn;
            std::string fn, ln, city;
            char block;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> id;
            std :: cout << "Enter First Name: ";
            std :: cin >> fn;
            std :: cout << "Enter Last Name: ";
            std :: cin >> ln;
            std :: cout << "Enter House Number: ";
            std :: cin >> hn;
            std :: cout << "Enter Block (single char): ";
            std :: cin >> block;
            std :: cout << "Enter Street Number: ";
            std :: cin >> sn;
            std :: cout << "Enter City: ";
            std :: cin >> city;
            company->createEmployee(id, fn, ln, hn, block, sn, city);
        }
        else if (choice == 3) {
            int id;
            std::string desc;
            std :: cout << "Enter Project ID: ";
            std :: cin >> id;
            std :: cout << "Enter Project Description: ";
            std :: cin >> desc;
            company->createProject(id, desc);
        }
        else if (choice == 4) {
            int id;
            std :: cout << "Enter Department ID: ";
            std :: cin >> id;
            company->displayDeptID(id);
        }
        else if (choice == 5) {
            int id;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> id;
            company->displayEmpID(id);
        }
        else if (choice == 6) {
            int id;
            std :: cout << "Enter Project ID: ";
            std :: cin >> id;
            company->displayProjID(id);
        }
        else if (choice == 7) {
            int idE, idD;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> idE;
            std :: cout << "Enter Department ID: ";
            std :: cin >> idD;
            company->addEmpInDep(idE, idD);
        }
        else if (choice == 8) {
            int idE, idP;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> idE;
            std :: cout << "Enter Project ID: ";
            std :: cin >> idP;
            company->addEmpInProj(idE, idP);
        }
        else if (choice == 9) {
            int id;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> id;
            company->displayAllProj(id);
        }
        else if (choice == 10) {
            int id;
            std :: cout << "Enter Department ID: ";
            std :: cin >> id;
            company->displayAllEmpInDep(id);
        }
        else if (choice == 11) {
            int idE, idD;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> idE;
            std :: cout << "Enter Department ID: ";
            std :: cin >> idD;
            company->removeEmpFromDep(idE, idD);
        }
        else if (choice == 12) {
            int idE, idP;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> idE;
            std :: cout << "Enter Project ID: ";
            std :: cin >> idP;
            company->removeEmpFromProj(idE, idP);
        }
        else if (choice == 13) {
            int id;
            std :: cout << "Enter Project ID: ";
            std :: cin >> id;
            company->displayAllEmpInProj(id);
        }
        else if (choice == 14) {
            int id;
            std :: cout << "Enter Employee ID: ";
            std :: cin >> id;
            company->displayEmpDept(id);
        }
        else {
            std :: cout << "Invalid option. Please try again." << std :: endl;
        }
    }

    delete company;
    return 0;
}