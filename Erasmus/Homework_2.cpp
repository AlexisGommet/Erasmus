#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

class CCarList
{
  public:

    const string & RZ ( void ) const{
      CRegister  a = new CRegister();   
      return (CRegister)a.getdata()[index][0];
    }

    bool AtEnd ( void ) const{
      CRegister a;
      if(a.getdata()[index + 1][1] == ""){
        return true;
      }
      return false;   
    }

    void Next ( void ){
      if(!AtEnd()){
        index++;
      }
    }

    void add ( string string ){
      carlistv.push_back(string);
    }

  private:
    int index = 0;
    vector<string> carlistv;
};

class CPersonList
{
  public:

    const string & Name ( void ) const{
      CRegister a;   
      return a.getdata()[index][1]; 
    }

    const string & Surname ( void ) const{
      CRegister a;
      return a.getdata()[index][2];
    }

    bool AtEnd ( void ) const{
      CRegister a; 
      if(a.getdata()[index + 1][0] == ""){
        return true;
      }
      return false;
    }

    void Next ( void ){
      if(!AtEnd()){
        index++;
      }
    }

    void add (){
      CRegister a;
      bool duplicate = false;
      for(int i = 0; i < (int)personlistv.size(); i++){
        if((personlistv[i][0] == a.getdata()[index][1]) && (personlistv[i][1] == a.getdata()[index][2])){
          duplicate = true;
        }
      }
      if(!duplicate){
        personlistv[index][0] = a.getdata()[index][1];
        personlistv[index][1] = a.getdata()[index][2];
      } 
    }

  private:
    int index = 0;
    vector<vector<string>> personlistv;
};

class CRegister
{
  public:
    CRegister  ( void ){}
    
    ~CRegister  ( void ){
      database.erase(database.begin(), database.end());
      database.shrink_to_fit();
    }

    CRegister  ( const CRegister & src ) = delete;
    CRegister & operator = ( const CRegister & src ) = delete;

    bool AddCar ( const string & rz, const string & name, const string & surname ){
      for(int i = 0; i < (int)database.size(); i++){
        if(database[i][0] == rz){
          return false;
        }
      }
      database.push_back(vector<string>());
      int size = database.size()+1;
      database[size].push_back(rz);
      database[size].push_back(name);
      database[size].push_back(surname);
      return true;
    }

    bool DelCar ( const string & rz ){
      bool found = false;
      int index;
      for(int i = 0; i < (int)database.size(); i++){
        if(database[i][0] == rz){
          found = true;
          index = i;
        }
      }
      if(!found){
        return false;
      }     
      auto it = database.begin();
      database.erase(it + index); 
      return true; 
    }

    bool Transfer ( const string & rz, const string & nName, const string & nSurname){
      bool carfound = false;
      int index;
      for(int i = 0; i < (int)database.size(); i++){
        if(database[i][0] == rz){
          carfound = true;
          index = i;
          if((database[index][1] == nName) && (database[index][2] == nSurname)){
            return false;
          }
        }
      }
      if(!carfound){
        return false;
      }
      DelCar(rz);
      AddCar(rz, nName, nSurname);
      return true;
    }

    CCarList ListCars ( const string & name, const string & surname ) const{
      CCarList carlist;
      for(int i = 0; i < (int)database.size(); i++){
        if((database[i][1] == name) && (database[i][2] == surname)){
          carlist.add(carlist.RZ());
        }
        carlist.Next();
      }
      return carlist;
    }

    int CountCars  ( const string & name, const string & surname ) const{
      int count = 0;
      for(int i = 0; i < (int)database.size(); i++){
        if((database[i][1] == name) && (database[i][2] == surname)){
          count++;
        }
      }
      return count;
    }

    CPersonList ListPersons( void ) const{
      CPersonList personlist;
      for(int i = 0; i < (int)database.size(); i++){
        personlist.add();
        personlist.Next();
      }
      return personlist;
    }

    vector<vector<string>> getdata(){
      return database;
    }

