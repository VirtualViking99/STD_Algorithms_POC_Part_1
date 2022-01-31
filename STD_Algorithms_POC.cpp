// Algorithm: a set of steps used to solve a problem, similar
// to a cooking recipe
// 
// this often refers to techniques which are used to search or sort data
// or to solve a specific problem
// c++ stl defines lots of functions in <algorithm> include
// these implement classic as well as other useful routines
// 
// 
// 
// Why use Algorithms:
//		100+ algorithm functions and useful features
//		shorter clearer code
//		highly flexible - functionality can be customized
// 
// 
// 
// 
// Typical Algorithm:
// STL Algorithm is passed an iterator range
// 
// These specify which elements in the container will be processed
// by the algorithm
//		often begin(0 and end() to process the entire container
// 
// the algorithm will iterate over this range of elements and call a
// function on each element
// 
// the algrithm will return either
//		1. an iterator representing a particular element
//		2. a value containing the result of some operation on the elements
// 
// ------------------------------------------------------------------------------
//
// 
//  
// Landa Expressions: What if we could actually write the code inside the algorithm call
// 
// When we call an algorithm function, we have been using functors or function pointers,
// we pass an object of a functorial class or a function object, in order to customize
// the way the call actually processes the elements
// 
// modern C++ has lambda expressions
// these can be thought of as anonymous local(not global) functions, similat to "closures" in other 
// languages
// 
// When the compiler encounters a lambda expression, it will generate code that defines a functor
//		- this functor will have a unique name chosen by the compiler
//		- the function call operator of the functor will have the same body as the lambda expression
//		- it will have the same return type as the lambda expression
// 
// the compiler will add code to create a functor object of this class  at the point where the expression appears in the code
// 
// SYNTAX:
//		- lambda expressions are  anonymous and defined inline so you write the code where the expression is
//		- to define a lambda function we put [] for the function name
// 		- then we have a pair of () which contain the arguments just like a normal function
// 		- we then have a pair of {} which contain the actual code we want executed
// 		- we write the function arguments in the usual way
// 		- we write the function body the same as for an inline function 
//		- if we write this as a single statement that returns a value, the compiler will always be able to deduce the return type
// 
// 				[](int n) {return (n % 2 == 1);}	* return type deduced as bool 
// 		- the statement above causes the compiler to create a functor object
//		- the functor will be equivalent to is_odd
// 
// 
// 
// In c++ 11, the return type is only deduced if the lambda expression is a single statement that returns a value
//		- otherwise the return type is deduced as a void
// 
// For more complex problems, we need to provide a trailing return type
//		- [](int n) -> bool{
//		...
//		}
// 
// In later versions the return type is deduced automatically
//		- in cpp 14, it must be the same in all return paths
//		- in cpp 17, this is no longer required, so you can have one brach which returns in and one which returns string and 
//		the compiler will deduce the return type
// 



#pragma warning(disable: 4018)

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include<thread>
#include<chrono>

int global{ 99 };													//non-local variable
void findstring()
{
	//1. 
// string::find() returns an index
// std::find() returns an iterator
// some containers do not have the concept of an index
// 
// if  the character is not found, the algorithm will return the iterator for the "one after last" element
//
	std::string str{ "Hello World" };
	std::cout << "String: ";

	for (auto c : str)
		std::cout << c << ", ";
	std::cout << "\n";

	// search string for first occurence of 'l'
	auto res = std::find(std::cbegin(str), std::cend(str), 'l');

	// check if found
	if (res != std::cend(str)) {
		//access the result

		std::cout << "found a matching element at index: " << res - str.cbegin() << std::endl;
	}

	std::cout << " At this point in the string: ";
	for (auto it = res; it != str.cend(); ++it)
		std::cout << *it;
	std::cout << std::endl;
}


//for sorting() function, Define a predicate function 
bool is_shorter(const std::string& lhs, const std::string& rhs)
{
	return lhs.size() < rhs.size();		//predicate function has to return a bool
}




