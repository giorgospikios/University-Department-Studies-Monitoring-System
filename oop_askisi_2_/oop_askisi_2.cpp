#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class Course;

class Person
{
	private:
		string name;
		string surname;
		string school;
		int age;
		int id;

	public:
		string get_name() const {return name;} //γυρναμε αντιγραφα και οχι αναφορες η΄ δεικτες στα ιδιωτικα μελη ωστε να επιτυγχανεται η ενθυλακωση
		string get_surname() const {return surname;} //const στο τελος της συναρτησης ωστε να μην μπορουν να αλαγχθουν ιδιωτικα μελη της κλασης αφου η συναρτησεις εχουν αμεση προσαβση σε αυτα
		string get_school() const {return school;}
		int get_age() const {return age;}
		int get_id() const {return id;}

		Person(const string& name = "not available", const string& surname = "not available", const string& school = "not available", const int age = -1, const int id = -1) 
				: name(name), surname(surname), school(school), age(age), id(id) {} //αρχικοποιω τα ιδιωτικα μελη της κλασης ακομα και αν δεν τα χρειαζομαι
		virtual ~Person() {};

		// virtual void print_data() const; //εχουμε προσθεση την επιλογη της εικονικης συναρτησης ωστε αν χρειαστει να τυπωθουν μονο τα ιδιωτικα μελη του Person η΄ των derived κλασεων

		virtual void print_data() const = 0; //γνησια εικονικη συναρτηση 
};

// void Person::print_data() const
// {
// 	cout << "name: " << name << '\n' ;
// 	cout << "surname: " << surname << '\n' ;
// 	cout << "school: " << school << '\n' ;
// 	cout << "age: " << age << '\n' ;
// 	cout << "id: " << id << "\n\n" ;
// }

class Student;

class Proffessor : public Person
{
	private:
		vector<Course*> proffesors_courses; //ενας καθηγητης μπορει να εχει παραπανω απο ενα μαθημα
		string proffessor_status; //επικουρος, αναπληρωτης, βοηθος
		string specialization;
		int salary;

	public:
		Proffessor(const string& name = "not available", const string& surname = "not available", const string& school = "not available", const int age = -1, 
				const int id = -1, const string& proffessor_status = "not available", const string& specialization = "not available", const int salary = -1) 
				: Person(name, surname, school, age, id), proffessor_status(proffessor_status), specialization(specialization), salary(salary) {}
		virtual ~Proffessor() {};

		virtual void print_data() const; //οι συναρτησεις των κλασεων που εχουν κληρονομισει δημοσια μια βασικη κλαση εχουν προσβαση στα δημιοσια και προστατευμενα μελη 
		void define_proffessors_course(Proffessor* const proffessor, Course* const course, bool check);
		void delete_proffessors_course(Course* const course_to_delete, bool check);
		void print_proffessor_courses() const;
		void define_student_grade(float grade, Student* student, const string& course_name);
		void courses_statistics(const string& requested_semester) const;
};

class Student : public Person
{
	private:
		map<Course*, float> course_grade_map; //εχουμε επιλεξει δομη map εφοσον ενας μαθητης μπορει να ειναι εγγεγραμμενος σε πολλα μαθηματα τα οποια ειναι μοναδικα και αν γινει λαθος και εισαχθει ξανα ιδιο μαθημα ο ελεγχος ειναι αμεσος

		typedef struct passed_courses{ //η ιδεα ηταν ο μαθητης περναει ενα μαθημα να αποθηκευεται σε αυτο το πινακα εφοσον το μαθηαματα για να παρει καποιος πτυχιο ειναι συγκεκριμενα αλλα δεν τα καταφεραμε να το υλοποιησουμε
			string course_name;
			string course_semester;
			int year_offered;
			bool mandatory;
			int ects;
		} passed_courses;
		passed_courses array[42];

		string student_tier; //προπτυχιακος, μεταπτυχιακος
		int semester_attendance;
		float grade_point_average;

	public:
		Student(const string& name = "not available", const string& surname = "not available", const string& school = "not available", const int age = -1, 
				const int id = -1, const string& student_tier = "not available", const int semester_attendance = -1, const float grade_point_average = -1) 
				: Person(name, surname, school, age, id), student_tier(student_tier), semester_attendance(semester_attendance), grade_point_average(grade_point_average) {}
		virtual ~Student() {};

		int get_semester_attendance() const {return semester_attendance;}
		float get_course_grade(const string& course_name);

