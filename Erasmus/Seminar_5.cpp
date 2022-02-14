#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;

public:
    // constructor, destructor

    CTime(){}

    CTime(int hours,int minutes){
        if((hours > 23) || (hours < 0) || (minutes > 59) || (minutes < 0)){
            throw invalid_argument("Invalid argument");
        }
        m_Hour = hours;
        m_Minute = minutes;
        m_Second = 0;
    }

    CTime(int hours,int minutes,int seconds){
        if((hours > 23) || (hours < 0) || (minutes > 59) || (minutes < 0) || (seconds > 59) || (seconds < 0)){
            throw invalid_argument("Invalid argument");
        }
        m_Hour = hours;
        m_Minute = minutes;
        m_Second = seconds;
    }

    // arithmetic operators

    CTime operator+(const int& seconds) const {
        CTime time;
        int total;
        total = ((this->m_Hour*3600) + (this->m_Minute*60) + (this->m_Second + seconds));
        total = total % 86400;
        if(total < 0){total = total + 86400;}                 
        time.m_Hour = (total / 3600) % 24;
        total = total % 3600;
        time.m_Minute = total / 60;
        total = total % 60;
        time.m_Second = total;         
        return time;
    }
    CTime operator+=(const int& seconds) const {
        CTime time;
        int total;
        total = ((this->m_Hour*3600) + (this->m_Minute*60) + (this->m_Second + seconds));
        total = total % 86400;
        if(total < 0){total = total + 86400;}                 
        time.m_Hour = (total / 3600) % 24;
        total = total % 3600;
        time.m_Minute = total / 60;
        total = total % 60;
        time.m_Second = total;        
        return time;
    }
    CTime operator-(const int& seconds) const {
        CTime time;
        int total;
        total = ((this->m_Hour*3600) + (this->m_Minute*60) + (this->m_Second - seconds));
        total = total % 86400;
        if(total < 0){total = total + 86400;}                 
        time.m_Hour = (total / 3600) % 24;
        total = total % 3600;
        time.m_Minute = total / 60;
        total = total % 60;
        time.m_Second = total;       
        return time;
    }
    int operator-(const CTime & time) const {
        int seconds,time1,time2;
        time1 = (this->m_Hour*3600)+(this->m_Minute*60)+(this->m_Second);
        time2 = (time.m_Hour*3600)+(time.m_Minute*60)+(time.m_Second);
        seconds = abs(time2 - time1);
        if(seconds > 43200){
            seconds = abs(seconds - 86400);
        }        
        return seconds;
    }
    CTime operator-=(const int& seconds) const {
        CTime time;
        int total;
        total = ((this->m_Hour*3600) + (this->m_Minute*60) + (this->m_Second - seconds));
        total = total % 86400;
        if(total < 0){total = total + 86400;}                 
        time.m_Hour = (total / 3600) % 24;
        total = total % 3600;
        time.m_Minute = total / 60;
        total = total % 60;
        time.m_Second = total;         
        return time;
    }
    CTime operator++() {
        this->m_Second = this->m_Second + 1;
        if(this->m_Second > 59){
            this->m_Minute++;
            this->m_Second = this->m_Second - 60;
            if(this->m_Minute > 59){
                this->m_Hour++;
                this->m_Minute = this->m_Minute - 60;
                if(this->m_Hour > 23){
                    this->m_Hour = this->m_Hour - 24;
                }
            }
        }        
        return *this;
    }
    CTime operator++(int) {
        this->m_Second = this->m_Second + 1;
        if(this->m_Second > 59){
            this->m_Minute++;
            this->m_Second = this->m_Second - 60;
            if(this->m_Minute > 59){
                this->m_Hour++;
                this->m_Minute = this->m_Minute - 60;
                if(this->m_Hour > 23){
                    this->m_Hour = this->m_Hour - 24;
                }
            }
        }        
        return *this;
    }
    CTime operator--() {
        this->m_Second = this->m_Second - 1;
        if(this->m_Second < 0){
            this->m_Minute--;
            this->m_Second = this->m_Second + 60;
            if(this->m_Minute < 0){
                this->m_Hour--;
                this->m_Minute = this->m_Minute + 60;
                if(this->m_Hour < 0){
                    this->m_Hour = this->m_Hour + 24;
                }
            }
        }        
        return *this;
    }
    CTime operator--(int) {
        this->m_Second = this->m_Second - 1;
        if(this->m_Second < 0){
            this->m_Minute--;
            this->m_Second = this->m_Second + 60;
            if(this->m_Minute < 0){
                this->m_Hour--;
                this->m_Minute = this->m_Minute + 60;
                if(this->m_Hour < 0){
                    this->m_Hour = this->m_Hour + 24;
                }
            }
        }        
        return *this;
    }

    // comparison operators

    bool operator<(const CTime time) {
        bool comp;
        int seconds,time1,time2;
        time1 = (this->m_Hour*3600)+(this->m_Minute*60)+(this->m_Second);
        time2 = (time.m_Hour*3600)+(time.m_Minute*60)+(time.m_Second);
        seconds = time1 - time2;
        if(seconds < 0){comp = true;}
        else{comp = false;}      
        return comp;
    }
    bool operator<=(const CTime time) {
        bool comp;
        int seconds,time1,time2;
        time1 = (this->m_Hour*3600)+(this->m_Minute*60)+(this->m_Second);
        time2 = (time.m_Hour*3600)+(time.m_Minute*60)+(time.m_Second);
        seconds = time1 - time2;
        if((seconds < 0) || (seconds == 0)){comp = true;}
        else{comp = false;}      
        return comp;
    }
    bool operator>(const CTime time) {
        bool comp;
        int seconds,time1,time2;
        time1 = (this->m_Hour*3600)+(this->m_Minute*60)+(this->m_Second);
        time2 = (time.m_Hour*3600)+(time.m_Minute*60)+(time.m_Second);
        seconds = time1 - time2;
        if(seconds > 0){comp = true;}
        else{comp = false;}      
        return comp;
    }
    bool operator>=(const CTime time) {
        bool comp;
        int seconds,time1,time2;
        time1 = (this->m_Hour*3600)+(this->m_Minute*60)+(this->m_Second);
        time2 = (time.m_Hour*3600)+(time.m_Minute*60)+(time.m_Second);
        seconds = time1 - time2;
        if((seconds > 0) || (seconds == 0)){comp = true;}
        else{comp = false;}      
        return comp;
    }
    bool operator==(const CTime time) {
        bool comp;
        if((this->m_Hour == time.m_Hour) && (this->m_Minute == time.m_Minute) && (this->m_Second == time.m_Second)){
            comp = true;
        }
        else{comp = false;}            
        return comp;
    }
    bool operator!=(const CTime time) {
        bool comp;
        if((this->m_Hour != time.m_Hour) || (this->m_Minute != time.m_Minute) || (this->m_Second != time.m_Second)){
            comp = true;
        }
        else{comp = false;}            
        return comp;
    }
    

    // in/out operators

    friend ostringstream &operator<<(ostringstream &os, const CTime time) {
        if(time.m_Hour < 10){
            os << "0" << time.m_Hour << ":"; 
        }
        else{os << time.m_Hour << ":";}
        if(time.m_Minute < 10){
            os << "0" << time.m_Minute << ":"; 
        }
        else{os << time.m_Minute  << ":";}
        if(time.m_Second < 10){
            os << "0" << time.m_Second; 
        }
        else{os << time.m_Second;}       
        return os;
    }
    friend bool operator>>(istringstream &is, CTime & time) {   
        string strh, strm, strs;
        for(int i = 0; i < (int)is.str().length(); i++){
            if(isdigit(is.str()[i])){
                if((i == 0) || (i == 1)){
                    strh += is.str()[i];
                }
                if((i == 3) || (i == 4)){
                    strm += is.str()[i];
                }
                if((i == 6) || (i == 7)){
                    strs += is.str()[i];
                }
            }else{is.setstate(ios::failbit);}
        }
        time.m_Hour = stoi(strh);
        time.m_Minute = stoi(strm); 
        time.m_Second = stoi(strs);       
        return true; 
    }    

    friend class ::CTimeTester;
};

