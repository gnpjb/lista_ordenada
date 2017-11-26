#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool file_exist(string file_name)
{
    ifstream file(file_name);
    if(file.is_open())
    {
        file.close();
        return true;
    }
    else
        return false;
}


void create_file(string file_name)
{
    ofstream file(file_name);
    file.close();
    return;
}

bool list(string file_name)
{
    string text;
    ifstream file(file_name);
    if(!file.is_open())
        return false;
    while(!file.eof())
    {
        getline(file,text,'\n');
        cout<<text<<endl;
    }
    return true;
}

bool write_inplace(string file_name,string text)
{
    string new_file_name="temp.txt";
    string temp_text;
    bool written=false;
    int line=0;
    char curr_char='a';
    string::iterator text_itr=text.begin();
    ifstream file(file_name);
    ofstream new_file(new_file_name);
    if(!new_file.is_open())
    {
        remove(new_file_name.c_str());
        return false;
    }
    if(!file.is_open())
        return false;
    
    file.seekg(0,ios::beg);
    curr_char=file.get();
    file.seekg(0,ios::beg);
    while(!file.eof())
    {
        if(curr_char=='\n')
        {
            new_file<<text<<endl;
            written=true;
        }
        if(*text_itr>curr_char&&written==false)
        {   
            file.seekg(-(line),ios::cur);
            getline(file,temp_text,'\n');
            new_file<<temp_text<<endl;
            file.seekg(line,ios::cur);
            curr_char=file.get();
            file.seekg(-1,ios::cur);
        }
        if(*text_itr==curr_char&&written==false)
        {
            line++;
            //file.seekg(1,ios::cur);
            curr_char=file.get();
            file.seekg(-1,ios::cur);
        }
        if(*text_itr<curr_char&&written==false)
        {
            new_file<<text<<endl;
            written=true;
        }
        if(written==true)
        {
            file.seekg(-(line),ios::cur);
            while(!file.eof())
            {
                getline(file,temp_text,'\n');
                new_file<<temp_text<<endl;
            }
        }
    }
    if(file.eof()&&written==false)
    {
        new_file<<text<<endl;
    }
    remove(file_name.c_str());
    rename(new_file_name.c_str(),file_name.c_str());
    
    return true;
    
}










int main()
{
    string file_name="lista.txt";
    char action='a';
    string text;
    while(true)
    { for(int i=0;i<10&&!file_exist(file_name);i++)
        {
            create_file(file_name);
        }
        if(!file_exist(file_name))
        {
            cout<<endl<<"couldnt create file.error 1"<<endl;
            return 0;
        }
        do{
            cout<<endl<<"what to do:write(w),delete(d),list(l) or exit(e)"<<endl;
            action=cin.get();
            cin.ignore(1000,'\n');
            cin.clear();
            if(!(action=='w'||action=='d'||action=='e'||action=='l'))
                cout<<"bad input";
        }while(!(action=='w'||action=='d'||action=='e'||action=='l'));
        if(action=='w')
        {
            cout<<"write word to add:"<<endl;
            cin>>text;
            cin.ignore(1000,'\n');
            cin.clear();
            write_inplace(file_name,text);
        }
        if(action=='d')
        {
            cout<<"word to delete:"<<endl;
            cin>>text;
            cin.ignore(1000,'\n');
            cin.clear();
            if(true/*!delete_inplace(file_name)*/);
            {
                cout<<"couldnt delete";
            }
        }
        if(action=='l')
        {
            if(!list(file_name))
            {
                cout<<"couldnt list"<<endl;
            }
        }
        if(action=='e')
        {
            cout<<"closing program"<<endl;
            break;
        }
    }
}