		virtual void print_data() const;
		void print_students_selected_courses() const;
		void course_enrolment(Course* const course, bool check);
		void print_courses_grades(const string& semester_name);

		friend class Proffessor; //δεν θελω να μπορει ενας καθηγητης να εχει προσβαση σε ολα τα ιδιωτικα δεδομενα ενος μαθητη αρα δεν επιλεγω τη φιλικη προσεγγιση
};

class Course
{
	private:
		vector<Person*> vector_of_people;
		string course_name;
		string mandatory;
		int ects;
		int year_thatis_offered;
		string semester_thatis_offered;

	public:
		Course(const string& course_name = "not available", const string& mandatory = "not available", const int ects = -1, const int year_thatis_offered = -1, const string& semester_thatis_offered = "not available") 
				: course_name(course_name), mandatory(mandatory), ects(ects), year_thatis_offered(year_thatis_offered), semester_thatis_offered(semester_thatis_offered) {}
		virtual ~Course() {};

		string get_course_name() const {return course_name;}
		int get_year_thatis_offered() const {return year_thatis_offered;}
		string get_semester_thatis_offered() const {return semester_thatis_offered;}

		void set_semester(string s) {semester_thatis_offered = s;}

		void print_course_people() const;
		void print_course_proffessors() const;
		void print_course_students() const;
		void print_data() const;
		void define_course_proffessors(Proffessor* const proffessor, Course* const course, bool check);
		void delete_course_proffessors(Proffessor* const proffessor_to_delete, Course* const course, bool check);
		void student_enrolment(Student* const student, bool check);
		void return_all_students(vector<Student*>* pstudents_vector);

		Proffessor* find_proffessor(const int proffessor_id_requested);
		Student* find_student(const int requested_student_id);
};

class Semester
{
	private:
		vector<Course*> courses_vector; //vector με τα μαθηματα το οποια προσφερονται στο συγκεκριμενο εξαμηνο
		string semester_name;

	public:
		Semester(const string& semester_name = "not available") : semester_name(semester_name) {};
		virtual ~Semester() {};

		string get_semester_name() const {return semester_name;}

		Course* find_course(const string& course_name) const;

		void print_semester_courses() const;
		void define_course_proffessors(Proffessor* proffessor, Course* course) const; //αυτη η συναρτηση καλειται απο τη define_course_proffessors της secretary αφου το μαθημα βρισκεται μεσα στο εξαμηνο σε δομη της επιλογης μας
		void delete_course_proffessors(Proffessor* proffessor_to_delete, Course* course);
		void define_semester_courses(Course* const course);
		void delete_course_from_semester(const string& course_name);

		int sizeof_courses_vector();
};

class Secretary
{
	private:
		vector<Semester*> semesters_vector; //ακομα μια ιδεα ειναι απλα να εχει 2 δεικτες σε 2 semester αντικειμενα αφου ολα τα πιθανα εξαμηνα ειναι 2(χειμερινο-εαρινο)
		vector<Semester> semesters_holder_vec;
		vector<Proffessor> proffessors_holder_vector; //δοχεια που θα γεμησουν απο τα δεδομενα των αρχειων txt που θα περασουμε στη γραμματεια 
		vector<Student> students_holder_vector;
		vector<Course> courses_holder_vector;

	public:
		Secretary(Semester* winter_semester, Semester* spring_semester); //εφοσον η γραμματεια οριζει τους διδασκοντες σε καθε εξαμηνο δλδ δεν μπορει να υφισταται γραμματεια χωρις εξαμηνο σκεφτηκαμε να οριζουμε τα εξαμηνα που διαχειριζεται η γραμματεια μεσα απο τον κατασκευαστη της με τη πουποθεση οτι εχουν ηδη δημιουργηθει
		Secretary();
		virtual ~Secretary() {};

		void create_and_set_proffessors(const string& name, const string& surnname, const string& school, const int age, const int id, const string& proffessor_status, 
										const string& specialization, const int salary);
		void create_and_set_students(const string& name, const string& surnname, const string& school, const int age, const int id, const string& student_tier, 
						  			const int semester_attendance);
		void create_and_set_courses(const string& course_name, const string& mandatory, const int ects, const int year_thatis_offered, const string& semester_thatis_offered); 

		Semester* find_semester(const string& semester_name);
		Semester* find_semester_from_holder(const string& semester_name);
		Proffessor* find_proffessor(const int proffessor_id_requested);
		Student* find_student(const int students_id_requested);
		Course* find_course(const string& requested_course_name);

