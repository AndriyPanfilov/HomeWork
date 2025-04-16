#include<iostream>

template <typename T>
class MyClass
{
private:
	T x;
	T y;
public:
	MyClass() {

		this->x = 5;
		this->y = 10;
		std::cout << "Consntructor MyClass  " << this << std::endl;
	}

	~MyClass()
	{
		this->x = 0;
		this->y = 0;
		std::cout << "Destructor MyClass " << this << std::endl;
	}

	void setX(T&x) { this->x = x; }
	void setX(T&& x) { this->x = x; }
	void setY(T&y) { this->y = y; }
	void setY(T&& y) { this->y = y; }
	T getX() { return x; }
	T getY() { return y; }
};

template <typename T>
class UniquePtr {
private:
	T* ptr;
public:
	//1. ��������� ����������� (ptr = nullptr);
	UniquePtr() noexcept{
		this->ptr = nullptr;
		std::cout << "Construntor UniquePtr() " << this << std::endl;
	}

	//����������� � ��������� *ptr
	UniquePtr(T* ptr) {		
		this->ptr = ptr;
		ptr = nullptr;
		std::cout << "Constructor UniquePtr(*ptr) "<<this<<std::endl;
	}

	//����������� � UniquePtr&& .
	UniquePtr(UniquePtr&& other) noexcept {		
		this->ptr = other.ptr;
		other.ptr = nullptr;
		std::cout << "Move Constructor UniquePtr " << this << std::endl;
	};

	
	//��������� ������������ ���������;
	UniquePtr(const UniquePtr&) = delete;

	~UniquePtr()
	{
		if(ptr)
		delete ptr;
		std::cout << "Destructor  " << this << std::endl;
	}


	//B�������� ��������� ������������ � ����������
	UniquePtr& operator = (const UniquePtr&) = delete;