//for sorting(), next define a predicate as a functor
class is_shorter_2 {
public:
	// overload () operator
	// takes two strings as arguments
	// returns true/false depending on relative stirng length
	
	bool operator() (const std::string& lhs, const std::string& rhs)
	{
		return lhs.size() < rhs.size();
	}
};

void sorting()
{
	std::vector<std::string> names = { "William", "Benjamin", "Nick", "Stan", "Finguy", "Vassili" };

	std::wcout << "\n\n";

	std::cout << "Vector before sort(): ";

	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl << std::endl;


	// sort data in alphabetical order
	std::sort(std::begin(names), std::end(names));

	std::cout << "\nVector AFTER sort(): ";

	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl;
	std::cout << "The vector has been sorted alphabetically";

	// sort data, passing the function pointer as the predicate
	
	
	
	std::sort(std::begin(names), std::end(names), is_shorter);
	std::cout << "\nsorted by length: ";
	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl << std::endl;


}

void sorting_with_object()
{
	std::vector<std::string> names = { "Mark", "Pewdie", "KSI", "Cherno", "William", "Disney" };

	std::wcout << "\n";

	std::cout << "Vector before sort(): ";

	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl << std::endl;

	// use is_shorter to sort the data
	std::sort(std::begin(names), std::end(names), is_shorter_2());

	std::cout << "\n";

	
	std::cout << "sorted by length: ";
	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "Functor syntax can be slightly easier than a function pointer." << std::endl;

}

// Algorithms with predicates:
//	Many algorithms call a function on each element which returns bool
//		- find() calls  the == operator for each element to compare it to the target value
// 
// this is known as a "Predicate"
// 
// These algorithms allow us to supply our own predicate
// 
// We can pass a callable object as an optional extra argument to the algorithm call
// 
// 
// std::sort();
// 
// the sort algorithm works by comparing pairs of elements
// the comparison is called by calling the elements < operator on each pair of elements
// 
// sort() moves the smallest elements to the front and the largest to the rear of
// the container (by a clever choice of which pairs to compare, the sort can be very efficient.
// 
// 
// 
//
// --------------------------------------------------------------------------------------------
// 
// Algorithms with _if versions:
//		Many Algorithms have two versions
//			- the base version which takes a value argument
//			- An _if version which takes a predicate argument
// 
//		find() takes a value and searches for the first element with it's value
//		find_if() takes a predicate function and searches for the first element 
//	for which this predicate returns true
// 
//		we can use a functor to provide this predicate
// 
// 

// Functor for _if predicate explicit
class greater_than_5 {
public:
	bool operator () (const std::string& s) const {
		return (s.size() > 5);
	}
};

// Functor for _if predicate of any number
//suppose we want to look for any number of characters
// we do that by adding a state to our functor

class ge_n {
private:
	const int n;
public:
	ge_n(const int n) : n(n) {}

	bool operator () (const std::string& str) const {
		return str.size() > n;
	}
};



void _if_Finder()
{
	//manually coded example
	std::vector<std::string> names = { "AJ","Jeny", "Dax", "Wally", "Allice", "Michael", "Kim","Jo", "Nataliana","Rebecca-Jane"};

	std::cout << "Vector before sort(): ";

	for (auto name : names)
		std::cout << name << ", ";
	std::cout << std::endl << std::endl;


	greater_than_5 long_enough;
	for (auto name : names) {
		if (long_enough(name))
		{
			std::cout << "Loop: the first name with > 5 letters is: \"" << name << "\"\n";
			break;
		}
	}

	// Find the first object with more than 5 characters
	// pass a functor object as a predicate

	auto res = std::find_if(std::cbegin(names), std::cend(names), greater_than_5());

	//Display it: 
	if (res != std::cend(names))
		std::cout << "Algorithm: the first name with > 5 characters is \"" << *res << "\"\n";

	//Find first object with less than or equal to 5 characters
	auto res2 = std::find_if_not(std::cbegin(names), std::cend(names), greater_than_5());

	//Display it: 
	if (res2 != std::cend(names))
		std::cout << "Algorithm: the first name with <= 5 characters is \"" << *res2 << "\"\n";



	/*-------------------------------------------------------*/


	//When we call the algorithm with the state, we need to perovide an object and pass numebr into constructor 
	auto res3 = find_if(cbegin(names), cend(names), ge_n(8));	// 11 max for this example

	// Display it
	if (res3 != cend(names))
		std::cout << "The first word with > 5 characters is \"" << *res3 << "\"\n";


}



