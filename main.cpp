

using namespace std;


int main()
{
    char action=a;                                                                  //variables initiation
    string file_name="lista.txt";
    string text;
    fstream file(file_name);
    if(!file.is_open())                                                             //if file failed to open, create new file
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
            if(!create(file_name))
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
        do
            {                                                                               
                cout<<endl<<endl<<endl<<"action to execute:write(w),delete(d),exit(e),list(l)"<<endl        //action to be taken
                cin>>action;
                if(!(action=='w'||action=='d'||action=='e'||action=='l'))
                    cout<<endl<<"bad input"<<endl;
            }while(!(action=='w'||action=='d'||action=='e'||action=='l'))
        
        
        if(action=='e')
        {
            break;
        }
        if(action=='w')
        {
            cout<<endl<<"write name to add";
            getline(cin,text,' ');
            if(!streampos find_place_output=find_place_w(file_name,text))
            {
                cout<<"write error";
                return 0;
            }
            append(file_name,find_place_output);
            
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