	//�������� ������������ � �����������
	UniquePtr& operator = (UniquePtr&& other) noexcept
	{
		if (this != other)
		{
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}	

	//�������������� ���������* (������������ ��������� �� ��� �, ���� ����䳺 UniquePtr).
	T& operator* () {		
			return *ptr;
	}

	//�������������� ��������� -> (��������� ���������� ����� ���� �).
	T* operator->() noexcept{
			return ptr;
	}


	explicit operator bool() {
		return ptr!= nullptr;
	}
};

int main() {
	
//1.SCOPE:	������ ������������ �� �����������. ptr=nullptr;	
	{
		std::cout << "1. Default constructor (ptr=nullptr)\n";
		UniquePtr <MyClass<int>> A;
		std::cout << "Built obj_A()\n";
		std::cout<<"MSG obj_A: " << (A.operator bool() ? ("ptr is full->") : ("ptr is empty-> ")) << " operator bool = { " << A.operator bool() << " }" << std::endl;
	}

//2.SCOPE:	������ ������������ � ���������� *ptr;	
	{
		std::cout << "\n2. Constructor with parameter *ptr (ptr!=nullptr)\n";
		UniquePtr<MyClass<int>> B(new MyClass<int>);
		std::cout << "Built obj_B(*ptr)\n";
		std::cout << "MSG obj_B: " << (B.operator bool() ? ("ptr is full->") : ("ptr is empty->")) << " operator bool = { " << B.operator bool() << " }" << std::endl;
		std::cout<<"B->x =" << B->getX() << std::endl;
		std::cout << "B->y = " << B->getY() << std::endl;
	}

//3.SCOPE:	������ move ������������	
	{
		std::cout << "\n\n3. Move Construcotr\n";
		UniquePtr<MyClass<int>> A(new MyClass<int>);
		std::cout << "Built obj_A(*ptr)\n";
		std::cout << "MSG obj_A: " << (A.operator bool() ? ("ptr is full->") : ("ptr is empty->")) << " operator bool = { " << A.operator bool() << " }" << std::endl;
		std::cout << "A->x = " << A->getX() << std::endl;
		std::cout << "A->y =" << A->getY() << std::endl;

		//auto B = std::move(A); // ������ �����������
		auto B(std::move(A));	// ������ �����������
		std::cout << "Built obj_B (move(A))\n";
		std::cout << "MSG obj_B: " << (B.operator bool() ? ("ptr is full->") : ("ptr is empty->")) << " operator bool = { " << B.operator bool() << " }" << std::endl;
		std::cout << "B->x =";
		(B.operator bool() ? (std::cout<<B->getX()) : (std::cout<<" NULL ")) << std::endl;
		std::cout << "B->y = ";
		(B.operator bool() ? (std::cout << B->getY()) : (std::cout << " NULL ")) << std::endl;
		std::cout << "MSG obj_A: " << (A.operator bool() ? ("ptr is full->") : ("ptr is empty->")) << " operator bool = { " << A.operator bool() << " }" << std::endl;
		std::cout << "A->x =";
		(A.operator bool() ? (std::cout << A->getX()) : (std::cout << " NULL ")) << std::endl;
		std::cout << "A->y = ";
		(A.operator bool() ? (std::cout << A->getY()) : (std::cout << " NULL ")) << std::endl;
	}
//4. ��������������� ��������� *
	{
		std::cout << "\n\n4. Overloaded * operator\n";
		UniquePtr<MyClass<int>> B(new MyClass<int>);
		std::cout << "Built obj_B(*ptr)\n";
		std::cout << "*B.getX()_1  =  {" << (*B).getX() << "} \n";	//if ptr==nullptr x==5 �� �������;
		std::cout << "*B.getY()_1  =  {" << (*B).getY() << "} \n";		//if ptr==nullptr y==10 �� �������;
		
		(*B).setX(12);//�������������� x (rvalue);
		std::cout << "\n*B.getX(rv_12)_2  =  {" << (*B).getX() << "} \n";
		
		int val = 25;//������������� y (lvalue);
		(*B).setY(val);
		std::cout << "*B.getY(lv_25)_2  =  {" << (*B).getY() << "} \n";

//5. ���������������� ��������� bool
		std::cout << "\n5.Overloaded bool operator\n";
		std::cout<<"MSG obj_B " << (B.operator bool() ? ("ptr is full") : ("ptr is empty: ")) << " operator bool { " << B.operator bool() << " }" << std::endl;

//6. ���������������� ��������� = ��� T&&
		std::cout << "\n6.Overloaded = operator (move assignment operator)\n";
		auto A = std::move(B);
		std::cout << "Built obj_A= move(B)\n";
		std::cout <<"MSG obj_A " << (A.operator bool() ? (" ptr is full  ") : ("ptr is empty: ")) << "operator bool { " << A.operator bool() << " }" << std::endl;
		std::cout << "A->x =";
		(A.operator bool() ? (std::cout << A->getX()) : (std::cout << " NULL ")) << std::endl;
		std::cout << "A->y = ";
		(A.operator bool() ? (std::cout << A->getY()) : (std::cout << " NULL ")) << std::endl;

		std::cout <<"MSG obj_B " << (B.operator bool() ? ("Bptr is full  ") : ("ptr is empty: ")) << "operator bool { " << B.operator bool() << " }" << std::endl;
		std::cout << "B->x =";
		(B.operator bool() ? (std::cout << B->getX()) : (std::cout << " NULL ")) << std::endl;
		std::cout << "B->y = ";
		(B.operator bool() ? (std::cout << B->getY()) : (std::cout << " NULL ")) << std::endl;
//7. ���������������� ��������� ->
		std::cout << "\n7.Overloaded -> operator\n";
		std::cout << "x = {" << A->getX() << "} " << std::endl;
		std::cout << "� = {" << A->getY() << "} " << std::endl;
		std::cout << "\nX <- 35 "; A->setX(35);
		std::cout << "\nY<- 77"; A->setY(77);
		std::cout << "\nx = {" << A->getX() << "} " << std::endl;
		std::cout << "� = {" << A->getY() << "} " << std::endl;
	}	

	system("pause");
}