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

typedef bool (*process_file_lines_function)(ifstream &, ofstream &, const string &);

bool process_file_lines(const string &file_name, const string &text, process_file_lines_function f)
{
  string temp_file_name = "temp.txt";
  ifstream original_file(file_name);
  ofstream new_file(temp_file_name);

  bool result = f(original_file, new_file, text);

  original_file.close();
  new_file.close();

  remove(file_name.c_str());
  rename(temp_file_name.c_str(), file_name.c_str());

  return result;
}

bool process_write_in_place(ifstream &original, ofstream &results, const string &text)
{
  bool written = false;

  for(string line; getline(original, line) && !written;)
  {
    int comparisson = line.compare(text);
    if (comparisson < 0)
    {
      results << line << endl;
    }
    else
    {
      written = true;
      results << text << endl << line << endl;
    }
  }

  for (string line; getline(original, line);)
  {
    results << line << endl;
  }

  if (!written)
  {
    results << text << endl;
  }

  return true;
}


bool process_delete_in_place(ifstream &original, ofstream &results, const string &text)
{
  bool deleted = false;

  for (string line; getline(original, line);)
  {
    int comparisson = line.compare(text);
    if (comparisson == 0)
    {
      deleted = true;
    }
    else
    {
      results << line << endl;
    }
  }

  return deleted;
}


int main()
{
  string file_name="lista.txt";
  char action='a';
  string text;
  while(true)
  {
    for(int i=0;i<10&&!file_exist(file_name);i++)
    {
      create_file(file_name);
    }
    if(!file_exist(file_name))
    {
      cout<<endl<<"couldnt create file.error 1"<<endl;
      return 0;
    }
    do
    {
      cout<<endl<<"what to do:write(w),delete(d),list(l) or exit(e)"<<endl;
      action=cin.get();
      cin.ignore(1000,'\n');
      cin.clear();
      if(!(action=='w'||action=='d'||action=='e'||action=='l'))
        cout<<"bad input";
    }
    while(!(action=='w'||action=='d'||action=='e'||action=='l'));

    if(action=='w')
    {
      cout<<"write word to add:"<<endl;
      cin>>text;
      cin.ignore(1000,'\n');
      cin.clear();
      process_file_lines(file_name, text, &process_write_in_place);
    }
    if(action=='d')
    {
      cout<<"word to delete:"<<endl;
      cin>>text;
      cin.ignore(1000,'\n');
      cin.clear();
      if(!process_file_lines(file_name, text, &process_delete_in_place))
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
