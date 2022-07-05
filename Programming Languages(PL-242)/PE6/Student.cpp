#include "Student.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****               *** STUDENT ***              ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
*/
Student::Student(int _id, string _fullname, string _department) {
    
	// TODO
	this->id= _id;
	this->fullname=_fullname;
	this->department=_department;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current student.
*/
Student::~Student() {
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
}

/* Copy constructor : It totally applies shallow copy.
*/
Student::Student(const Student& student) {
	// TODO
	this->id= student.id;
	this->fullname=student.fullname;
	this->department=student.department;
}

/* This method returns the id of the student.
*/
int Student::getId() const {
	// TODO
	return id;
}

/* This method returns the GPA of the student.
*/
float Student::getGPA() const {
	// TODO
	float total=0;
	int size=courses.size();
	for(int i=0;i<size;i++)
	{
	    total +=courses[i]->getGrade();
	}
	
	//this->gpa=total/size;
	
	return total/size;
}

/* This method returns the courses taken by
   this student. Note that the grade taken in that
   course is not important. You should return
   all the passed and failed courses.
*/
vector<const CourseInstance*> Student::listCourses() const {
	// TODO
	vector<const CourseInstance*> course_list;
	//course_list=courses;
	
	for(int i=0;i<courses.size();i++)
	{
	    //const CourseInstance* const_course = new CourseInstance(*(courses[i]),*this);
	    course_list.push_back(courses[i]);
	}
	
	return course_list;
}

/* This method grades the given course for this student.
   In order to grade the course, learnGrade() method is 
   called. learnGrade() method is already implemented by 
   the HW admin, yet it is invisible to you. You call it
   by giving the course name as the first argument and
   student id as the second argument. For instance;
       learnGrade("Programming Languages", 1234567);
   Then, you should save the grade returned by learnGrade().
   
   Also, after learning the grade, you should recalculate
   the GPA of the student in this method.
   GPA is a float value calculated by simply taking the 
   average of all the graded courses (The courses for which
   gradeCourse() method is called before or now).
*/
void Student::gradeCourse(const OpenCourse& openCourse) 
{
	// TODO
	Grade grade;
	grade = learnGrade(openCourse.getName(),id);
	
	for(int i=0;i<courses.size();i++)
	{
	    if(courses[i]->getName()==openCourse.getName())
	    {
	        courses[i]->setGrade(grade);
	        break;
	    }
	}
	gpa=this->getGPA();
	
}

/* This method sets the upgrade information for the current
   student to true. You may not need this method, yet still
   it is defined in case that it may be beneficial later.
*/
void Student::setUpgradeStatus() {
	// TODO
	upgrade_status=true;
}


/****************************************************/
/****              *** FRESHMAN ***              ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to 
   carry the upgrade information and initalize it to 
   false. This may be needed in the other methods 
   later on.
*/
Freshman::Freshman(int id, string fullname, string department):Student(id,fullname,department) {
	// TODO
	this->gpa=0.0;
	upgrade_status=false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current freshman.
*/
Freshman::~Freshman() {
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
}

/* Copy constructor : It totally applies shallow copy.
*/
Freshman::Freshman(const Freshman& freshman):Student(freshman) 
{
	// TODO
	
}

/* This method tries to add the given opencourse.
   In order to add, it just checks the prerequisites of the
   course is satisfied ot not. If all the prerequisites are
   satisfied (the prerequisite courses had been taken before),
   then it adds the course by constructiong a new CourseInstance
   object by using given OpenCourse object, then the newly
   created CourseInstance should be stored in an array of taken
   courses.
   If the course could be added successfuly, the method returns
   true. Otherwise (if there is at least one non-satisfied 
   prerequisite), it returns false.
*/
bool Freshman::addCourse(const OpenCourse& opencourse) {
	// TODO
	
	int count=0;
	for(int i=0;i<opencourse.getPrerequisites().size();i++)
	{
	    for(int j=0;j<courses.size();j++)
	    {
	        if((opencourse.getPrerequisites())[i]->getName() == courses[i]->getName())
	        {
	            count++;
	        }
	    }
	}
	
	if(count != opencourse.getPrerequisites().size() )
	{
	    return false;
	}
	
	CourseInstance* new_course= new CourseInstance(opencourse,*this);
	courses.push_back(new_course);
	
	
	
	
	return true;
}

/****************************************************/
/****              *** SOPHOMORE ***             ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
*/
Sophomore::Sophomore(int id, string fullname, string department):Freshman(id,fullname,department) {
	// TODO
	
	INTERNSHIP_2=false;
	INTERNSHIP_1=false;
	
}

/* Constructor : initializes the derived members of the
   Freshman class with the one given as first parameter.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
 */
Sophomore::Sophomore(const Freshman& freshman):Freshman(freshman) 
{
	// TODO
	INTERNSHIP_2=false;
	INTERNSHIP_1=false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current sophomore.
*/
Sophomore::~Sophomore() 
{
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
	
}

/* Copy constructor : It totally applies shallow copy.
*/
Sophomore::Sophomore(const Sophomore& sophomore):Freshman(sophomore) {
	// TODO
	INTERNSHIP_2=sophomore.INTERNSHIP_2;
	INTERNSHIP_1=sophomore.INTERNSHIP_1;
}

/* This method grades the internship with the given id
   (1 or 2).
   In order to grade the internship, learnGrade() method 
   is called. learnGrade() method is already implemented 
   by the HW admin, yet it is invisible to you. You call 
   it by giving the internship name as the first argument 
   and student id as the second argument. For instance;
       learnGrade("INTERNSHIP-1", 1234567); or
	   learnGrade("INTERNSHIP-2", 1234567);
   If the grade returned by learnGrade() method is greater
   than or equal to DD, then restore the value of the 
   corresponding internship variable as true, else leave it
   as false.
*/
void Sophomore::doAnInternship(int intership_no) 
{
	// TODO
	Grade grade;
	if(intership_no==1)
	{
	    grade=learnGrade("INTERNSHIP-1", id);
	    if(grade >=60)
	    {
	        INTERNSHIP_1=true;
	    }
	    else
	    {
	        INTERNSHIP_1=false;
	    }
	}
	else
	{
	    grade=learnGrade("INTERNSHIP-2", id); 
	    if(grade >=60)
	    {
	        INTERNSHIP_2=true;
	    }
	    else
	    {
	        INTERNSHIP_2=false;
	    }
	}
	
	
}

/* This method returns the status of the internship with
   the given id (1 or 2). The status is the fact that 
   it is completed successfully or not (true or false, 
   respectively).
*/
bool Sophomore::getInternshipStatus(int intership_no) {
	// TODO
	if(intership_no==1)
	{
	    return INTERNSHIP_1;
	}
	else
	{
	    return INTERNSHIP_2;
	}
	
}

/****************************************************/
/*                                                  */
/*           IT IS ENOUGH TO IMPLEMENT              */
/*    JUST CONSTRUCTORs, DESTRUCTOR & COPY CONS.    */
/*        FOR THE CLASS JUNIOR and SENIOR           */
/*     SIMILAR TO CLASS FRESHMAN and SOPHOMORE.     */
/*                                                  */
/*     JUNIOR and SENIOR OBJECTS MAY BE DEFINED     */
/*     IN TESTS, YET selectElectiveCourse() and     */ 
/*        graduate() METHOD WILL NOT BE USED.       */
/*                                                  */
/****************************************************/


/****************************************************/
/****                *** JUNIOR ***              ****/

Junior::Junior(int id, string fullname, string department):Sophomore(id,fullname,department) {
	// TODO
}

Junior::Junior(const Sophomore& sophomore):Sophomore(sophomore) {
	// TODO
}

Junior::~Junior() {
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
}

Junior::Junior(const Junior& junior):Sophomore(junior) {
	// TODO
}

void Junior::selectElectiveCourse() {
	// LEAVE EMPTY
}

/****************************************************/
/****                *** SENIOR ***              ****/

Senior::Senior(int id, string fullname, string department):Junior(id,fullname,department) {
	// TODO
}

Senior::Senior(const Junior& junior):Junior(junior) {
	// TODO
}

Senior::~Senior() {
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
}

Senior::Senior(const Senior& senior):Junior(senior) {
	// TODO
}

bool Senior::graduate() {
	// LEAVE EMPTY
	return true;
}