//Lambda Expressions
// Define a functor for the predicate
//


class is_odd
{
public:
	bool operator() (const int n) const { return (n % 2 == 1); }
};

std::vector<int> vec{ 3,1,4,1,5,9 };

void is_ODD()
{
	
	std::cout << "The Fector is as follows : ";
	for (auto vec : vec)
		std::cout << vec << ", ";
	std::cout << std::endl << std::endl;

	//pass the functor object
	auto odd_it = std::find_if(std::cbegin(vec), std::cend(vec), is_odd());

	//odd_it will be the iterator to the first odd element(if there is one)
	if (odd_it != cend(vec))
		std::cout << "First odd element is : " << *odd_it << std::endl;
}

void is_ODD_Lambda()
{
	std::cout << "The Fector is as follows : ";
	for (auto vec : vec)
		std::cout << vec << ", ";
	std::cout << std::endl << std::endl;

	//sort the data with a lambda expression as a predicate
	auto odd_it = std::find_if
	(
		std::cbegin(vec), std::cend(vec),
		[](int n) {								// lambda expression with one argument
		return (n % 2 == 1);					// return type deduced as a bool
	});


	//odd_it will be the iterator to the first odd element(if there is one)
	if (odd_it != cend(vec))
		std::cout << "First odd element is : " << *odd_it << std::endl;
}


//Practical lambda implementation demo

//case insensitive string comparison
//		Suppose we wrote a function that compares two string arguments and ignores case
// 
//				- bool equal_strings(const std::string& lhs, const std::string& rhs);
//					if(equal_strings(str1,str2))....
// 
//		We will rework this using a lambda function
//		We will use the equal()
// 
// equal() ALGORITHM: 
// equal() used to compare elements in two containers
//		bool cmp = std::equal(std::cbegin(ct1),std::cend(ct1),std::cbegin(ctd2),std::cend(ct2));
// 
// this iterates through each element in container 1, and compares it to the coresponding element in container 2
// it returns a false as soon as it encounters a mismatch
//		- if ct1 has more elements than ct2, it will always return false
//		- if ct2 has more elements than ct1, the extra elements are ignored
// 
// By default, the == operator is used to compare the elements
//		- if the containers are std::string, the comparison will be CASE SENSITIVE	
// 
// equal() ALGORITHM WITH PREDICATE:
// 
// There is an overload of the equal() algorithm which takes a predicate
//		bool cmp = std::equal(std::cbegin(ct1),std::cend(ct1),std::cbegin(ctd2),std::cend(ct2), func);
// This predicate will be called INSTEAD of the == operator
// 
// 
// We can use this to define what we mean by 'Equality"
//		ex: we want two string characters to be equal if the have the same after being converted to upper-case
// 
// We write a lambda expression for this predicate, which will be passed one character from each string as arguments.
// Then it will convert both characters to upper case.  It will return true if the converted characters are equal,
// otherwise it will return false.
// 
// [] (char lc, char rc){return toupper(lc) == toupper(rc);}
//

//define the predicate
bool equal_strings(const std::string& lhs, const std::string& rhs) {
	
	//call equal() algorithm  function using a lambda expression
	return equal(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs), std::cend(rhs),
		[](char lc, char rc) {return toupper(lc) == toupper(rc); }
	);

}

//define function to implement bool return
void equal_strings_test(const std::string& str1, const std::string& str2)
{
	std::cout << str1 << " and" << str2 << " are..." <<
		(equal_strings(str1, str2) ? "" : " NOT")
		<< " equal" << std::endl;
}




