#include "DataBase.h"


int main(int argc, char **argv)
{
	DataBase db("localhost", "root", "", "lab10");

	/* 2. Get a list of all student names from the database. 
   3.  Display the data. */

	cout << "All students:" << endl;
	db.print_query("SELECT sName,sSurname FROM student");
	cout << endl;


	/* 4. Get a list of students who are taking classes in any subject from the database. 
   5. Display the list: name, course name and grade of the student taking the course.   */

	cout << “All students taking the course: " << endl;
	int subject;
	cout << "Enter subject number: ";
	cin >> subject;

	char buf[2048];
	sprintf_s(buf, "SELECT student.sName,student.sSurname,\
				 subjects.nameSubject,\
				 student_subjects.grade_of_subject \
				 FROM student_subjects \
				 LEFT JOIN student \
				 ON student.id = student_subjects.id_student\
				 LEFT JOIN subjects\
				 ON subjects.id = student_subjects.id_subjects\
				 WHERE student_subjects.id_subjects = %i"
				 , subject);

	db.print_query(buf);
	cout << endl;

	/* 6. An authorization mechanism for the program based on available database.  */

	char login[100];
	char password[100];

	cout << "Authorization: " << endl;
	cout << "Login (sName): ";
	cin >> login;
	cout << "Haslo (sSurname): ";
	cin >> password;

	int id = db.check_login(login, password);

	if (id >= 0)
	{ 
    // logged in
		cout << "Logged in successfully. Downloading your subjects ... \n" << endl;
		char buf[2048];
		sprintf_s(buf, "SELECT subjects.nameSubject,\
					   student_subjects.ocena_z_subjectu \
					   FROM student \
					   LEFT JOIN student_subjects \
					   ON student.id = student_subjects.id_student\
					   LEFT JOIN subjects\
					   ON subjects.id = student_subjects.id_subjects\
					   WHERE student.id = %i"
					   , id);

		db.print_query(buf);
		cout << endl;

	}
	else
	{
    // not logged in
		cout << "Failed to login" << endl;
	}

	system("pause");
	return 0;
}
