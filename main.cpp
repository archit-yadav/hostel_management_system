#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

MYSQL* db_connect();

MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

void admin();
void add_employee();
void delete_employee();
void edit_employee();
void show_all_employees();
void show_employee_by_id();

void  employee();
void add_student();
void delete_student();
void edit_student();
void show_all_student();
void show_student_by_id();

bool check_exist_employee(int id);

bool check_exist_student(int id);

int main() {
    string id="";
    string password="";

    conn=db_connect();


    int ch;
    while (true) {
        cout << "Welcome to Hostel Management System" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Select your choice:\n 1. Admin \n 2. Employee \n 3. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        if (ch == 3) {
            cout << "Exiting the system...\n\n" << endl;
            break;
        }

        switch (ch) {
            case 1:
                system("cls");
                cout << "Admin selected.\n" << endl;
                cout<<"Enter login id\n";
                cin>>id;
                cout<<"Enter Password\n";
                cin>>password;


                if(id=="admin"&&password=="admin@123"){
                    cout<<"Access granted";
                    admin();
                }
                else{
                    cout << "Wrong id & password. Exiting the system...\n\n" << endl;
                    return 0;
                }
                break;

            case 2:
                system("cls");
                cout << "Employee selected.\n" << endl;
                cout<<"Enter login id\n";
                cin>>id;
                cout<<"Enter Password\n";
                cin>>password;

                if(id=="emp"&&password=="emp@123"){
                    cout<<"Access granted\n\n";
                    employee();
                }
                else{
                    cout << "Wrong id & password. Exiting the system...\n\n" << endl;
                    return 0;
                }
                break;


            default:
                cout << "Invalid choice. Please try again. loop\n\n" << endl;
                break;
        }
    }


}



void admin(){

    int ach;
    system("cls");

    while(true){
        cout<<"Admin Panel"<<endl<<endl;
        cout<<"-------------------------------"<<endl;
        cout << "Select your choice:\n 1. Add new employee \n 2. Remove Employee \n 3. Edit Employee details\n 4. Show all Employee details \n 5. Retrieve details via Employee id\n 6. Add new student \n 7. Terminate student \n 8. Edit student details\n 9. Show all students details \n 10. Retrieve details via student id\n 11. Return to previous menu\n";
        cout << "Enter your choice: ";
        cin >> ach;

        if (ach == 11) {
            system("cls");
            break;
        }

        switch (ach) {
            case 1:
                system("cls");
                cout<<"Add new employee\n\n ";
                add_employee();
                break;

            case 2:
                system("cls");
                cout<<"Delete an employee\n\n ";
                delete_employee();
                break;

            case 3:
                system("cls");
                cout<<"Edit details of an employee\n\n";
                edit_employee();
                break;

            case 4:
                system("cls");
                cout<<"Show all employees\n\n";
                show_all_employees();
                break;

            case 5:
                system("cls");
                cout<<"Retrieve employee details by id\n\n";
                show_employee_by_id();
                break;

            case 6:
                system("cls");
                cout<<"Adding a new student\n\n"<<endl;
                add_student();
                break;

            case 7:
                system("cls");
                cout<<"Delete a student\n\n";
                delete_student();
                break;

            case 8:
                system("cls");
                cout<<"Edit student details\n\n";
                edit_student();
                break;

            case 9:
                system("cls");
                cout<<"Show all student details\n\n";
                show_all_student();
                break;

            case 10:
                system("cls");
                cout<<"Retrieve student details by id \n\n";
                show_student_by_id();
                break;


            default:
                cout << "Invalid choice. Please try again.\n\n" << endl;
                break;
        }


    }

}

void add_employee(){


        int emp_id;
        string name;
        string designation;
        long long contact_no;
        string address;


        cout << "Enter the details of the employee to add:\n " << endl;
        cout << "Enter employee id:";
        cin >> emp_id;
        cin.ignore();  // Clear newline character from the buffer

        cout << "Enter employee name: ";
        getline(cin, name);

        cout << "Enter designation of employee: ";
        getline(cin, designation);

        cout << "Enter employee contact number: ";
        cin >> contact_no;
        cin.ignore();  // Clear newline character from the buffer

        cout << "Enter address of employee: ";
        getline(cin, address);

        int qstate = 0;

        stringstream insert_query_ss;
        insert_query_ss << "INSERT INTO emp(emp_id, name, designation, contact, address) VALUES("<< emp_id << ", '" << name << "', '" << designation << "', "<< contact_no << ", '" << address << "');";
        string insert_query = insert_query_ss.str();
        const char* insert_q = insert_query.c_str();

        qstate = mysql_query(conn, insert_q);

        if (qstate == 0) {
            cout << "Record inserted successfully." << endl;
        } else {
            cout << "Insert failed: " << mysql_error(conn) << endl;
        }

  }

