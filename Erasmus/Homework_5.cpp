#ifndef __PROGTEST__
#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

class CResult
{
public:
  CResult(const string &name,
          unsigned int studentID,
          const string &test,
          int result)
      : m_Name(name),
        m_StudentID(studentID),
        m_Test(test),
        m_Result(result)
  {
  }
  bool operator==(const CResult &other) const
  {
    return m_Name == other.m_Name && m_StudentID == other.m_StudentID && m_Test == other.m_Test && m_Result == other.m_Result;
  }
  string m_Name;
  unsigned int m_StudentID;
  string m_Test;
  int m_Result;
};
#endif /* __PROGTEST__ */

class CExam
{
public:

  CExam(){}

  static const int SORT_NONE = 0;
  static const int SORT_ID = 1;
  static const int SORT_NAME = 2;
  static const int SORT_RESULT = 3;

  bool Load(istringstream &cardMap){
    istringstream ss(cardMap.str());
    string count1 = cardMap.str();
    string str, str1;
    int count2 = 0;
    int lines = 0;
    int m = 0;
    vector<string> strlist;
    vector<string> cardidlist;
    vector<vector<string>> student;
    vector<int> idnum;
    int y = -1;
    ss.clear();
    for(int i = 0; i < (int)count1.length(); i++){
      if(count1[i] == '\n'){
        count2++;
      }
    }
    loop:if(getline(ss, str)) {
      bool add = false;
      if(lines == count2){
        goto endloop;
      }
      lines++;
      y++;
      strlist.push_back(str);
      istringstream ss1;
      ss1.clear();
      ss1.str(str);
      int x = 0;
      str.clear();
      while(getline(ss1, str1, ',')) {
        if(add){
          str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end());
          cardidlist.push_back(str1);
          x++;
        }
        else{add = true;} 
        str1.clear();
        m = x;
        if(ss1.eof()){
          idnum.push_back(m);
          goto loop;
        }    
      }
    }
    endloop:
    int x = 0;
    for(int i = 0; i < (int)strlist.size(); i++){
      vector<string> student2;
      int a = 0;
      string studentid = strlist[i].substr(0, strlist[i].find(":"));  
      string name = strlist[i].substr(strlist[i].find(":")+1, strlist[i].find_last_of(":")-studentid.length()-1);
      string cardid = strlist[i].substr(strlist[i].find_last_of(":")+1, strlist[i].find(",")-studentid.length()-name.length()-2);
      for(int i = 0; i < (int)liststudent.size(); i++){
        for(int y = 0; y < (int)liststudent[i].size(); y++){
          if((liststudent[i][0] == studentid) || (liststudent[i][y] == cardid)){
            return false;
          }
        }
      } 
      cardid.erase(remove(cardid.begin(), cardid.end(), ' '), cardid.end()); 
      student2.push_back(studentid);
      student2.push_back(name);
      student2.push_back(cardid);
      if(idnum[i] != 0){
        while(a < idnum[i]){
          student2.push_back(cardidlist[x]);
          a++;
          x++;
        }
      }
      student.push_back(student2);    
      index++;      
    }
    for(int i = 0; i < (int)student.size(); i++){
      liststudent.push_back(student[i]);
    }
    return true;
  }

  bool Register(const string &cardID, const string &test){
    bool cardidfound = false;
    bool studentfound = false;
    bool testfound = false;
    for(int i = 0; i < (int)tests.size(); i++){
      if(test == tests[i][0]){
        testfound = true;
      }
    }
    if(!testfound){
      vector<string> teststr;
      teststr.push_back(test);
      tests.push_back(teststr);
    }
    for(int i = 0; i < (int)liststudent.size(); i++){
      for(int y = 0; y < (int)liststudent[i].size(); y++){
        if(cardID == liststudent[i][y]){
          cardidfound = true;
          goto breakh;
        }
      }
    }
    breakh:
    if(!cardidfound){
      return false;
    }
    int indexstud = 0;
    for(int l = 0; l < (int)liststudent.size(); l++){
      for(int n = 0; n < (int)liststudent[l].size(); n++){
        if(cardID == liststudent[l][n]){
          indexstud = l;
        }
      }
    }
    for(int i = 0; i < (int)tests.size(); i++){
      if(tests[i][0] == test){
        for(int y = 0; y < (int)tests[i].size(); y++){
          for(int n = 0; n < (int)liststudent[indexstud].size(); n++){
            if(liststudent[indexstud][n] == tests[i][y]){
              studentfound = true;
              goto breakj;
            }        
          }        
        }
      }
    }
    breakj:
    if(studentfound){
      return false;
    }
    for(int i = 0; i < (int)tests.size(); i++){
      if(test == tests[i][0]){
        tests[i].push_back(cardID);
      }
    }
    return true;
  }

  bool Assess(unsigned int studentID, const string &test, int result){
    bool studentfound = false;
    int indexs;
    for(int i = 0; i < (int)tests.size(); i++){
      if(tests[i][0] == test){
        for(int y = 0; y < (int)tests[i].size(); y++){
          for(int j = 0; j < (int)liststudent.size(); j++){
            if(liststudent[j][0] == to_string(studentID)){
              for(int u = 0; u < (int)liststudent[j].size(); u++){
                if(liststudent[j][u] == tests[i][y]){
                  studentfound = true;
                  goto breakn;
                }
              }
            }
          }
        }
      }
    }
    breakn:
    if(!studentfound){return false;}
    studentfound = false;
    for(int i = 0; i < (int)liststudent.size(); i++){
      if(to_string(studentID) == liststudent[i][0]){
        studentfound = true;
        indexs = i;
        break;
      }
    }
    if(!studentfound){return false;}
    studentfound = false;
    for(int i = 0; i < (int)results.size(); i++){
      if((results[i].m_StudentID == studentID) && (results[i].m_Test == test)){
        studentfound = true;
        break;
      }
    }
    if(studentfound){return false;}
    string name = liststudent[indexs][1];
    results.push_back(CResult( name,studentID, test, result));
    return true;
  }

  list<CResult> ListTest(const string &testName, int sortBy) const{
    std::list<CResult> listtest;
    bool sort = true;
    bool sort1 = true;
    bool sort2 = true;
    switch(sortBy){
      case SORT_NONE:
        listtest = pushlist(testName, listtest);
      break;
      case SORT_ID:
        listtest = pushlist(testName, listtest);
        while(sort){
          auto it2 = listtest.begin();
          auto it1 = listtest.begin();
          it1++;
          sort = false;
          for(int i = 0; i < (int)listtest.size(); i++){
            if(i > 0){
              if(get(listtest, i-1).m_StudentID > get(listtest, i).m_StudentID ){
                swap(*it1, *it2);
                sort = true;
                it1++;
                it2++;
              }else{it1++;it2++;}
            } 
          }
        }
        break;
      case SORT_NAME:
        listtest = pushlist(testName, listtest);
        while(sort1){
          auto it2 = listtest.begin();
          auto it1 = listtest.begin();
          it1++;
          sort1 = false;
          for(int i = 0; i < (int)listtest.size(); i++){
            if(i > 0){
              string comp1 = get(listtest, i-1).m_Name;
              string comp2 = get(listtest, i).m_Name;
              int comp = 0;
              int index = 0;
              for(int j = 0; j < (int)comp1.length(); j++){
                if(comp1[j] == comp2[index]){
                  comp = 0;
                }else if(comp1[j] > comp2[index]){
                  comp = 1;
                  break;
                }else{comp = -1;break;}
                index++;                            
              }
              if(comp == 1){
                swap(*it1, *it2);
                sort1 = true;
                it1++;
                it2++;
              }else{it1++;it2++;}
            } 
          }
        }
        break;
      case SORT_RESULT:
        listtest = pushlist(testName, listtest);
        while(sort2){
          auto it2 = listtest.begin();
          auto it1 = listtest.begin();
          it1++;
          sort2 = false;
          for(int i = 0; i < (int)listtest.size(); i++){
            if(i > 0){
              if(get(listtest, i-1).m_Result < get(listtest, i).m_Result ){
                swap(*it1, *it2);
                sort2 = true;
                it1++;
                it2++;
              }else{it1++;it2++;}
            } 
          }
        }                   
        break;      
    }
    return listtest;
  }

  set<unsigned int> ListMissing(const string &testName) const{
    vector<string> registered;
    set<unsigned int> students;
    bool found = false;
    int x = 0;
    for(int i = 0; i < (int)tests.size(); i++){
      if(tests[i][0] == testName){
        for(int y = 0; y < (int)tests[i].size(); y++){
          if(x != 0){
            for(int p = 0; p < (int)liststudent.size(); p++){
              for(int u = 0; u < (int)liststudent[p].size(); u++){
                if(tests[i][y] == liststudent[p][u]){
                  registered.push_back(liststudent[p][0]);
                }
              }
            }            
          }
          x++;
        }
      }
    }
    for(int i = 0; i < (int)registered.size(); i++){
      found = false;
      for(int y = 0; y < (int)results.size(); y++){
        if((registered[i] == to_string(results[y].m_StudentID)) && (results[y].m_Test == testName)){
          found = true;
          break;
        }
      }
      if(!found){
        students.insert(stoi(registered[i]));
      }
    }
    return students;
  }

