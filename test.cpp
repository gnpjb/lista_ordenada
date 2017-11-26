#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void create_file(string file_name)
{
    ofstream file(file_name);
    file<<"a"<<endl<<"b"<<endl<<"c"<<endl<<"d"<<endl<<"e"<<endl<<"f"<<endl<<"g"<<endl<<"h"<<endl<<"i";
    file.close();
}
int main()
{
    string file_name="demo.txt";
    create_file(file_name);
    cout<<endl;
    string algo="random text";
    string::iterator algo_itr=algo.begin();
    char a;
    ifstream file(file_name);
    while(!file.eof()&&algo_itr!=algo.end())
    {
        a=file.get();
        if(*algo_itr>a)
            cout<<"alg>a"<<"   alg value="<<*algo_itr<<"   a value="<<a<<endl;
        if(*algo_itr<a)
            cout<<"alg<a"<<"   alg value="<<*algo_itr<<"   a value="<<a<<endl;
        if(*algo_itr==a)
            cout<<"alg==a"<<"   alg value="<<*algo_itr<<"   a value="<<a<<endl;
        algo_itr++;
        
    }
}