		void define_course_proffessors(Proffessor* proffessor, Course* course);
		void differentiate_course_proffessor(const string& semester_name, Proffessor* proffessor, Course* course);
		void delete_course_proffessors(Proffessor* proffessor_to_delete, Course* course);
		void define_semester_courses(const string& semester_name, Course* const course) const;
		void move_course_toanother_semester(const string& course_name);

		void add_new_proffessor(Proffessor& new_proffessor);

		void update_proffessors_data();

		void can_student_graduate(Student* student);
		void which_students_passedthis_course(const string& course_name);
};


float Student::get_course_grade(const string& course_name)
{
	float return_grade;
	for(auto cgm = course_grade_map.begin(); cgm != course_grade_map.end(); cgm++)
		if((cgm->first)->get_course_name() == course_name){
			return_grade = cgm->second;
			break;
		}
	return return_grade;
}

void Student::print_data() const
{	
	string name = get_name();
	string surname = get_surname();
	string school = get_school();
	int age = get_age();
	int id = get_id();
	cout << "name: " << name << '\n';
	cout << "surname: " << surname << '\n';
	cout << "shcool: " << school << '\n';
	cout << "age: " << age << '\n';
	cout << "id: " << id << '\n';
	cout << "semester_attendance: " << semester_attendance << '\n';
	cout << "grade_point_average: " << grade_point_average << "\n\n";
}

void Student::print_students_selected_courses() const
{	
	if(course_grade_map.size() == 0){
		cout << "map is empty \n";
		return;
	}
	for (auto i = course_grade_map.begin(); i != course_grade_map.end(); i++)
		cout << (i->first)->get_course_name() << " with grade: " << (i->second) << '\n';
}

void Student::course_enrolment(Course* const course, bool check)
{	
	course_grade_map.insert({course, -1}); //αρχικοποιω με -1 το οποιο υποδυκνυει οτι ακομα ο καθηγητης δεν εχει περασει βαθμο
	if((float)(course->get_year_thatis_offered()) <= (float)get_semester_attendance()/2){
		if(!check){
			check = true;
			course->student_enrolment(this, check);
		}
	}
	else{
		cout << "the course that the student wants to enroll is in bigger year\n";
		return;
	}
}

void Student::print_courses_grades(const string& semester_name)
{
	for(auto cgm = course_grade_map.begin(); cgm != course_grade_map.end(); cgm++)
		if((cgm->first)->get_semester_thatis_offered() == semester_name)
			cout << "course: " << (cgm->first)->get_course_name() << " grade: " << (cgm->second) << '\n'; 
}

void Proffessor::print_data() const 
{
	string name = get_name();
	string surname = get_surname();
	string school = get_school();
	int age = get_age();
	int id = get_id();
	cout << "name: " << name << '\n';
	cout << "surname: " << surname << '\n';
	cout << "shcool: " << school << '\n';
	cout << "age: " << age << '\n';
	cout << "id: " << id << '\n';
	cout << "proffessor_status: " << proffessor_status << '\n';
	cout << "specialization: " << specialization << '\n';
	cout << "salary: " << salary << "\n\n";
}

void Proffessor::define_proffessors_course(Proffessor* const proffessor, Course* const course, bool check)
{
	proffesors_courses.push_back(course);
	if(!check){
		check = true;
		course->define_course_proffessors(proffessor, course, check);
	}
}

void Proffessor::delete_proffessors_course(Course* const course_to_delete, bool check)
{
	for(int i=0; i<(int)(proffesors_courses.size()); i++)
		if(course_to_delete->get_course_name() == proffesors_courses[i]->get_course_name())
			proffesors_courses.erase(proffesors_courses.begin() + i);

	if(!check){
		check = true;
		course_to_delete->delete_course_proffessors(this, course_to_delete, check);
	}
}

void Proffessor::print_proffessor_courses() const
{	
	if(proffesors_courses.size() == 0){
		cout << "this proffessor hasn't any courses assigned to him yet\n";
		return;
	}
	for(int i=0; i<(int)(proffesors_courses.size()); i++)
		cout << proffesors_courses[i]->get_course_name() << '\n';
}

