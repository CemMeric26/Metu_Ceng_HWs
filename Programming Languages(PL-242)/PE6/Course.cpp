#include "Student.h"
#include "Course.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****               *** COURSE ***               ****/

/* Constructor : initializes <name> of the object to 
   the given string.
*/

//static vector<Student*>student_list2;
static vector<vector<Student*>> open_courses;

Course::Course(string name) {
	// TODO
	this->name=name;
	
}

/* Destructor  : It is NOT responsible of the 
   destruction of the prerequisite courses and students
   who take the course.
*/
Course::~Course() {
	// TODO
	/*for(int i=0;i<prerequisite.size();i++)
	{
	    delete prerequisite[i];
	}
	*/
}

/* Copy constructor : It totally applies shallow copy.
*/
Course::Course(const Course& course) {
	// TODO
	this->name=course.name;
	
	this->prerequisite= course.prerequisite;
	
}

/* This method directly adds (without creating a copy) the 
   given course as a prerequisite of the current course.
*/
void Course::addPrerequisite(const Course& course) {
    
	// TODO
	this->prerequisite.push_back(&course);
}

/* This method returns the prerequisites of the course.
*/
const vector<const Course*> Course::getPrerequisites() const {
    
	// TODO
	const vector<const Course*> prerequisite_p = prerequisite;
	return prerequisite_p;
	
}

/* This method returns the name of the course.
*/
string Course::getName() const {
	// TODO
	return name;
}

/* == operator overload : This method returns true if
   the two courses have the same name, false otherwise.
*/
bool Course::operator== (const Course& rhs) const {
	// TODO
	return !(name.compare(rhs.name));
}

/****************************************************/
/****             *** OPEN COURSE ***            ****/

/* Constructor : initializes the derived members of the
   Course class with the one given as first parameter.
   Also, initializes <term> of the object to the given 
   string. Initializes the <course_index> and the <quota>
   to the given last two integers, respectively.
   
   course_index is the index of the course in the array
   of OpenCourses at Metu.
   
   quota is the upper limit for the number of students
   who takes the course.
*/
OpenCourse::OpenCourse(const Course& course, string term, int course_index, int quota):Course(course) 
{
	// TODO
	this->term=term;
	this->course_index=course_index;
	this->quota=quota;
}

/* Destructor  : It is NOT responsible of the
   destruction of the prerequisite courses and students
   who take the course.
*/
OpenCourse::~OpenCourse() {
	
	/*for(int i=0;i<student_list.size();i++)
	{
	    delete student_list[i];
	}
	*/
}

/* Copy constructor : It totally applies shallow copy.
*/
OpenCourse::OpenCourse(const OpenCourse& opencourse):Course(opencourse)
{
	// TODO
	term=opencourse.term;
	course_index=opencourse.course_index;
	quota=opencourse.quota;
	student_list=opencourse.student_list;
	//open_courses.insert(open_courses.begin()+this->course_index,student_list);
	//student_list2=opencourse.student_list;
	
}

/* This method returns the ids of the students who take
   the current OpenCourse.
   In order this method to reach the students, it
   is advised to hold the students taking the course
   in a "static" array variable.
*/
const vector<int> OpenCourse::showStudentList() const {
    
	// TODO
	vector<int> student_ids;
	
	for(int i=0;i<student_list.size();i++)
	{
	    student_ids.push_back(student_list[i]->getId());
	}
	return student_ids;
	
}

/* This method calls the gradeCourse() method to grade
   the current OpenCourse for each student who take
   the course.
   In order this method to reach the students, it
   is advised to hold the students taking the course
   in a "static" array variable.
*/
void OpenCourse::finalize() {
	// TODO
	
	for(int i=0;i<student_list.size();i++)
	{
	    student_list[i]->gradeCourse(*this);
	}
	
/*	for(int j=0;j<open_courses[this->course_index].size();j++)
	{
	    open_courses[this->course_index][j]->gradeCourse(*this);
	}
	*/
}


/****************************************************/
/****          *** COURSE INSTANCE ***           ****/

/* Constructor : initializes the derived members of the
   OpenCourse class with the one given as first parameter.
   Also, holds the information that the current 
   CourseInstance object is owned by which student, by
   using the second parameter.
   HINT: For the related OpenCourse object to reach the
   entire student list, it is recommended to store the
   given student in a "static" array. This way of
   implementation may be beneficial in the other methods 
   later.
   This method initializes the grade corresponding to
   this CourseInstance to Grade::NA.
*/
CourseInstance::CourseInstance(const OpenCourse& opencourse, Student& student):OpenCourse(opencourse)
{
	// TODO
	this->student=&student;
}

/* Destructor  : It is NOT responsible of the
   destruction of the prerequisite courses and students
   who take the course.
*/
CourseInstance::~CourseInstance() {
	// TODO
	delete student;
}

/* This method saves the given grade value into the
   corresponding class member.
*/
void CourseInstance::setGrade(enum Grade grade) {
	// TODO
	this->grade=grade;
}

/* This method returns the grade of the CourseInstance.
*/
enum Grade CourseInstance::getGrade() const {
	// TODO
	
	return grade;
}