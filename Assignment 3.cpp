#include <fstream>
#include <iostream>
#include<cstring>


using namespace std;

class FloatArray{
    protected:
        int size_; //the size of array
        float* arr_; //the dynamic array
        int counter_; //the counter
    public:
        FloatArray(int size){
            counter_ = 0 ;
            size_= size;
            arr_ = new float[size_];
        }
    // function that adds a float at the end of the array
        virtual void add(const float number){
            arr_[ counter_++ ] = number;
        }
	// overloading for insertion operator <<
        friend ofstream &operator<<(ofstream &output, const FloatArray &obj){
            output << obj.counter_ <<"|\t";
            for(int i = 0 ; i < obj.counter_; i++){
                output << obj.arr_[i] << "\t";
            }
            output << endl;
            return output;
        }
	// overloading for extraction operator >>
        friend ifstream &operator>>(ifstream &input, FloatArray &obj){
            for(int i = 0 ; i < obj.size_ ; i++){
                float number;
                input >> number;
                obj.add(number);
            }
            return input;
        }
	// FloatArray Destructor
        ~FloatArray(){
            delete[] arr_;
        }
};
// the class of the SortedArray
class SortedArray : public FloatArray{
    public:
        SortedArray(int size) : FloatArray(size) {}
    // function that adds a float at the right place in the array
        void add(const float number){
            int CHECK = 1;
            for (int i = counter_ ; i > 0; i--){ 
                if (number <= arr_[i - 1]){
                arr_[i] = arr_[i- 1];
                }
                else{
                    arr_[i] = number;
                    CHECK = 0;
                    break;
                }
            }
            if(CHECK) arr_[0] = number;
            counter_++;
        }
};
// the FrontArray class
class FrontArray:public FloatArray{
    public:
        FrontArray(int size) : FloatArray(size){}
    //function that adds a float at the front of the array.
        void add(const float number){
            arr_[ size_ - 1 - counter_++] = number;
        }


};
// the positiveArray class
class PositiveArray : public SortedArray{
    public :
        PositiveArray(int size) : SortedArray(size){}
    // function that adds a float to the array only if it’s a positive number
        void add(const float number){
            if(number > 0){
                SortedArray::add(number);
            }
        }
};
// the NegativeArray class
class NegativeArray : public SortedArray{
    public :
        NegativeArray(int size) : SortedArray(size) {}
    // function that adds a float to the array only if it’s a negative number
        void add(const float number){
            if(number < 0){
                SortedArray::add(number);
            }
        }
};

int main(){
    FloatArray* float_array[10];
    string name_of_input , name_of_output;
    // ask the user to name the input file 
    cout << "Enter the name of the file input : ";
    cin >> name_of_input;
    // ask the user to name the output file
    cout << "Enter the name of the output : ";
    cin >> name_of_output;

    ifstream file_input;
    file_input.open(name_of_input.c_str());

    ofstream file_output;

    for (int i = 0; i < 10; i++){
        string type_object;
        file_input >> type_object;
        int size;
        file_input >> size;
		// if conditions to determine the class
        if(type_object[0] == 'A'){
            float_array[i] = new FloatArray(size);
        }
        else if(type_object[0] == 'P'){
            float_array[i] = new PositiveArray(size);
        }
        else if(type_object[0] == 'N'){
            float_array[i] = new NegativeArray(size);
        }
        else if(type_object[0] == 'S'){
            float_array[i] = new SortedArray(size);
        }
        else if(type_object[0] == 'F'){
            float_array[i] = new FrontArray(size);
        }
        file_input >> *float_array[i];
    }
    file_input.close();

    file_output.open(name_of_output.c_str());
    for(int i = 0 ; i < 10 ;i++){
        file_output << *float_array[i];
        // Delete the array
        delete float_array[i];
        float_array[i] = NULL; 
    }
    file_output.close();

    return 0;
}

