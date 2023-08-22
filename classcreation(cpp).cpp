#include<iostream>
using namespace std;
class car
{
	private:
		int phno;
	protected:
		double per;
	public:
		int roll;
		string name;
    car(int r,string me)
    {
       this->roll = r;
    	this->name = me;
	}
	 void display()
	{
		cout<<"roll"<<" "<<"name";
	}		
};
int main()
{
	car s1(1,"harsha");
	s1.display();
	return 0;	
}