void Proffessor::define_student_grade(float grade, Student* student, const string& course_name) 
{	
	int proffesors_courses_size = proffesors_courses.size();
	if(proffesors_courses_size == 0){
		cout << "this proffessor does not teach any course\n";
		return;
	}

	for(int i=0; i < (int)(proffesors_courses.size()); i++){
		if(proffesors_courses[i]->get_course_name() == course_name)
			break;
		else{
			cout << "the course you enter is not taught by this proffessor\n";
			return;
		}
	}

	for(auto i = student->course_grade_map.begin(); i != student->course_grade_map.end(); i++)
		if( (i->first)->get_course_name() == course_name){
			i->second = grade;
			return;
		}
	cout << "the student hasnt enroll in this course\n";
}

void Proffessor::courses_statistics(const string& requested_semester) const
{	

	if(requested_semester != "winter_semester")
		if(requested_semester != "spring_semester"){
			cout << "the semester you provide does not exist, your options are winter and spring semesters that can be selected with the keywords: winter_semester-spring_semester\n";
			return;
		}

	for(int i=0; i<(int)(proffesors_courses.size()); i++)
		if(proffesors_courses[i]->get_semester_thatis_offered() == requested_semester){
			cout << "\nproffessor " << get_name() << ' ' << get_surname() << " with course " << proffesors_courses[i]->get_course_name() << " has these students:\n"; 
			proffesors_courses[i]->print_course_students();
		}
}

void Course::print_course_people() const
{	
	for(Person* person : vector_of_people){

		if(Student* student = dynamic_cast<Student*>(person))
			cout << "student's full name: " << student->get_name() << ' ' << student->get_surname() << '\n';

		if(Proffessor* proffessor = dynamic_cast<Proffessor*>(person))
			cout << "proffessor's full name: " << proffessor->get_name() << ' ' << proffessor->get_surname() << '\n';
	}
}

void Course::print_course_proffessors() const 
{	
	if(vector_of_people.size() == 0){
		cout << "this course hasnt any proffessors assigned to it yet\n";
		return;
	}

	for(Person* person : vector_of_people)
		if(Proffessor* proffessor = dynamic_cast<Proffessor*>(person))
			cout << "proffessor's name: " << proffessor->get_name() << '\n';
}

void Course::print_course_students() const
{
	for(Person* person : vector_of_people)
		if(Student* student = dynamic_cast<Student*>(person)){
			cout << "student's full name: " << student->get_name() << ' ' << student->get_surname();
			cout << " - student's id: " << student->get_id() << '\n';
		}
}

void Course::print_data() const
{
	cout << "course name: " << course_name << '\n';
	cout << "is course mandatory: " << mandatory << '\n';
	cout << "course's ects : " << ects << '\n';
	cout << "the year this course is offered : " << year_thatis_offered << '\n';
	cout << "the semester this course is offered : " << semester_thatis_offered << '\n';
}

void Course::define_course_proffessors(Proffessor* const proffessor, Course* const course, bool check) 
{	
	vector_of_people.push_back(proffessor);
	if(!check){
		check = true;
		proffessor->define_proffessors_course(proffessor, course, check);
	}
}

void Course::delete_course_proffessors(Proffessor* const proffessor_to_delete, Course* const course, bool check)
{
	for(int i=0; i<(int)(vector_of_people.size()); i++)
		if(proffessor_to_delete->get_name() == vector_of_people[i]->get_name())
			vector_of_people.erase(vector_of_people.begin() + i);

	if(!check){
		check = true;
		proffessor_to_delete->delete_proffessors_course(course, check);
	}
}

void Course::student_enrolment(Student* const student, bool check) 
{
	vector_of_people.push_back(student);
	if(!check){
		check = true;
		student->course_enrolment(this, check);
	}
}

void Course::return_all_students(vector<Student*>* pstudents_vector)
{	
	int i = 0;
	for(Person* person : vector_of_people)
		if(Student* student = dynamic_cast<Student*>(person)){
			cout << "\n student->get_name(): " << student->get_name() << '\n';
			(*pstudents_vector)[i] = student;
			cout << "\n\ni = " << i;
			i++;
		}
}

Proffessor* Course::find_proffessor(const int proffessor_id_requested)
{
	Proffessor* pointerto_requested_proffessor;

	for(Person* person : vector_of_people)
		if(Proffessor* proffessor = dynamic_cast<Proffessor*>(person))
			if(proffessor->get_id() == proffessor_id_requested)
				pointerto_requested_proffessor = proffessor;
	
	return pointerto_requested_proffessor;
}

Student* Course::find_student(const int requested_student_id)
{
	Student* pointerto_requested_student;

	for(Person* person : vector_of_people)
		if(Student* student = dynamic_cast<Student*>(person))
			if(student->get_id() == requested_student_id)
				pointerto_requested_student = student;
	
	return pointerto_requested_student;
}

