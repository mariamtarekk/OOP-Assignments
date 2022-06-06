#include <iostream>
#include<string>
using namespace std;
// the item class
class item{
	private:
		int ID;
		string Name;
		int Quantity;
		float Price;
	public:
		static int id;
		// the default constructor
		item(){
			ID=id;
			id++;
			Name="";
			Quantity=0;
			Price=0;
		}
		// the parameterized constructor
		item(string n,int q,float p){
			Name=n;
			Quantity=q;
			Price=p;
		}
		// the copy constructor
		item(item &obj){
			Name=obj.Name;
			Quantity=obj.Quantity;
			Price=obj.Price;
		}
		//  setter functions 
		void setN(string n){
			Name=n;
		}
		void setQ(int q){
			Quantity=q;
		}
		void setP(float p){
			Price=p;
		}
		// getter functions
		string getN(){
			return Name;
		} 
		int getQ(){
			return Quantity;
		} 
		float getP(){
			return Price;
		} 
		int getI(){
			return ID;
		}
		// operator overloading
	bool operator==(item &obj){
		return Name==obj.Name;
	}
	void operator+=(const int quantity){
		Quantity+=quantity;
	}
	void operator-=(const int quantity){
		Quantity-=quantity;
	}
	friend ostream& operator<<(ostream&output ,const item& ob){
		 	output<<"the name of the item:"<<ob.Name<<endl;
			output<<"the quantity of the item:"<<ob.Quantity<<endl;
			output<<"the price of the item:"<<ob.Price<<endl;
			output<<"the id of the item:"<<ob.ID<<endl;
	}
	friend istream& operator>>(istream& input,item& ob){
		cout <<"Please enter the name of the item : ";
		input >> ob.Name;
		cout << "Please enter the price of the item : " ;
		input >> ob.Price ;
		cout << "Pleas enter the quantity of the item : " ;
		input >> ob.Quantity;
		return input;
	}
	
};
	int item::id=1;
	// the second class
class Seller{
	private:
		string name_;
		string email_;
		int maxItems_;
		item *items_;
	public:
		// parameterized constructor
		Seller(string name, string email ,int maxItems){
			name_=name;
			email_=email;
			maxItems_=maxItems;
			items_=new item[maxItems_];
		}	
		// add function
		bool add(item &obj){
			for(int i=0 ; i<maxItems_; i++){
				if(items_[i]==obj){
					items_[i]+=obj.getQ();
					return true;
				}
			}
			
			for(int i = 0 ; i < maxItems_ ; i++){
				if(items_[i].getN() ==""){ 
					items_[i].setN(obj.getN());
					items_[i].setP(obj.getP());
					items_[i].setQ(obj.getQ());
					return true;
				}
			}
			return false;
		}
		// sell function
		bool sell(string name , int quantity){
			for(int i =0 ; i < maxItems_ ; i++){
				if(name == items_[i].getN() ){
					if(quantity <= items_[i].getQ()){
						items_[i] -= quantity;
						return true;
					}
					else{
						cout << "There is only " << items_[i].getQ() <<"left for this item. ";
						return false;
					}
				}
			}	
			return true;		
		}	
		
		friend ostream& operator << (ostream& input , Seller &seller){
			cout << "the seller name : " << seller.name_ << endl ;
			cout << "the seller email : " << seller.email_ << endl;
		}
		// print function
		void print(){
			for(int i=0 ; i<maxItems_ ; i++){
				cout<<items_[i]<<endl;
			}
		}
		// Destructor
		~Seller(){
			delete [] items_;
		}
		// find my id function
		item findId(int id){
			item tmp;
			if(id >= 1 && id <= maxItems_){
				return items_[id - 1];
			}
			else{
				tmp.setN("Out Of Range ");
				return tmp;
			}
		}
};


// The main
int main(int argc, char** argv) {
	string n , email;
	int maxItems;
	cout << "Enter Your name : ";
	cin >> n ;
	cout << " Enter your email : ";
	cin >> email;
	cout << "Enter your Capcity : ";
	cin >> maxItems;
	Seller user(n , email ,maxItems);
    cout << "1. Print My Info." << endl
	   	 << "2. Add An Item. " << endl
		 << "3. Sell An Item. " <<endl
		 << "4. Print Items. " <<endl
		 << "5. Find an Item by ID." <<endl
		 <<"6. Exit" << endl; 

	bool flag = true ;
	while(true){
		int choice ;
		cout << " Please enter your choice : ";
		cin >> choice;
		
		if(choice == 1){
			cout << user;
		}
		if(choice == 2){
			item item;
			cin >> item;
			if(user.add(item)){
				cout << "Item added ." <<endl;
			}
			else{
				cout << "The capcity is Full ." << endl ;
			}
		}
		if(choice == 3){
			string name;
			int quantity;
			cout << "Enter the name of the item : ";
			cin >> name ;
			cout << "Enter the quantity of the item : ";
			cin >> quantity ;
			if(user.sell(name , quantity) ) {
				cout << "Item Sold" << endl;
			}
		}
		if(choice == 4){
			user.print();
		}
		if(choice == 5){
			int id ;
			cout << "Enter the id you want : ";
			cin >> id ;
			if(user.findId(id).getN() =="Out Of Ragne"){
				cout << "The id is not valid ." << endl;
			}
			else{
				cout << user.findId(id) ;
			}
		}
		if(choice == 6){
			flag = false;
		}	
	}
	cout << "Thank you ." << endl;
}