//----------------------------------------------------------
// Lambda Expressions and Capture
// 
// We can pass data t a lambda expressio through the arguments 
// if we have an algorithm call which uses a lambda expression then we can only pass elements of the 
// containter the algo is processing
// 
// we cant add more aguments because the signature of the expression MUST match the expectations of the algorithm
// 
// WHAT CAN WE DO?
// 
// A lambda expression HAS access to non-local variables
// it also has access to static variables in the same scope
// 
// By default, lambdas have very limmited acces to local variables, in the scope where the arguments is being called
//		- a lambda can access local variables which are references and were initialized with a constant expression
//		- a lambda can read- but not modify- local variables which are integers or enums  and were initialized
//			with a const expression
// 
//		- compilers often do not implement this propperly
// 
// We need to do something special, which is called "Capturing" of the local variable
// 
// int n{2}
// [n](int arg){return (n* arg);}		//captures the local variable n
// 
// int x{2},y{3};
// [x,y](int arg){ return (x * arg + y)	//captures the local variables x and y
//
void Capture_example()
{
	std::vector<std::string>words{ "a","of","words","With","collection", "Varying","lengths" };

	std::cout << "Vector before sort(): ";

	for (auto name : words)
		std::cout << "\"" << name << "\", ";
	std::cout << std::endl << std::endl;

	int n{ 5 };
	//find first element with more than  5 characters
	auto res = std::find_if(std::cbegin(words), std::cend(words),
		[n](const std::string& str) {return str.size() > n; });

	//display it
	if (res != std::cend(words)) {
		std::cout << R"(The first word which is more than )" << n << R"(letters long is ")";
		std::cout << *res << R"(")" << std::endl;
	}
}
//
// Implementation:
// A lambda with capture is implemented as a "functor with state": compiler will generate a class with private member variable
//		- the functor has a private data member which stores the variable
//		- it is initialized in the functors constructor
//		- the data member is available in the  operator() body
// 
// By Default, the captured variable is passed to the functors constructor by value
//		- the functor has it's own copy of the captured variable
//		- "Capture by value"
// 
// By default, the data member is 'const'
//		- the function call operator cannot modify its copy of the variable
// 
// 
// Suppose we want to find the index of the variable
//
void find_index_example()
{
	std::vector<std::string>words{ "a","of","words","With","collection", "Varying","lengths" };

	std::cout << "Vector before sort(): ";

	for (auto name : words)
		std::cout << "\"" << name << "\", ";
	std::cout << std::endl << std::endl;

	int n{ 5 }, idx{ -1 };	//this will generatea functor which has a const member to represent idx

	//find first element with more than  5 characters
	auto res = std::find_if(std::cbegin(words), std::cend(words),
		[n, idx](const std::string& str) mutable {++idx; return str.size() > n; });		//this generates an error because you can't increment a const data member, UNLESS you have the keyword mutable

	//display it
	if (res != std::cend(words)) {
		std::cout << R"(The first word which is more than )" << n << R"(letters long is ")";
		std::cout << *res << R"(")" << std::endl;
		std::cout << "the index is : " << idx << std::endl;
	}

	//the functor hasa copy of the captured variable, so when it's being modified, it was changing the copied variable.
}


// Captureby reference:
// 
//		There is a way to CHANGE a captured variable...
// before this point we saw that a labda can capture a local variable by value, which gives it a copy of the variable which is const uless mutable
// 
// However, To change a captured variable, we need to capture it by reference,
// to do this, we put & before the captured variable
// 
// int n{2};
// [&n](int arg) {return (n * arg);}		the n inside the body is going to be a reference to the local variable, so if lambda changes the variable, it will also effect the variable in local scope
//