int Semester::sizeof_courses_vector()
{
	return courses_vector.size();
}

Course* Semester::find_course(const string& course_name) const
{
	for(int i=0; i<(int)(courses_vector.size()); i++)
		if(courses_vector[i]->get_course_name() == course_name)
			return courses_vector[i];
	cout << "\nthe course you asked for does not exist in " << get_semester_name() << '\n';
	return nullptr;
}

void Semester::print_semester_courses() const
{	
	int size_of_courses_vector = courses_vector.size(); 
	if(size_of_courses_vector == 0){
		cout << "vector is empty\n";
		return;
	}
	for(int i=0; i<size_of_courses_vector; i++)
		cout << courses_vector[i]->get_course_name() << '\n';
}

void Semester::define_course_proffessors(Proffessor* proffessor, Course* course) const
{	
	bool check = false;
	//πρεπει να ελεγχω αν υπαρχει το μαθημα που θα ορισω καθηγητη σε αυτο
	course->define_course_proffessors(proffessor, course, check);
}

void Semester::delete_course_proffessors(Proffessor* proffessor_to_delete, Course* course)
{
	bool check = false;
	course->delete_course_proffessors(proffessor_to_delete, course, check);
}

void Semester::define_semester_courses(Course* const course)  
{	
	courses_vector.push_back(course);
}

void Semester::delete_course_from_semester(const string& course_name)
{	
	for(int i=0; i<(int)(courses_vector.size()); i++)
		if(courses_vector[i]->get_course_name() == course_name)
			courses_vector.erase(courses_vector.begin() + i);
}

void Secretary::which_students_passedthis_course(const string& course_name)
{	
	//αρχικα πρεπει να βρουμε σε ποιο εξαμηνο ανηκει το μαθημα που ζηταει η γραμματεια
	Semester* pwinter_semester = find_semester("winter_semester");
	Semester* pspring_semester = find_semester("spring_semester");

	Course* wrequested_course = pwinter_semester->find_course(course_name);
	Course* srequested_course = pspring_semester->find_course(course_name);
	
	string output_file = course_name;
	output_file.append(".txt");
	ofstream fout_course_name(output_file);
	if(fout_course_name.is_open() == false){

		fout_course_name.close();
		cout << "ERROR: output_file.txt cant be created/opened\n";
		exit(EXIT_FAILURE);
	}
	vector<Student*> students_vector;//το κανω για να μειωση τη χρονικη πολυπλοκοτητα αντι να καλω συνεχεια τη find_student
	if(wrequested_course != nullptr){
		fout_course_name << pwinter_semester->get_semester_name() << ' ' << wrequested_course->get_course_name() << "\n\n"; 

		wrequested_course->return_all_students(&students_vector);
		for(int i=0; i<(int)(students_vector.size()); i++)
			if(students_vector[i]->get_course_grade(course_name) >= 4.9)
				fout_course_name << students_vector[i]->get_name() << ' ' << students_vector[i]->get_surname() << ' ' << students_vector[i]->get_id() << '\n'; 		
	}
	else{
		fout_course_name << pspring_semester->get_semester_name() << ' ' << srequested_course->get_course_name() << "\n\n"; 
		
		srequested_course->return_all_students(&students_vector);
		for(int i=0; i<(int)(students_vector.size()); i++)
			if(students_vector[i]->get_course_grade(course_name) >= 4.9)
				fout_course_name << students_vector[i]->get_name() << ' ' << students_vector[i]->get_surname() << ' ' << students_vector[i]->get_id() << '\n';
	}
}

Secretary::Secretary(Semester* winter_semester, Semester* spring_semester)
{
	semesters_vector.push_back(winter_semester); //υπαρχουν μονο 2 εξαμηνα χειμερινο και εαρινο 
	semesters_vector.push_back(spring_semester);
}

Secretary::Secretary()
{
	Semester winter_semester("winter_semester");
	Semester spring_semester("spring_semester");

	semesters_holder_vec.push_back(winter_semester);
	semesters_holder_vec.push_back(spring_semester);

	Semester* pwinter_semester = find_semester_from_holder(winter_semester.get_semester_name());
	Semester* pspring_semester = find_semester_from_holder(spring_semester.get_semester_name());

	semesters_vector.push_back(pwinter_semester);
	semesters_vector.push_back(pspring_semester);

	semesters_holder_vec.clear();
}

