/*
    Name: Fares Elbermawy.
    Project description: Simulating a university which has three courses that they offer. Each course has its
    own lecturer and students. But there are some conditions for students. First, if the student is from
    another university they are only allowed to enroll in one course. Second, there cannot be two students
    with the same email enrolled in the same course. Each course has a max of 10 participants and minimum of
    3. If it is less than 3 it won't be conducted. After enrolling all students, We print out all the courses
    and the participants including a message if the course won't be conducted. Then printing the courses which
    are not fully booked with their name, number of free places, and the name of the lecturer and their title.
    Lastly, print the data of participants who should be notified that their course would not be conducted.
*/
#include <iostream>
#include <vector>
using namespace std;
//A universal variable stating the name of the university we are in.
string universityName = "THD";
//Making the parent class person which includes child classes who are students and lecturers.
class PERSON
{
protected:
    //Each person has their own Surname,first name, and email address.
    string surname;
    string firstName;
    string email;
public:
    PERSON(string surname, string firstName, string email)
    {
        this -> surname = surname;
        this -> firstName = firstName;
        this -> email = email;
    }
};
//Making the child class Lecturer
class LECTURER: public PERSON
{
    //Each lecturer has their academic title in addition.
    string academic_title;
public:
    LECTURER(string surname, string firstName, string email, string academic_title): PERSON(surname, firstName, email)
    {
        this -> academic_title = academic_title;
    }
    //Getting the lecturer full name and academic title
    string lecturerName()
    {
        return this -> academic_title + ' ' + this -> firstName + ' ' + this -> surname;
    }
} ;
//Making the child class student.
class STUDENT: public PERSON
{
    //Each student has their own matriculation number, university which they are enrolled in, and the number of courses they are enrolled in.
    int matriculationNumber;
    string university;
    int coursesTaken = 0;
public:
    STUDENT(string surname, string firstName, string email, int matriculationNumber, string university): PERSON(surname, firstName, email)
    {
        this -> matriculationNumber = matriculationNumber;
        this -> university = university;
    }
    //Checking if the student is allowed to take another course or not.
    bool isAllowed()
    {
        if (coursesTaken > 0 && university != universityName)
        {
            return false;
        }
        return true;
    }
    //Getting the email of the student to check with it if there is duplicate emails in the same course.
    string getEmail()
    {
        return this -> email;
    }
    //Printing all the data of the student.
    void printData()
    {
        cout << "Name: " << this -> firstName << " " << this -> surname << endl;
        cout << "email: " << getEmail() << endl;
        cout << "matriculation Number: " << this -> matriculationNumber << endl;
        cout << "University: " << this -> university << endl;
    }
} ;
//Making a course class.
class COURSE
{
    //Each course has its own name, lecturer, and list of students participating in it.
    string courseName;
    LECTURER lecturer;
    vector <STUDENT> participants;
public:
    COURSE(string courseName, LECTURER lecturer): lecturer(lecturer)
    {
        this -> courseName = courseName;
    }
    string getName()
    {
        return courseName;
    }
    //Method to add a student to the course
    void addParticipant(STUDENT student)
    {
        //Checking if the course has reached the limit and if the student is allowed to take the course.
        if (participants.size() < 10 && student.isAllowed())
        {
            //Checking if there is another student registered with the same email in the same course.
            for (int i = 0; i < participants.size(); i++)
            {
                if (participants[i].getEmail() == student.getEmail())
                {
                    cout << "Error! Duplicate email has been found." << endl;
                    return;
                }
            }
            participants.push_back(student);
        }
        else
        {
            cout << "Error! Maximum participants reached or this student has the max limit of courses." << endl;
        }
    }
    //Checking if the number of participants is enough to start the course.
    bool takesPlace()
    {
        if (participants.size() >= 3)
            return true;
        return false;
    }
    //Printing our the course name and the data of the participants in it.
    void participantsData()
    {
        cout << "Course name: " << courseName << endl;
        for (int i = 0; i < participants.size(); i++)
        {
            participants[i].printData();
        }
    }
    //Checking if the course is not fully booked.
    void notFullyBooked()
    {
        //Making the condition here to spare lines from the main function
        if (participants.size() < 10)
        {
            cout << "Name of the course: " << courseName << endl;
            cout << "The number of free places are: " << 10 - participants.size() << endl;
            cout << "Name of the lecturer: " << lecturer.lecturerName() << endl;
        }
    }
};
int main()
{
    int coursesNumber = 3;
    //Making objects of the lecturer class for the three programs.
    LECTURER programmingLecturer("Doe", "John", "john.doe@thd.com", "Dr.");
    LECTURER databasesLecturer("Smith", "Mike", "mikeSmith@thd.com", "Prof.");
    LECTURER softwareLecturer("Lee", "Sarah", "Sarah_lee@thd.com", "Prof.Dr.");
    //Making objects of the three courses and storing them in an array.
    vector <COURSE> courses = {COURSE("Programming", programmingLecturer), COURSE("Databases", databasesLecturer), COURSE("Software Engineer", softwareLecturer)};
    //Making objects of students.
    STUDENT student1("Dean", "Lina", "Lina.Dean@thd.de", 12345, "THD");
    STUDENT student2("Mueller", "Liza", "Liza.Mueller@thd.de", 12335, "THD");
    STUDENT student3("Bauer", "Marko", "Marko.Bauer@tum.de", 34012, "TUM");
    STUDENT student4("Patel", "Mila", "Mila.Patel@fau.de", 4519, "FAU");
    STUDENT student5("Smith", "Alex", "Alex.Smith@thd.de", 122345, "THD");
    //Enrolling students to courses.
    courses[0].addParticipant(student1);
    courses[0].addParticipant(student2);
    courses[0].addParticipant(student3);
    courses[1].addParticipant(student4);
    courses[2].addParticipant(student5);
    courses[2].addParticipant(student4); //this should give an error because this student isn't allowed to take more than one course.
    //Outputting all the courses with the participants.
    cout << "Courses that are available: " << endl;
    for(int i = 0; i < coursesNumber; i++)
    {
        courses[i].participantsData();
        if (!courses[i].takesPlace())
        {
            cout << "Course will not take place." << endl;
        }
        cout << endl;
    }
    //Printing the courses that are not fully booked yet
    cout << "Courses that are not fully booked: " << endl;
    for(int i = 0; i < coursesNumber; i++)
    {
        courses[i].notFullyBooked();
        cout << endl;
    }
    //Printing the participants data which should be notified that their course will not take place
    cout << "These participants should be notified that their course will not take place: " << endl;
    for (int i = 0; i < coursesNumber; i++)
    {
        if (!courses[i].takesPlace())
        {
            courses[i].participantsData();
            cout << endl;
        }
    }
    return 0;
}