void find_index_example_with_referenced_lambda_variable()
{
	// we were trying to find a word with more than 5 chars and it's index.
	// but we had a problem because we could only modify a copy of index variable...
	std::vector<std::string>words{ "a","of","words","With","collection", "Varying","lengths" };

	std::cout << "Vector before sort(): ";

	for (auto name : words)
		std::cout << "\"" << name << "\", ";
	std::cout << std::endl << std::endl;

	int n{ 5 }, idx{ -1 };	
	// if we now capture by reference [&idx], it's going to be a reference in lambda body
	// so when we increment in the body, it will also incremebt the local variable through reference
	// and when the find_if call returns, it should have the corect value
	//
	auto res = std::find_if(std::cbegin(words), std::cend(words),
		[n, &idx](const std::string& str) mutable {++idx; return str.size() > n; });

	if (res != std::cend(words)) {
		std::cout << R"(The first word which is more than )" << n << R"( letters long is ")";			//https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
		std::cout << *res << R"(")" << std::endl;
		std::cout << "the index in the vector is : " << idx << std::endl;						
	}

	//the functor hasa copy of the captured variable, so when it's being modified, it was changing the copied variable.
}

// IMPLEMENTATION: 
// lambda w/ capture by reference is also implemented as "functor with state", similar to capture by value, so compiler will
// generate def of class with function call operator and private data member to store the captured value
// but the member variable is a REFERENCE to the captured variable this time
// the captured variable will be passed to the functor constructor by reference 
//		-it's function call operator can modify captured variable through the reference




// IMPLICIT CAPTURE
// we can make a lambda capture ALL variables in scope
// 
// [=] will capture all variables by value
// [&] will capture all variables by reference
// 
// NOTE:
//		Capturing all variables by reference can make thecode difficult to maintain
//			-lambda could modify any variable in scope
//		Usually it's safer to capture by reference ONLY those variables it needs to modify
// 
// HERE'S HOW:
// [=, &x]		this will capture x by reference, and all other variables by value
// 
// [&,=a, =b]	this will capture a and b by value, and all others variables by reference
// 
// 
// LAMBDA FUNCTIONS AND MEMBER FUNCTIONS:
// 
// A Member function called with an extra argument which is a pointer to the class instance it is being called on
//		test.do_it();
//		// called as Test::do_it&test)
//		// &test is available in the member function body as "this"
// 
// In effect, "this" is a variable in the scope of the member function.... meaning we can capture it!!!!!!
// 
// WHEN WE HAVE A LAMBDA [] EXPRESSION INSIDE A MEMBER FUNCTION, IT IS ALLOWED TO CAPTURE "this"
// 
// This allows the lambda to access data members and call other member functions of the class, including private ones, and others
// 
// CAPTURING "this"
// 
//		- to capture the class object we put [this], [&] or [=]... [&this] and [=this] are not allowed
//		- These all capture the object by reference
// 

class Test {
public:
	int time{ 10 };									// data member
	void countdown() {								// member function which calls a lambda expression
		[this]() {									// capture class object by reference... unless you write [*this]() mutable
			if (time > 0)
				std::cout << time << std::endl;
			else if (time == 0)
				std::cout << "Liftoff" << std::endl;
			--time;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}();										// call Lambda expression, makes the compiler create object of class and call function operator
	}
};



// 
// in c++ 17 we also have [*this], this will capture the object by value
// if we implement this in the class above it will give an error about
// needing a modifiable value unless we add mutable after the lambda
// and round brackets and before the curly braces
// 
// When we call the member function under that circumstance, the 
// member function has a copy of the object and it modifies the copy but not the actual object
// 
// 

// ------------------------------------------------------------------------------//
// LAMBDA EXPRESSIONS AND PARTIAL EVALUATION
// 
// Storing lambdas
//		the main use for lambdas is for writing in place local functions in things like algo calls
//		However they are considered "first class objects", it's an object of the functor class that cimpiler generates
//		We can store them in variables and pass them to a function
// 
//			//store lambda function in a variable
//			auto is_longer_than = [max](const& string str) {return str.size() > max; }
// 
//			//pass this variable as the predicate
//			auto res = find_if(cbegin(words), cend(words),is_longer_than);
// 
//		We must use auto here, as it is impossible to know the type of the compiler generated functor
//