void Secretary::create_and_set_proffessors(const string& name, const string& surname, const string& school, const int age, const int id, const string& proffessor_status, 
										   const string& specialization, const int salary)
{
	Proffessor proffessor(name, surname, school, age, id, proffessor_status, specialization, salary);
	proffessors_holder_vector.push_back(proffessor);
}

void Secretary::create_and_set_students(const string& name, const string& surname, const string& school, const int age, const int id, const string& student_tier, 
						     			const int semester_attendance)
{
	Student student(name, surname, school, age, id, student_tier, semester_attendance);
	students_holder_vector.push_back(student);
}

void Secretary::create_and_set_courses(const string& course_name, const string& mandatory, const int ects, const int year_thatis_offered, const string& semester_thatis_offered)
{	
	Course* new_course_pointer;
	Course course(course_name, mandatory, ects, year_thatis_offered, semester_thatis_offered);
	courses_holder_vector.push_back(course);
	new_course_pointer = find_course(course_name);
	define_semester_courses(semester_thatis_offered, new_course_pointer);
}

Semester* Secretary::find_semester(const string& semester_name)
{	
	// Semester* requested_semester;
	for(int i=0; i<(int)(semesters_vector.size()); i++)
		if(semesters_vector[i]->get_semester_name() == semester_name)
			return semesters_vector[i];
	return nullptr;
}

Semester* Secretary::find_semester_from_holder(const string& semester_name)
{	
	Semester* semester_tobe_returned;
	for(int i=0; i<(int)(semesters_holder_vec.size()); i++)
		if(semesters_holder_vec[i].get_semester_name() == semester_name)
			semester_tobe_returned = &semesters_holder_vec[i];
	return semester_tobe_returned;
}			

Proffessor* Secretary::find_proffessor(const int proffessor_id_requested)
{	
	Proffessor* pointerto_requested_proffessor;

	for(int i=0; i<(int)(proffessors_holder_vector.size()); i++)
		if(proffessors_holder_vector[i].get_id() == proffessor_id_requested)
			pointerto_requested_proffessor = &proffessors_holder_vector[i];

	return pointerto_requested_proffessor;
}

Student* Secretary::find_student(const int students_id_requested)
{
	Student* pointerto_requested_student;

	for(int i=0; i<(int)(students_holder_vector.size()); i++)
		if(students_holder_vector[i].get_id() == students_id_requested)
			pointerto_requested_student = &students_holder_vector[i];

	return pointerto_requested_student;
}

Course* Secretary::find_course(const string& requested_course_name)
{
	Course* pointerto_requested_course;
	
	for(int i=0; i<(int)(courses_holder_vector.size()); i++)
		if(courses_holder_vector[i].get_course_name() == requested_course_name)
			pointerto_requested_course = &courses_holder_vector[i];
	
	return pointerto_requested_course;
}

void Secretary::define_course_proffessors(Proffessor* proffessor, Course* course) //ζητειται απο την εκφωνηση οτι πρεπει μεσα απο τη γραμματεια να οριζονται οι καθηγητες των μαθηαωτν
{	
	for(int i=0; i<(int)(semesters_vector.size()); i++)
		if(semesters_vector[i]->get_semester_name() == course->get_semester_thatis_offered())
			semesters_vector[i]->define_course_proffessors(proffessor, course); //καλουμαι τη συναρτηση του εξαμηνου γιατι το καθε μαθημα ανηκει και μπορει να ειναι μονο σε ενα εξαμηνο	

		//πρεπει αν δεν υπαρχει το εξαμηνο δλδ εχει περαστει λαθος ονομα να γυρναω exception
}

void Secretary::delete_course_proffessors(Proffessor* proffessor_to_delete, Course* course)
{
	for(int i=0; i<(int)(semesters_vector.size()); i++)
		if(semesters_vector[i]->get_semester_name() == course->get_semester_thatis_offered())
			semesters_vector[i]->delete_course_proffessors(proffessor_to_delete, course);
}

void Secretary::define_semester_courses(const string& semester_name, Course* const course) const
{
	for(int i=0; i<(int)(semesters_vector.size()); i++)
		if(semesters_vector[i]->get_semester_name() == semester_name){
			semesters_vector[i]->define_semester_courses(course);
			return;
		}
	cout << "the semester you provide does not exist, your options are winter and spring semesters that can be selected with the keywords: winter_semester-spring_semester\n";
}