private:

  vector<vector<string>> liststudent;
  vector<vector<string>> tests;
  vector<CResult> results;
  int index = 0;

  std::list<CResult> pushlist(const string &testName, std::list<CResult> listtest) const {
    for(int i = 0; i < (int)results.size(); i++){
      if(results[i].m_Test == testName){
        listtest.push_back(results[i]);
      }
    }
    return listtest;
  }

  CResult get(std::list<CResult> _list, int _i) const {
    std::list<CResult>::iterator it = _list.begin();
    for(int i=0; i<_i; i++){
        ++it;
    }
    return *it;
  }

};

#ifndef __PROGTEST__
int main ( void )
{
  istringstream iss;
  CExam         m;
  iss . clear ();
  iss . str ( "123456:Smith John:er34252456hjsd2451451, 1234151asdfe5123416, asdjklfhq3458235\n"
      "654321:Nowak Jane: 62wtsergtsdfg34\n"
      "456789:Nowak Jane: okjer834d34\n"
      "987:West Peter Thomas:sdswertcvsgncse\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #1" ) );
  assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #2" ) );
  assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #1" ) );
  assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #3" ) );
  assert ( m . Register ( "sdswertcvsgncse", "PA2 - #1" ) );
  assert ( !m . Register ( "1234151asdfe5123416", "PA2 - #1" ) );
  assert ( !m . Register ( "aaaaaaaaaaaa", "PA2 - #1" ) );
  assert ( m . Assess ( 123456, "PA2 - #1", 50 ) );
  assert ( m . Assess ( 654321, "PA2 - #1", 30 ) );
  assert ( m . Assess ( 654321, "PA2 - #2", 40 ) );
  assert ( m . Assess ( 987, "PA2 - #1", 100 ) );
  assert ( !m . Assess ( 654321, "PA2 - #1", 35 ) );
  assert ( !m . Assess ( 654321, "PA2 - #3", 35 ) );
  assert ( !m . Assess ( 999999, "PA2 - #1", 35 ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_RESULT ) == (list<CResult>
  {
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_NAME ) == (list<CResult>
  {
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_NONE ) == (list<CResult>
  {
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 ),
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_ID ) == (list<CResult>
  {
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 )
  } ) );
  assert ( m . ListMissing ( "PA2 - #3" ) == (set<unsigned int>{ 123456 }) );
  iss . clear ();
  iss . str ( "888:Watson Joe:25234sdfgwer52, 234523uio, asdf234235we, 234234234\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "234523uio", "PA2 - #1" ) );
  assert ( m . Assess ( 888, "PA2 - #1", 75 ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "888:Watson Joe:2345234634\n" );
  assert ( !m . Load ( iss ) );

  assert ( !m . Register ( "ui2345234sdf", "PA2 - #1" ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "666:Watson Thomas:okjer834d34\n" );
  assert ( !m . Load ( iss ) );

  assert ( !m . Register ( "ui2345234sdf", "PA2 - #3" ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "666:Watson Thomas:jer834d3sdf4\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "ui2345234sdf", "PA2 - #3" ) );
  assert ( m . ListMissing ( "PA2 - #3" ) == (set<unsigned int>{ 555, 123456 }) );

  return 0;
}
#endif /* __PROGTEST__ */
