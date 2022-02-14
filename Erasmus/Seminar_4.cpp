#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

class CTimeStamp
{
public:

    int year, month, day, hour, minute, second;

    CTimeStamp (){}
        
    CTimeStamp (int year, int month, int day, int hour, int minute, int second){

        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute; 
        this->second = second;

    }
};
class CContact
{
public:

    CTimeStamp ctimestamp;
    int phone1, phone2;

    CContact (CTimeStamp ctimestamp, int phone1, int phone2){
        this->ctimestamp = ctimestamp;
        this->phone1 = phone1;
        this->phone2 = phone2;
    }
};
class CEFaceMask
{
private:

    vector<CContact> ContactList;

public:

    CEFaceMask& addContact (CContact ccontact){
        ContactList.push_back(ccontact);
        return *this;
    }

    vector<int> listContacts (int phone) const{

        vector<int> phonenumlist;
        for(int i = 0; i < (int)ContactList.size(); i++){

            bool duplicate = false;
            int p1 = ContactList[i].phone1;
            int p2 = ContactList[i].phone2;
            
            if(p1 != p2){
                for(int p = 0; p < (int)phonenumlist.size(); p++){
                    if((phonenumlist[p] == p2) || (phonenumlist[p] == p1)){
                        duplicate = true;
                    }                          
                }
                if(!duplicate){
                    if(phone == p1){       
                        phonenumlist.push_back(p2);
                    }
                    if(phone == p2){
                        phonenumlist.push_back(p1);                                                    
                    }
                }        
            }                                      
        }

        return phonenumlist;
    }

    vector<int> listContacts (int phone, CTimeStamp time1, CTimeStamp time2) const{

        vector<int> phonenumlist;

        for(int i = 0; i < (int)ContactList.size(); i++){

            bool duplicate = false;
            bool p1t = false;
            bool p2t = false;
            int p1 = ContactList[i].phone1;
            int p2 = ContactList[i].phone2;
            int y = ContactList[i].ctimestamp.year-2021;
            int mo = ContactList[i].ctimestamp.month;
            int d = ContactList[i].ctimestamp.day;
            int h = ContactList[i].ctimestamp.hour;
            int m = ContactList[i].ctimestamp.minute;
            int s = ContactList[i].ctimestamp.second;
            int y1 = time1.year-2021;
            int mo1 = time1.month;
            int d1 = time1.day;
            int h1 = time1.hour;
            int m1 = time1.minute;
            int s1 = time1.second;
            int y2 = time2.year-2021;
            int mo2 = time2.month;
            int d2 = time2.day;
            int h2 = time2.hour;
            int m2 = time2.minute;
            int s2 = time2.second;
            long int time,time1,time2 = 0;
            
            if(p1 != p2){
                for(int p = 0; p < (int)phonenumlist.size(); p++){
                    if((phonenumlist[p] == p2) || (phonenumlist[p] == p1)){
                        duplicate = true;
                    }                          
                }
                if(!duplicate){
                    if(phone == p1){       
                        p2t = true;
                    }
                    if(phone == p2){
                        p1t = true;                                                   
                    }
                }        
            }

            time = (((y*3.154)/1000)*(10*10*10*10*10*10*10))+(((mo*2.628)/1000)*(10*10*10*10*10*10))+(d*86400)+(h*3600)+(m*60)+(s);
            time1 = (((y1*3.154)/1000)*(10*10*10*10*10*10*10))+(((mo1*2.628)/1000)*(10*10*10*10*10*10))+(d1*86400)+(h1*3600)+(m1*60)+(s1);
            time2 = (((y2*3.154)/1000)*(10*10*10*10*10*10*10))+(((mo2*2.628)/1000)*(10*10*10*10*10*10))+(d2*86400)+(h2*3600)+(m2*60)+(s2);


            if(((time > time1) && (time < time2)) || ((time == time1) || (time == time2))){
                if(p1t){phonenumlist.push_back(p1);}                      
                else if(p2t){phonenumlist.push_back(p2);}
            }
        }
        return phonenumlist;  
    }
};    


#ifndef __PROGTEST__
int main ()
{
  CEFaceMask test;

  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
  assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
  assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
  return 0;
}
#endif /* __PROGTEST__ */