void delete_employee() {
    int emp_id;
    cout << "Enter employee ID to delete: ";
    cin.ignore();
    cin >> emp_id;

    if(!check_exist_employee(emp_id)){
        cout << "Employee doesn't exist ";

    }else{


        stringstream ss;
        ss << "DELETE FROM emp WHERE emp_id = " << emp_id << ";";
        string query = ss.str();
        if (mysql_query(conn, query.c_str())) {
            cout << "Error deleting employee: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Employee deleted successfully." << endl;
        }
    }
}

void edit_employee() {
    int emp_id;

    cout << "Enter employee ID to edit: ";
    cin >> emp_id;
    if(!check_exist_employee(emp_id)){
        cout << "Employee doesn't exist" << endl;
    }else{

    string name, address,designation;
    cout << "Enter new name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);

    long long contact;
    cout << "Enter new contact: ";
    cin >> contact;

    cout << "Enter new address: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, address);

    cout << "Enter the designation: ";
    getline(cin,designation);

    stringstream ss;
    ss << "UPDATE emp SET name = '" << name << "', contact = '" << contact << "', address = '" << address << "',designation = '"<<designation<<"' WHERE emp_id = " << emp_id << ";";
    string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        cout << "Error updating employee: " << mysql_error(conn) << endl;
    } else {
        cout << "Employee updated successfully." << endl;
    }
    }
}

void show_all_employees() {

    cin.ignore();
    if (mysql_query(conn, "SELECT * FROM emp")) {
        cout << "Error fetching employees: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    int num_fields = mysql_num_fields(res);

    cout<<"\n\nemp_id | name | designation | contact | address\n";
    cout<<"~~~~~~~~~~~~~~~~~~\n\n";

    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            cout << row[i] << " | ";
        }

        cout << endl<<endl;
    }
    cout<<"~~~~~~~~~~~~~~~~~~~\n\n\n\n";
}

void show_employee_by_id() {

    int emp_id;
    cout << "Enter employee ID to retrieve: ";
    cin >> emp_id;

    stringstream ss;
    ss << "SELECT * FROM emp WHERE emp_id = " << emp_id << ";";

    string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        cout << "Error retrieving employee: " << mysql_error(conn) << endl;
        return;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    cout<<"\n\nemp_id | name | designation | contact | address\n";
    cout<<"~~~~~~~~~~~~~~~~~~\n\n";

    if (row) {
        for (int i = 0; i < mysql_num_fields(res); i++) {
            cout << row[i] << " | ";
        }
        cout << endl;
    } else {
        cout << "Employee not found." << endl;
    }

    cout<<"~~~~~~~~~~~~~~~~~~\n\n";

}

void employee(){

    int ech;
    system("cls");

    while(true){
        cout<<"Employee Panel"<<endl<<endl;
        cout<<"-------------------------------"<<endl;
        cout << "Select your choice:\n 1. Add new student \n 2. Terminate student \n 3. Edit student details\n 4. Show all students details \n 5. Retrieve details via student id\n 6. Return to previous menu\n";
        cout << "Enter your choice: ";
        cin >> ech;

        if (ech == 6) {
            system("cls");
            break;
        }

        switch (ech) {
            case 1:
                system("cls");
                cout<<"Adding a new student\n\n"<<endl;
                add_student();
                break;

            case 2:
                system("cls");
                cout<<"Delete a student\n\n";
                delete_student();
                break;

            case 3:
                system("cls");
                cout<<"Edit student details\n\n";
                edit_student();
                break;

            case 4:
                system("cls");
                cout<<"Show all student details\n\n";
                show_all_student();
                break;

            case 5:
                system("cls");
                cout<<"Retrieve student details by id \n\n";
                show_student_by_id();
                break;

            default:
                cout << "Invalid choice. Please try again.\n\n" << endl;
                break;

        }


    }

}


