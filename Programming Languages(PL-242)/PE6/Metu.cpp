#include "Metu.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****                *** METU ***                ****/

/* Constructor : Initialize your own variables if you
   need.
*/
Metu::Metu() {
	// TODO
	row_size=0;
	column_size=0;
}

/* Destructor  : It is responsible of the destruction of
   the Course and OpenCourse objects and the registered
   students, and the constrcuted seating plan, if any.
*/
Metu::~Metu() {
	// TODO
	for(int i=0;i<courses.size();i++)
	{
	    delete courses[i];
	}
	for(int j=0;j<students.size();j++)
	{
	    delete students[j];
	}
}

/* This method returns the student whose id is given
   in the argument. You need to find the corresponding
   student among the registered students.
*/
Student& Metu::getStudent(int id) {
	// TODO
	for(int i=0;i<students.size();i++)
	{
	    if(students[i]->getId()==id)
	    {
	        return *(students[i]);
	    }
	}
	
	
	
}

/* This method directly adds (without creating a copy)
   the given student to the list of registered students.
*/
void Metu::registerStudent(Student* student) {
	// TODO
	students.push_back(student);
	
}

/* This method directly adds (without creating a copy)
   the given course to the list of base course objects
   (not among the derived ones).
*/
void Metu::registerCourse(const Course& course) {
	// TODO
	//const Course* new_course= &course;
	courses.push_back(&course);
}

/* This method constructs a new OpenCourse object by deriving
   from the Course object given in the first argument and
   using the <term> and <quota> values given in the second
   and third arguments, respectively.
   Also, for each student given in the corresponding lists as
   function arguments, the newly created OpenCourse is tried 
   to be added in order.
   Note that the priority order is given from greater to less
   as follows: Seniors > Juniors > Sophomores > Freshmans.
   After the priority ordering, you should try to add the
   course for each student of the same type in the order inside
   the corresponding list.
   Also, during the course addition, you should take the course
   quota in consider.
   In the end, there may be left the students who could not add
   the course because of the quota or the course prerequisite.
   Finally, you should return the created OpenCourse object.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/
OpenCourse& Metu::openCourse(const Course& course, string term, int quota, 
							vector<Freshman*> freshmans, vector<Sophomore*> sophomores, vector<Junior*> juniors, vector<Senior*> seniors) {
	// TODO
	
	int index;
	for(int i=0;i<courses.size();i++)
	{
	    if(courses[i]->getName()==course.getName())
	    {
	        index=i;break;
	    }
	}
	
	
	
	OpenCourse* opc = new OpenCourse(course,term,index,quota); // course_index confusion
	
	int curr_number=0;
	
	for(int i=0;i<seniors.size();i++)
	{
	    if(quota>curr_number)
	    {
	        seniors[i]->addCourse(*opc);
	        //opc->student_list.push_back(seniors[i]);  //dangerous line
	        curr_number++;
	        //open_courses[index].push_back(seniors[i]);
	        
	    }
	}
	
	if(quota>curr_number)
	{
	    for(int i=0;i<juniors.size();i++)
	    {
    	    if(quota>curr_number)
    	    {
    	        juniors[i]->addCourse(*opc);curr_number++;
    	        //opc->student_list.push_back(juniors[i]);
    	        //open_courses[index].push_back(juniors[i]);
    	    }
	    }
	}
	
	if(quota>curr_number)
	{
	    for(int i=0;i<sophomores.size();i++)
	    {
    	    if(quota>curr_number)
    	    {
    	        sophomores[i]->addCourse(*opc);curr_number++;
    	        //opc->student_list.push_back(sophomores[i]);
    	       // open_courses[index].push_back(sophomores[i]);
    	    }
	    }
	}
	if(quota>curr_number)
	{
	    for(int i=0;i<freshmans.size();i++)
	    {
    	    if(quota>curr_number)
    	    {
    	        freshmans[i]->addCourse(*opc);curr_number++;
    	       // opc->student_list.push_back(freshmans[i]);
    	       //open_courses[index].push_back(freshmans[i]);
    	    }
	    }
	}
	
	
	
	return *opc;
}

/* This method upgrades the given Freshman object to
   the Sophomore status by constructing a new Sophomore
   object with the properties of the given Freshman.
   You should delete the given Freshman and place the 
   newly created Sophomore object to its location in the 
   students array of Metu object.
   In the end, you should return the created Sophomore.

   By the way; of course it would be nicer to define 
   this method in "virtual" in order to use it for different 
   types of Students. However, we do not want to test 
   you with "virtual" keyword in this PE. We've left it 
   to next PE.
*/
Sophomore* Metu::upgradeStudent(Freshman& student) {
	// TODO
	int index;
	Sophomore* newsophomore= new Sophomore(student);
	for(int i=0;i< students.size();i++)
	{
	    if(students[i]->getId()==student.getId())
	    {
	        index=i;
	        delete students[i];
	        break;
	    }
	}
	
	students.insert(students.begin()+index,newsophomore);
	
	return newsophomore;
	
	
}

/* This method upgrades the given Sophomore object to
   the Junior status by constructing a new Junior
   object with the properties of the given Sophomore.
   You should delete the given Sophomore and place the
   newly created Junior object to its location in the
   students array of Metu object.
   In the end, you should return the created Junior.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/
Junior* Metu::upgradeStudent(Sophomore& student) {
	// TODO
	
	int index;
	Junior* newjunior= new Junior(student);
	for(int i=0;i< students.size();i++)
	{
	    if(students[i]->getId()==student.getId())
	    {
	        index=i;
	        delete students[i];
	        break;
	    }
	}
	
	students.insert(students.begin()+index,newjunior);
	
	return newjunior;
	
	
}

/* This method upgrades the given Junior object to
   the Senior status by constructing a new Senior
   object with the properties of the given Junior.
   You should delete the given Junior and place the
   newly created Senior object to its location in the
   students array of Metu object.
   In the end, you should return the created Senior.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/
Senior* Metu::upgradeStudent(Junior& student) {
	// TODO
	int index;
	Senior* newsenior= new Senior(student);
	for(int i=0;i< students.size();i++)
	{
	    if(students[i]->getId()==student.getId())
	    {
	        index=i;
	        delete students[i];
	        break;
	    }
	}
	
	students.insert(students.begin()+index,newsenior);
	
	return newsenior;
	
}

/* This method sets the number of rows and number of columns in a
   standard Metu classroom with the given arguments, respectively.
*/
void Metu::setClassroomSize(int row_size, int column_size) {
	// TODO
	
	this->row_size=row_size;
	this->column_size=column_size;
}

/* This method tries to construct the 2D seating plan by using
   the given information as function argument one-by-one.
   The information consists of 2 integers and 1 string argument.
   The string parameter can be either "|" or "-".
   If it is "|", then it means location of the student whose id 
   given in the first argument is <row_id, column_id> whereas
   location of the student whose id given in the second argument
   is <row_id + 1, column_id>.
   If it is "-", then it means location of the student whose id 
   given in the first argument is <row_id, column_id> whereas
   location of the student whose id given in the second argument
   is <row_id, column_id + 1>.
*/
void Metu::addCheatInfo(int from_student_id, int to_student_id, string dir) {
	// TODO
	
}

/* This method prints the given seating plan, in
   other words the 2D array. Between each seat,
   print an empty space, i.e. " " character.
   Also, put an empty space to the end of each row.
   After each row (including the last one), print a
   new line, i.e. "\n" character.
   For the empty seats, print a "X" character (uppercase).
   For non-empty seats, print the id of the student
   sitting there.
*/
void Metu::printSeatingPlan() {
	// TODO
}