void Secretary::move_course_toanother_semester(const string& course_name)
{	
	Semester* requested_semester;
	Semester* receiving_semester;
	Course* course_tobe_moved = find_course(course_name);
	for(int i=0; i<(int)(semesters_vector.size()); i++)
		if(semesters_vector[i]->get_semester_name() == course_tobe_moved->get_semester_thatis_offered())
			requested_semester = semesters_vector[i];
		else
			receiving_semester = semesters_vector[i];
	
	receiving_semester->define_semester_courses(course_tobe_moved);
	requested_semester->delete_course_from_semester(course_name);

	course_tobe_moved->set_semester(receiving_semester->get_semester_name());
}

void Secretary::add_new_proffessor(Proffessor& new_proffessor)
{
	proffessors_holder_vector.push_back(new_proffessor);
}


int main()
{	
	string name, surname, school, status, specialization, student_tier, course_name, semester_thatis_offered, mandatory;
	int age, id, salary, semester_attendance, ects, year_thatis_offered;
	// Semester winter_semester("winter_semester"); 
	// Semester spring_semester("spring_semester");

	// Secretary secretary(&winter_semester, &spring_semester);

	Secretary secretary;

	ifstream fin_proffessor("proffessors_data.txt");
	if(fin_proffessor.is_open() == false){
		cout << "Error: fin_proffessor's is_open() failed\n";
		exit(EXIT_FAILURE);
	}
	ifstream fin_student("students_data.txt");
	if(fin_student.is_open() == false){
		fin_proffessor.close();
		cout << "Error: fin_student's is_open() failed\n";
		exit(EXIT_FAILURE);
	}
	ifstream fin_course("courses_data.txt");
	if(fin_course.is_open() == false){
		fin_proffessor.close();
		fin_student.close();
		cout << "Error: fin_course's is_open() failed\n";
		exit(EXIT_FAILURE);
	}

	while(1){
		fin_proffessor >> name >> surname >> school >> age >> id >> status >>  specialization >> salary;
		if(!fin_proffessor)
			break;
		secretary.create_and_set_proffessors(name, surname, school, age, id, status, specialization, salary);
	}
	while(1){
		fin_student >> name >> surname >> school >> age >> id >> student_tier >> semester_attendance;
		if(!fin_student)
			break;
		secretary.create_and_set_students(name, surname, school, age, id, student_tier, semester_attendance);
	}
	while(1){
		fin_course >> course_name >> mandatory >> ects >> year_thatis_offered >> semester_thatis_offered;
		if(!fin_course)
			break;
		secretary.create_and_set_courses(course_name, mandatory, ects, year_thatis_offered, semester_thatis_offered);
	}

	//ελεγχω αν η προσθεση των μαθηματων στα εξαμηνα ηταν επιτυχης
	Semester* wrequested_semester = secretary.find_semester("winter_semester");
	Semester* srequested_semester = secretary.find_semester("spring_semester");
	cout << "spring semester courses: ";
	srequested_semester->print_semester_courses();
	cout << "\nwinter semester courses: ";
	wrequested_semester->print_semester_courses();
	cout << '\n';

	//ελεγχω αν μπορω να βρω εναν καθηγητη που βρισκεται στα αρχικα δοχεια βαση του Α.Μ του μεσω της γραμματειας
	Proffessor* requested_proffessor_pointer = secretary.find_proffessor(12345);
	requested_proffessor_pointer->print_data();

	//ελεγχω αν μπορω να βρω εναν μαθητη που βρισκεται στα αρχικα δοχεια βαση του Α.Μ του μεσω της γραμματειας
	Student* requested_student_pointer = secretary.find_student(1900353);
	requested_student_pointer->print_data();

	//ελεγχω αν μπορω να βρω ενα μαθημα που βρισκεται στα αρχικα δοχεια βαση του ονοματος του (υποθετωντας οτι το ονομα ειναι μοναδικο) μεσω της γραμματειας
	Course* requested_course_pointer = secretary.find_course("opsys");
	requested_course_pointer->print_data();

	//ελεγχω αν η μετακινηση ενος μαθηματος ηταν επιτυχεις
	secretary.move_course_toanother_semester(requested_course_pointer->get_course_name());
	cout << "\nspring semester courses: ";
	srequested_semester->print_semester_courses();
	cout << "\nwinter semester courses: ";
	wrequested_semester->print_semester_courses();
	//ελεγχω αν το μελος του μαθηματος που αναφερει σε ποιο εξαμηνο βρισκεται ανανεωθηκε μετα τη μετακινηση του
	cout << "\n\n";
	requested_course_pointer->print_data();

	/*προσθεση/ορισμος καθηγητη σε μαθημα απο τη γραμματεια*/
	cout << "\nsecretary assignes a proffessor to a course\n";
	secretary.define_course_proffessors(requested_proffessor_pointer, requested_course_pointer);
	cout << "\n checking if the assingment was succesfull\n";
	Proffessor* recent_proffessor_assignment = requested_course_pointer->find_proffessor(12345);
	cout << "checking if proffessor's id that was assigned in course is 12345: " << recent_proffessor_assignment->get_id() << "\n\n";
	//εφοσον ο καθηγητης εχει προστεθει στη δομη καθηγητων του μαθηματος πρεπει και το μαθημα να εχει προστεθει στη δομη μαθηματων του καθηγητη
	recent_proffessor_assignment->print_proffessor_courses();


	/*διαγραφη καθηγητη απο τη γραμματεια*/
	secretary.delete_course_proffessors(requested_proffessor_pointer, requested_course_pointer);
	recent_proffessor_assignment->print_proffessor_courses();
	//εφοσον ο καθηγητης εχει αφαιρεθει απο τη δομη καθηγητων του μαθηματος πρεπει και το μαθημα να εχει αφαιρεθει απο τη δομη μαθηματων του καθηγητη
	requested_course_pointer->print_course_proffessors();
	cout << '\n';

	//ελεγχω αν ο μαθητης μπορει να εγγραφει σε μαθημα που του επιτρεπεται
	cout << "student's enrolment check" << '\n';
	cout << "student's id: " << requested_student_pointer->get_id() << " that is about to enroll in the course which name is: " << requested_course_pointer->get_course_name() << '\n';
	requested_student_pointer->course_enrolment(requested_course_pointer, false);
	cout << "checking if the student got added in the course data structure\n";
	requested_course_pointer->print_course_students();

	//ελεγχω αν ο φοιτητης δεν μπορει να εγγραφη σε μαθημα που ειναι μεγαλυτερο του ετους 
	cout << "\nchecking if student's enrolment is denied\n";
	Student* requested_student_pointer1 = secretary.find_student(1900284);
	cout << "student's id: " << requested_student_pointer1->get_id();
	cout << "	student's current semester: " << requested_student_pointer1->get_semester_attendance() << '\n';
	cout << "semester that this course is offered: " << requested_course_pointer->get_semester_thatis_offered() << '\n';
	cout << "the student should not be allowed to enroll in this course" << '\n';
	requested_student_pointer1->course_enrolment(requested_course_pointer, false);
	requested_course_pointer->print_course_students();


	//ελεγχω αν ο καθηγητης μπορει να καταχωρησει βαθμο σε ενα μαθητη
	//επιπλεον χρησιμοποιω το αντικειμενο του καθηγητη για τη καταχωρηση βαθμου και οχι της γραμματειας 
	//γιατι γραφει στην εκφωνηση να μπορει ο καθηγητης να καταχωρησει βαθμο
	secretary.define_course_proffessors(requested_proffessor_pointer, requested_course_pointer);
	requested_proffessor_pointer->define_student_grade(8.5, requested_student_pointer, requested_course_pointer->get_course_name());
	cout << "\n\nstudent with name: " << requested_student_pointer->get_name() << ' ' << requested_student_pointer->get_surname();
	cout << " chosen courses: " ;
	requested_student_pointer->print_students_selected_courses();
	cout << "\n\n";

	Course* requested_course_pointer1 = secretary.find_course("domes");
	requested_proffessor_pointer->define_student_grade(8.5, requested_student_pointer1, requested_course_pointer1->get_course_name());
	cout << "student with name: " << requested_student_pointer1->get_name() << ' ' << requested_student_pointer1->get_surname();
	cout << " chosen courses: " ;
	requested_student_pointer1->print_students_selected_courses();


	// secretary.which_students_passedthis_course("domes"); αντιμετοπιζουμε seg fault ωστοσο εγινε προσπαθεια να υλοποιειθει της συναρτησεις τις εχω αφησει απλα δεν τις χρησιμοποιουμε

	requested_proffessor_pointer->courses_statistics("spring_semester");

	requested_student_pointer1->print_courses_grades("spring_semester");
	cout << '\n';
	requested_student_pointer1->print_courses_grades("winter_semester");
	cout << '\n';

	return 0;
}