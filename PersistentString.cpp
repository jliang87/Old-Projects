//
//  PersistentString.cpp
//  PersistentString
//
//  Created by jack liang on 2013-09-26.
//  Copyright (c) 2013 jack liang. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <assert.h>

using namespace std;

struct ObjID
{
    int id;
    ObjID() {static int _id = 0; id = _id++;}
};

class PersistentString
{
public:
    PersistentString (const char * = "");
    PersistentString (const string &);
    PersistentString (const PersistentString &);
    ~PersistentString();
    
    PersistentString &operator=(const PersistentString &);
    bool operator==(const PersistentString &) const;
    bool operator==(const char *) const;
    bool operator==(const string &) const;
    //writer
    char &operator[](int);
    //reader 
    char operator[](int) const;
    PersistentString &Load();
    void Persist() const;
    bool isPalindrome() const;
    int GetLength() const;
private:
    int length;
    char *ptr;
    int id;
    string file;
    void setUp(const char *);
};



PersistentString::PersistentString(const char *s)
:length(s != 0 ? (int)strlen(s) : 0)
{
    setUp(s);
}


PersistentString::PersistentString(const PersistentString &s)
:length(s.length)
{
    setUp(s.ptr);
}


PersistentString::PersistentString(const string &s)
:length((int)s.size())
{
    setUp(s.c_str());
}


PersistentString::~PersistentString()
{
    Persist();
    delete [] ptr;
}


void PersistentString::setUp(const char *s)
{
    ptr = new char[length+1];
    if (length != 0)
        strcpy(ptr, s);
    else
        ptr[0] = '\0';
    
    struct ObjID obj;
    id = obj.id;
    time_t now = time(0);
    struct tm * t = localtime(&now);
    ostringstream o;
    o << id << (t->tm_year + 1900) << (t->tm_mon + 1) <<  t->tm_mday << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec;
    file = o.str();
}


PersistentString &PersistentString::operator=(const PersistentString &s)
{
    if (&s != this && strcmp(ptr, s.ptr) != 0)
    {
        length = s.length;
        if (length != 0)
            strcpy(ptr, s.ptr);
        else
            ptr[0] = '\0';
    }
    
    return *this;
}


bool PersistentString::operator==(const PersistentString &s) const
{
    return strcmp(ptr, s.ptr) == 0;
}


bool PersistentString::operator==(const char *s) const
{
    return strcmp(ptr, s) == 0;
}


bool PersistentString::operator==(const string &s) const
{
    return strcmp(ptr, s.c_str()) == 0;
}


char &PersistentString::operator[](int i)
{
    if (i < 0 || i > length-1)
    {
        cerr << "Index out of range!" << endl;
        exit(1);
    }
    return ptr[i];
}


char PersistentString::operator[](int i) const
{
    if (i < 0 || i > length-1)
    {
        cerr << "Index out of range!" << endl;
        exit(1);
    }
    return ptr[i];
}


PersistentString &PersistentString::Load()
{
    ifstream f(file, ios::in);
    if (!f)
    {
        cerr << "Unable to read from record!" << endl;
        exit(1);
    }
    
    ostringstream o;
    o << f.rdbuf();
    string s(o.str());
    
    delete [] ptr;
    length = (int)s.size();
    ptr = new char[length+1];
    if (length != 0)
        strcpy(ptr, s.c_str());
    else
        ptr[0] = '\0';
    
    return *this;
}


void PersistentString::Persist() const
{
    ofstream f(file,ios::out);
    if (!f)
    {
        cerr << "Unable to write to record!" << endl;
        exit(1);
    }
    
    f << ptr;
}


int PersistentString::GetLength() const
{
    return length;
}


bool PersistentString::isPalindrome() const
{
    string s(ptr);
    regex r("\\W+");
    s = regex_replace(s, r, "");
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    string sr = s;
    reverse(sr.begin(), sr.end());
    return s.compare(sr) == 0;
}



int main(int argc, const char * argv[])
{
    //c-style string constructor
    PersistentString a("racecar   racecar racecar ");
    //copy constructor
    PersistentString b(a);
    string s("this is not a palindrome");
    //c++ string constructor
    PersistentString c(s);
    
    a.Persist();
    b.Persist();
    c.Persist();
    assert(b==a);
    assert(a==b);
    
    b[0] = 'R';
    b[3] = 'E';
    b[8] = ',';
    assert (b.isPalindrome());
    assert (!c.isPalindrome());
    
    c[4] = 's';
    int l = c.GetLength();
    c[l-1] = 'g';
    assert(c=="thissis not a palindromg");
    string test("garbage");
    assert(!(c==test));
    c = a.Load() = b = b.Load();
    assert(c==b);
    assert(c==a);
    assert(b==a);
    assert(a==b);
}

