#include <iostream>
#include <windows.h>
using namespace std;

class ColoredBox{
private:

    int width,length,color ;
    char ch  ;
    char** arr ;
    static int biggest_area;

public:
    ColoredBox(int l , int w  , int c = 15, char x = '#' ) //constructor
    {
        width = w ;
        length = l ;
        color = c ;
        ch = x ;
        arr = new char *[length] ;

        for (int i = 0; i < length; i++) {
            arr[i] = new char [width] ;
        }

        for (int i = 0; i < length ; ++i) {
            for (int j = 0; j < width ; ++j) {
                *(*(arr + i) + j) = ch ;
            }
        }

        //calculate the biggest area
        if(length * width > biggest_area){
            biggest_area = length * width;
        }
    }

    //Function of set colors
    void SetColor(int ForgC)
    {
        WORD wColor;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        //We use csbi for the wAttributes word.
        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            //Mask out all but the background attribute, and add in the forgournd color
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        return;
    }

    // Destructor
    ~ColoredBox()
    {
        for (int i = 0; i < length ; ++i){
            delete[] arr[i];
        }
        delete[] arr;
        cout<<endl;
    }

    //displays functions:
    void display();
    void displayTransposed();
    void displayWider();
    void displayChess(int n) ;

    //setters & Getters
    void setColor (int c ){
        color = c ;
    }
    void setCh( char x )
    {
        ch = x ;
    }
    int getArea(){
        return width*length; // calculate the area
    }
    static int getMaxArea(){
        return biggest_area;
    }


}; int ColoredBox :: biggest_area =0 ; //initialization of static variable

// Function to display the colored box of character :
void ColoredBox ::display() {
    SetColor(color);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout << ch ;
        }
        cout << endl;
    }
    SetColor(15);
}

// Function to display Transposed of colored box :
void ColoredBox :: displayTransposed(){
    SetColor(color);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            cout<< ch  ;
        }
        cout <<endl;
    }
    SetColor(15);
}

//change the odd characters
void  ColoredBox :: displayChess(int n){
    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            if((i+j)%2 == 0)
            {
                SetColor(color);
                cout << ch ;
            }else
            {
                SetColor(n);
                cout << ch ;
            }
        }
        cout<<endl;
    }
    SetColor(15);
}

// widerization of colored box :
void ColoredBox :: displayWider(){
    SetColor(color);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout<< ch  << ' ';
        }
        cout<<endl;
    }
    SetColor(15);
}

//the driver of code :
int main() {
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea();
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea();
    delete cb2;
    return 0;
}