void add_student(){

        int id;
        string name;
        int room_no;
        int contact_no;


        cout << "Enter the details of the student to add: \n" << endl;

        cout << "Enter student id: ";
        cin >> id;
        cin.ignore();

        cout << "Enter student name: ";
        getline(cin, name);

        cout << "Enter student room number: ";
        cin >> room_no;

        cout << "Enter student contact number: ";
        cin >> contact_no;

        int qstate = 0;


        stringstream insert_query_ss;
        insert_query_ss << "INSERT INTO students(id, name, room_no, contact) VALUES("<< id << ", '" << name << "', " << room_no << ", " << contact_no << ");";
        string insert_query = insert_query_ss.str();
        const char* insert_q = insert_query.c_str();

        qstate = mysql_query(conn, insert_q);

        if (qstate == 0) {
            cout << "Record inserted successfully.\n\n\n\n" << endl;
        } else {
            cout << "Insert failed: \n\n\n\n" << mysql_error(conn) << endl;
        }


    }

void delete_student() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    if(!check_exist_student(id)){
        cout << "Student doesn't exist!" << endl;
    }else{
    stringstream ss;

    ss << "DELETE FROM students WHERE id = " << id << ";";
    string query = ss.str();

    if (mysql_query(conn, query.c_str())) {
        cout << "Error deleting student: " << mysql_error(conn) << endl;
    } else {
        cout << "Student deleted successfully. \n\n\n\n" << endl;
    }
    }
}

void edit_student() {

    int id;
    cout << "Enter student ID to edit:\n\n ";
    cin >> id;
    if(!check_exist_student(id)){
        cout << "Student id doesn't exist " << endl;
    }else{

    string name;
    int room_no;
    long long contact;

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter new room number: ";
    cin >> room_no;

    cout << "Enter new contact: ";
    cin >> contact;

    stringstream ss;
    ss << "UPDATE students SET name = '" << name << "', room_no = " << room_no << ", contact = " << contact << " WHERE id = " << id << ";";

    string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        cout << "Error updating student: " << mysql_error(conn) << endl;
    }else {
        cout << "Student updated successfully.\n\n\n\n" << endl;
    }
    }
}

void show_all_student() {
    if (mysql_query(conn, "SELECT * FROM students")) {
        cout << "Error fetching students: " << mysql_error(conn) << endl;
        return;
    }
    res = mysql_store_result(conn);
    int num_fields = mysql_num_fields(res);


    cout<<"\n\nid | name | room no | contact \n";
    cout<<"~~~~~~~~~~~~~~~~~~\n\n";

    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            cout << row[i] << " | ";
        }
        cout << endl;
    }
    cout<<"~~~~~~~~~~~~~~~~~~\n\n";

}

void show_student_by_id() {

    int id;
    cout << "Enter student ID to retrieve: ";
    cin >> id;

    stringstream ss;
    ss << "SELECT * FROM students WHERE id = " << id << ";";

    string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        cout << "Error retrieving student: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);


    cout<<"\n\nid | name | room no | contact \n";
    cout<<"~~~~~~~~~~~~~~~~~~\n\n";
    if (row) {
        for (int i = 0; i < mysql_num_fields(res); i++) {
            cout << row[i] << " | ";
        }
        cout << endl;
    } else {
        cout << "Student not found." << endl;
    }
}


bool check_exist_employee(int id){

    stringstream ss;
    ss << "SELECT * FROM emp WHERE emp_id = " << id << ";";

    string query = ss.str();

    int q_str = 0 ;
    q_str = mysql_query(conn, query.c_str());
    res = mysql_store_result(conn);

   /* if (q_str!=0) {
        cout << "Error retrieving employee: " << mysql_error(conn) << endl;
        return false;
    }*/


    row = mysql_fetch_row(res);

    if(mysql_num_rows(res)==0){
        cout<<"\n\nRecord not found.......\n\n\n";
        return false;
    }
    else{
        return true;
    }




}
bool check_exist_student(int id){

    stringstream ss;
    ss << "SELECT * FROM students WHERE id = " << id << ";";

    string query = ss.str();

    int q_str = 0 ;
    q_str = mysql_query(conn, query.c_str());
/*
    if (q_str!=0) {
        cout << "Error retrieving Student: " << mysql_error(conn) << endl;
        return false;
    }
*/
    res = mysql_store_result(conn);

    row = mysql_fetch_row(res);

    if(mysql_num_rows(res)==0){
        cout<<"\n\nRecord not found.......\n\n\n";
        return false;
    }
    else{
        return true;
    }
}


MYSQL* db_connect(){

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"127.0.0.1","root","","studentcpp",0,NULL,0);

    return conn;
}