  private:
    vector<vector<string>> database;
};

#ifndef __PROGTEST__
bool checkPerson           ( CRegister    & r,
                             const string & name,
                             const string & surname,
                             vector<string> result )
{
  for ( CCarList l = r . ListCars ( name, surname ); ! l . AtEnd (); l . Next () )
  {
    auto pos = find ( result . begin (), result . end (), l . RZ () ); 
    if ( pos == result . end () )
      return false;
    result . erase ( pos );
  }
  return result . size () == 0;
}
int main ( void )
{
  CRegister b1;
  assert ( b1 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
  assert ( b1 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
  assert ( b1 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
  assert ( b1 . CountCars ( "John", "Hacker" ) == 1 );
  assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22" } ) );
  assert ( b1 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
  assert ( b1 . AddCar ( "XYZ-99-88", "John", "Smith" ) == true );
  assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
  assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
  assert ( b1 . CountCars ( "John", "Hacker" ) == 2 );
  assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22", "XYZ-11-22" } ) );
  assert ( b1 . CountCars ( "Peter", "Smith" ) == 0 );
  assert ( checkPerson ( b1, "Peter", "Smith", {  } ) );
  assert ( b1 . Transfer ( "XYZ-11-22", "Jane", "Black" ) == true );
  assert ( b1 . CountCars ( "Jane", "Black" ) == 1 );
  assert ( checkPerson ( b1, "Jane", "Black", { "XYZ-11-22" } ) );
  assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
  assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
  assert ( b1 . DelCar ( "XYZ-11-22" ) == true );
  assert ( b1 . CountCars ( "Jane", "Black" ) == 0 );
  assert ( checkPerson ( b1, "Jane", "Black", {  } ) );
  assert ( b1 . AddCar ( "XYZ-11-22", "George", "White" ) == true );
  CPersonList i1 = b1 . ListPersons ();
  assert ( ! i1 . AtEnd () && i1 . Surname () == "Hacker" && i1 . Name () == "John" );
  assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22" } ) );
  i1 . Next ();
  assert ( ! i1 . AtEnd () && i1 . Surname () == "Smith" && i1 . Name () == "John" );
  assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
  i1 . Next ();
  assert ( ! i1 . AtEnd () && i1 . Surname () == "White" && i1 . Name () == "George" );
  assert ( checkPerson ( b1, "George", "White", { "XYZ-11-22" } ) );
  i1 . Next ();
  assert ( i1 . AtEnd () );

  CRegister b2;
  assert ( b2 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
  assert ( b2 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
  assert ( b2 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
  assert ( b2 . AddCar ( "XYZ-11-22", "Jane", "Black" ) == false );
  assert ( b2 . DelCar ( "AAA-11-11" ) == false );
  assert ( b2 . Transfer ( "BBB-99-99", "John", "Smith" ) == false );
  assert ( b2 . Transfer ( "ABC-12-34", "John", "Smith" ) == false );
  assert ( b2 . CountCars ( "George", "White" ) == 0 );
  assert ( checkPerson ( b2, "George", "White", {  } ) );
  CPersonList i2 = b2 . ListPersons ();
  assert ( ! i2 . AtEnd () && i2 . Surname () == "Hacker" && i2 . Name () == "John" );
  assert ( checkPerson ( b2, "John", "Hacker", { "ABC-32-22" } ) );
  i2 . Next ();
  assert ( ! i2 . AtEnd () && i2 . Surname () == "Smith" && i2 . Name () == "John" );
  assert ( checkPerson ( b2, "John", "Smith", { "ABC-12-34" } ) );
  i2 . Next ();
  assert ( ! i2 . AtEnd () && i2 . Surname () == "Smith" && i2 . Name () == "Peter" );
  assert ( checkPerson ( b2, "Peter", "Smith", { "XYZ-11-22" } ) );
  i2 . Next ();
  assert ( i2 . AtEnd () );

  return 0;
}
#endif /* __PROGTEST__ */
