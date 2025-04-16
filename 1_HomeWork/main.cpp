

#include <iostream>
#include <vector>
#include <functional>


//Виводить myV на консоль
static void printV(const std::vector<int>& V)
{
	if (V.size() > 0) {
		std::cout << "print myV\n";
		for (auto& el : V)
			std::cout << el << ": ";
	}
	else std::cout << "myV is empty " << std::endl;
}

//Змінює значення el з непарного на парне. Якщо el ==0 -> el=1;
static void changeVector(int& el)
{
	if (el == 0) {
		std::cout << "[" << el << "] - undefined bahavior and will be change ";
		el++;
		std::cout << " -> new value[" << el << "] " << std::endl;

	}
	else if (el % 2) {
		std::cout << "[" << el << "] - this value is odd and will be changed ";
		el++;
		std::cout << " -> new value [" << el << "] " << std::endl;
	}
	else {
		std::cout << "[" << el << "] - this value is even  " << std::endl;
	}


}

//Перевіряє el на парність (true) або не парність (false);
static bool checkV(int el)
{
	if (el == 0) {
		std::cout << "[" << el << "] - undefined bahavior (false)";
		return false;
	}
	else if (el % 2) {
		std::cout << "[" << el << "] - this value is odd (false)";
		return false;
	}
	else {
		std::cout << "[" << el << "] - this value is even (true)";
		return true;
	}
}

//Змінює значення елементів vector<int> myV з не парних на парні. якщо el ==0, то змінюється el++ (непарний);
//За результатом роботи виводиться на консоль змінений myV
static void for_each(std::vector<int>& myV, void (*f)(int& el))
{
	if (myV.size() > 0) {
		for (auto& el : myV)
			f(el);

		printV(myV);
	}
	else std::cout << "myV is empty\n";

}

//Перевіряє елементи vector<int> myV на парність або не парність,
//якщо всі елементи myV парні - функція повертае true, інакще false;
static bool all(std::vector<int>& myV, std::function<bool(int)> p)
{
	int k = 0;
	if (myV.size() > 0) {

		for (auto& el : myV)
		{
			if (!p(el)) return  false;
			else std::cout << std::endl;
		}


	}
	else {
		std::cout << "myV is empty \n";
		return false;
	};

	return true;
}

//Підрахвує кількість парних елементів вектору та повертає цю кількість на консоль
static int count_if(std::vector<int>& myV, std::function<bool(int)> f)
{
	int count = 0;
	if (myV.size() > 0)
	{
		for (auto& el : myV) {
			if (f(el)) {
				count++;
				std::cout << std::endl;
			}
			else std::cout << std::endl;
		}
	}
	else std::cout << "myV is empty " << std::endl;

	std::cout << "true element in myVector is: ";
	return count;
}



int main()
{
	//std::vector<int> myV{};
	//std::vector <int>myV{ 0,0,0,0 };
	//std::vector <int> myV{ 2,4,6,8,10 };
	//std::vector<int> myV {1,2,3,5,7};	
	//std::vector<int> myV {0,-2,4,-6,-9};	
	std::vector<int> myV{ 0,1,3,7 };

	printV(myV);
	std::cout << std::endl << std::endl;


	//1. завдання void for_each(vector<int>&, &f())
	std::cout << "Task_1\n";
	for_each(myV, changeVector);
	std::cout << std::endl << std::endl;

	//2. завдання bool all(vector<int>&, &p())
	std::cout << "Task_2\n";
	if (all(myV, checkV))
		std::cout << "ALL vector myV has only EVEN (true) value  -> all() is TRUE " << std::endl;
	else
		std::cout << "\nall() is FALSE " << std::endl;

	std::cout << std::endl << std::endl;

	//3. завдання int count_if(vector<int>&, &f())
	std::cout << "Task_3\n";
	std::cout << count_if(myV, checkV);


	std::cout << std::endl;
	std::system("pause");
}