CTime operator+(int i, CTime & time){
    return time+i;
}
CTime operator+(int i, const CTime & time){
    return time+i;
}  

#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test ( const CTime & time, int hour, int minute, int second )
    {
        return time.m_Hour == hour 
            && time.m_Minute == minute
            && time.m_Second == second;
    }
};

#include <cassert>
#include <sstream>

int main ()
{
    CTime a { 12, 30 };
    assert( CTimeTester::test( a, 12, 30, 0 ) );

    CTime b;
    std::istringstream input { "13:30:00" };
    assert( static_cast<bool>( input >> b ) );
    assert( CTimeTester::test( b, 13, 30, 0 ) );

    assert( b - a == 3600 );

    assert( CTimeTester::test( a + 60, 12, 31, 0 ) );
    assert( CTimeTester::test( a - 60, 12, 29, 0 ) );

    assert( a < b );
    assert( a <= b );
    assert( a != b );
    assert( !( a > b ) );
    assert( !( a >= b ) );
    assert( !( a == b ) );

    while ( ++a != b );
    assert( a == b );

    std::ostringstream output;
    assert( static_cast<bool>( output << a ) );
    assert( output.str() == "13:30:00" );

    assert( a++ == b++ );
    assert( a == b );

    assert( --a == --b );
    assert( a == b );

    assert( a-- == b-- );
    assert( a == b );

    return 0;
}
#endif /* __PROGTEST__ */
