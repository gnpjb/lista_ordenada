#include<iostream>
#include<fstream>
#include<string>

using namespace std;





bool create_file(string file_name)
{
    char retry='y';
    ofstream file(file_name);
    while(!file.is_open()&&retry=='y')
    {
        file.open(file_name.c_str());
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
        file.close();
        return false;
    }
    file.close();
    return true;
}


streampos find_endl(string file_name,streampos line)
{
    ifstream file(file_name);
    file.seekg(line);
    file.ignore(1000,'\n');
    streampos final_line=file.tellg();
    file.close();
    return final_line;
}


bool file_exist(string file_name)
{
    ifstream file(file_name);
    if(file.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}










/*void append_name(string file_name,streampos line,string text)
{
    ofstream file(file_name,ios::app);//do a while(!eof) copy file to new_file;delete file;rename new_file
    if(!file.is_open())
    {
        cout<<endl<<"couldnt append"<<endl;
    }
    file.seekp(0,ios::beg);
    file.seekp(line);
    file<<endl<<text;
    file.close();
}*/









void append_name(string file_name,streampos line,string text)
{
    ofstream new_file;
    string temp_filename="temp.txt";
    bool initializing=true;
    bool appended=false;
    bool erase_original=false;
    fstream file(file_name);
    if(!file.is_open())
    {
        cout<<endl<<"couldnt append"<<endl;
        return;
    }
    file.seekg(0,ios::beg);
    file.seekp(0,ios::beg);
    if(file.eof())
    {
        file<<text;
    }
    while(true)
    {
        if(initializing==true)
        {
            create_file(temp_filename);
            new_file.open(temp_filename);
            if(!file.is_open())
            {
                cout<<"couldnt create temporary file";
                return;
            }
            erase_original=true;
            initializing=false;
        }
        if(file.eof()&&appended==true)
        {
            break;
        }
        if(file.eof()&&appended==false)
        {
            new_file<<text<<endl;
            break;
        }
        if(file.tellg()>line&&appended==false)
        {
            new_file<<text<<endl;
            appended=true;
            
        }
        else
        {
            string text_line;
            getline(file,text_line,'\n');
            new_file<<text_line<<endl;
        }
    }
    if(erase_original==true)
    {
        remove(file_name.c_str());
        rename(temp_filename.c_str(),file_name.c_str());
    }
    file.close();
    new_file.close();
    
}
















void delete_name(string file_name,streampos line)
{
    streampos final_line=find_endl(file_name,line);//while(!eof) if(!thing tested)copy file to new_file;else skip line; delete file;rename new_file
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



























streampos find_place_w(string file_name,string text)
{
    char retry='y';
    char cur_char;
    char last_pos_char;
    string::iterator str_itr=text.begin();
    streampos last_pos;
    bool end_search;
    int i_ignore=0;
    ifstream file(file_name.c_str());
    while(!file.is_open()&&retry=='y')
    {
        file.open(file_name.c_str());
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
    
    if(retry=='n'&&!file.is_open())
    {
        cout<<"closing program. file couldn't open for finding";
        return -1;
    }
    file.seekg(0,ios::beg);
    if(file.eof())
    {   
        file.close();
        return 0;
    }
    cur_char=file.get();
    while(true/*str_itr==*(text.end())*/)
    {
        cout<<cur_char<<int(cur_char)<<endl<<*str_itr<<int(*str_itr)<<endl<<endl;
        if((cur_char==10||cur_char==' ')&& end_search==false)
        {
            last_pos=file.tellg();
            file.close();
            return last_pos;
           
        }
        
        
            else if((*str_itr)>cur_char||end_search==false)
        {
            last_pos=file.tellg();
            file.ignore(1000,'\n'); //no se que estoy haciendo aca
            if(i_ignore!=0)
                file.ignore(i_ignore);
            cur_char=file.get();
            file.seekg(-1,ios::cur);
        }
        
        
        else if((*str_itr)==cur_char||end_search==false)
        {
            i_ignore++;
            str_itr++;
            last_pos=file.tellg();
            file.ignore(1000,'\n'); //no se que estoy haciendo aca
            file.ignore(i_ignore);
            cur_char=file.get();
            
        }
        
        else if((*str_itr)<cur_char||end_search==false)
        {
            file.seekg(last_pos);
            i_ignore++;
            str_itr++;
            file.ignore(i_ignore);
            cur_char=file.get();
            

        }
    }
    
    last_pos=file.tellg();
    file.close();
    return last_pos;
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

int main()
{
    char action='a';                                                                  //variables initiation
    string file_name="lista.txt";
    string text;
                                                            //fstream file(file_name);
    if(!file_exist(file_name))                                                             //if(!file.is_open()) if file failed to open, create new file
    {
        char create_new_file;
        cout<<endl<<"File failed to open.Do you wish to create a file?y/n"<<endl;
        cin>>create_new_file;                                                       
        if(!(create_new_file=='y'||create_new_file=='n'))
        {
            cout<<"invalid input"<<endl;
        }
        if(create_new_file=='y')
        {
            if(!create_file(file_name))
            {
                cout<<endl<<"failed to create file. closing program"<<endl;
                return 0;
            }
        }
        if(create_new_file=='n')
        {
            cout<<endl<<"failed to open file.closing program"<<endl;
            return 0;
        }
    }
    while(true)
    {
        action='a';
        while(true)    
        {   
            cout<<endl<<endl<<"action to execute:write(w),delete(d),exit(e),list(l)"<<endl;        //action to be taken
            action=cin.get();
            cin.ignore(10000,'\n');
            cin.clear();
            if(action=='w'||action=='d'||action=='e'||action=='l')
            break;
        }
        if(action=='e')
        {
            break;
        }
        if(action=='w')
        {
            cout<<endl<<"write name to add"<<endl;
            getline(cin,text,'\n');
            append_name(file_name,find_place_w(file_name,text),text);
            action='a';
            
        }
        if(action=='d')
        {
            return 0;
            
        }
        if(action=='l')
        {
            return 0;
        }
    }
    cout<<endl<<endl<<endl<<"closing program"<<endl;
}
