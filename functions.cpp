#include<iostream>
#include<fstream>
#include<string>

using namespace std;








streampos find_endl(string file_name,streampos line)
{
    ifstream file(file_name);
    file.seekg(line);
    file.ignore(1000,'\n');
    streampos final_line=file.tellg();
    file.close();
    return final_line;
}











void append_name(string file_name,streampos line,string text)
{
    ofstream file(file_name,ios::app);
    file.seekp(line);
    file<<text;
    file.close();
}
















void delete_name(string file_name,streampos line)
{
    streampos final_line=find_endl(file_name,line);
    streampos current_line=line;
    ofstream file(file_name,ios::trunc);
    file.seekp(line);
    while(final_line>=current_line)
    {
        current_line +=1;
        file<<' ';
    }
    file.close();
}










bool create_file(string file_name)
{
    char retry='y';
    ofstream file(file_name);
    while(!file.is_open()&&retry!='n')
    {
        file.open(file_name);
        do
        {
            cout<<endl<<"Couldn't create file.Want to retry? y/n"<<endl;
            cin>>retry;
            if(!((retry=='y')||(retry=='n')))
                cout<<"invalid input"<<endl;
        }while(!((retry=='y')||(retry=='n')));
    }
    
    if(retry=='n'&&!file.is_open())
    {
        return false;
    }
    file.close();
}
















streampos find_place_w(string file_name,string text)
{
    char retry='y';
    char cur_char;
    string::iterator str_itr=text.begin();
    streampos last_pos;
    bool end_search;
    int i_ignore=0;
    ifstream file(file_name);
    while(!file.is_open()&&retry!='n')
    {
        
        file.open(file_name);
        if(!file.is_open())
        {
            do
            {
                cout<<"couldn't open file to execute search.retry?y/n";
                cin>>retry;
                if(!(retry=='n'||retry=='y'))
                {
                    cout<<endl<<"bad input"<<endl;
                }
            }while(!(retry=='n'||retry=='y'));
        }   
        
    }
    
    cur_char=file.get();
    
    if(retry=='n'&&!file.is_open())
    {
        cout<<"closing program";
        return -1;
    }
    while(*str_itr==*(text.end()))
    {
        if(cur_char==' '||cur_char=='\n')
        {
            return file.tellg();
        }
        
        
        if(*str_itr>cur_char||end_search==false)
        {
            last_pos=file.tellg();
            file.ignore(1000,'\n'); //no se que estoy haciendo aca
            file.ignore(i_ignore);
            cur_char=file.get();
        }
        
        
        if(*str_itr==cur_char||end_search==false)
        {
            i_ignore++;
            str_itr++;
            last_pos=file.tellg();
            file.ignore(1000,'\n'); //no se que estoy haciendo aca
            file.ignore(i_ignore);
            cur_char=file.get();
        }
        
        if(*str_itr<cur_char||end_search==false)
        {
            file.seekg(last_pos);
            i_ignore++;
            str_itr++;
            file.ignore(i_ignore);
            cur_char=file.get();
        }
    }
    return file.tellg();
}
    
    
    