// 
//
void Storing_Lambdas() {
	std::vector<std::string>words{ "a","of","words","With","collection", "Varying","lengths" };

	std::cout << "Vector words: ";

	for (auto name : words)
		std::cout << "\"" << name << "\", ";
	std::cout << std::endl << std::endl;
	int max{ 5 };

	//Below is the previous code but with lambda expressions split out


	//Save the lambda expression in a variable
	auto is_longer_than = [max](const std::string str) {return str.size() > max; };

	//Pass the variable as the predicate
	auto res = std::find_if(std::cbegin(words), std::cend(words), is_longer_than);

	//Display it!
	if (res != std::cend(words)) {
		std::cout << R"(The first word which is more than )" << max << R"( letters long is ")";			//https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
		std::cout << *res << R"(")" << std::endl;

	}

}


// RETURNING A LAMNDA FROM A FUNCTION CALL:
// 
// We can also return a lambda expression from a function
// 
// //Function which returns a Lambda function
//		auto greeter(const string& salutation){
//			return [salutation] (const string& name){return salutation + ","s + name; }
// 
// Calling this function will return a lambda which captures "salutation"
// //store the lambda function in a variable
//		auto greet = greeter("Hello"s);
// 
// greet is a Lambda which takes a name as an argument and adds the salutation to it
//

//This is the function which returns a lambda function
auto greeter(const std::string& salutation) { 
	return [salutation](const std::string& name) {return salutation + ", " + name; }; 
}


// PARTIAL EVALUATION:
//		in partial evaluation, data is processed in stages
//			-ex: formatting pages in a document viewer
//			-reduces computation
//			-can make processing simpler
//			-many applications in AI, DB queries, scientific computing etc.
//		
//		We can use lambda expressions with capture to implement partial evaluation
// 
//	auto greeter() performs a partial evaluation
//		- it processes the salutation part of the greeting but not the name
//		- code which issues a greeting only has to provide the name
//		- it does not need to process the salutation or know how it is processed
//		- the salutation processing is written ONCE, instead of every time someone is greeted
// 
//	If you want a different greeting, you call greeter() with a different argument
// 
//

int main()
{
	//findstring();
	//sorting();
	//sorting_with_object();
	//-------------------------------------------------------//
	//_if_Finder();
	//-------------------------------------------------------//
	//is_ODD();
	//is_ODD_Lambda();

	//-------------------------------------------------------//
	//equal_strings_test("lambda", "Lambda");
	//equal_strings_test("lambda", "Lambdada");
	//-------------------------------------------------------//

																	// int main(){} == scope containing lambda expression
	//static int answer{ 42 };												// static variable in containing scope
	//const int one{ 1 };												// Local Variable in containing scope
	//const int& r_one{ one };										// Local variable in containing scope

	//[]() {															//start of lambda expression
	//	std::cout << global << std::endl;							//Lambda can access NON-Local Variables
	//	std::cout << answer << std::endl;							//lambda can access static variables
	//	//does not compile in 14 or 17, 
	//	//std::cout << one << std::endl;
	//	//std::cout << r_one << std::endl;							//an enclosing - function local variable cannot be referenced in a lambda body unless it is in the capture list
	//	
	//	
	//
	//};

	//Capture_example();
	//find_index_example();

	//-----------------------------------------------------------//
														
	//find_index_example_with_referenced_lambda_variable();

	//-----------------------------------------------------------//

	// We've got two classes, the one we defined below and the functor which the compiler will define
	//Test test;
	//for (int i = 0; i < 12; i++)
	//	test.countdown();
	

	//-----------------------------------------------------------//
	//Storing_Lambdas();
	
	//store lambda function in a variable
	auto greet = greeter("Welcome");

	//call the Lambda function
	std::cout << "Greeting: " << greet("students") << std::endl;
	std::cout << "Greeting: " << greet("James") << std::endl;
	//-----------------------------------------------------------//



	std::cin.get();

}