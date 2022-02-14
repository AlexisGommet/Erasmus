#ifndef __PROGTEST__
#include <cstring>
using namespace std;

class CLinkedSetTester;
#endif /* __PROGTEST__ */


class CLinkedSet
{
private:
    struct CNode
    {
        CNode * m_Next;

        const char * value;

        const char * Value () const {
            return value;
        }
    };

    CNode * m_Begin;

public:
    // default constructor

    CLinkedSet(){}

    // copy constructor

    CLinkedSet(CLinkedSet & list){
        CNode * head = this->m_Begin;
        CNode * lhead = list.m_Begin;
        if(lhead != NULL){
            head->value = lhead->value;
            head->m_Next = NULL;    
        }
        while(lhead->m_Next != NULL){
            lhead = lhead->m_Next;
            CNode * new_node = new CNode();
            new_node->value = lhead->value;
            new_node->m_Next = NULL;
            head->m_Next = new_node;
            head = head->m_Next;
        }
    }

    // operator=

    CLinkedSet operator=(CLinkedSet & list) {
        CNode * head = this->m_Begin;
        CNode * lhead = list.m_Begin;
        if(lhead != NULL){
            head->value = lhead->value;
            head->m_Next = NULL;    
        }
        while(lhead->m_Next != NULL){
            lhead = lhead->m_Next;
            CNode * new_node = new CNode();
            new_node->value = lhead->value;
            new_node->m_Next = NULL;
            head->m_Next = new_node;
            head = head->m_Next;
        }
        return *this;
    }

    // destructor

    ~CLinkedSet(){
        CNode * current = m_Begin;
        CNode * next;
        while( current != NULL ) {
            next = current->m_Next;
            delete current;
            current = next;
        }
    }
  
    bool Insert ( const char * value ){  
        CNode * new_node = new CNode(); 
        CNode * last = m_Begin;
        CNode * next = m_Begin->m_Next;
        new_node->value = value;  
        new_node->m_Next = NULL;  
        if (m_Begin == NULL){       
            m_Begin = new_node;  
            return true;  
        }  
        while (last->m_Next != NULL){ 
            last = last->m_Next;
            if(new_node->value == last->value){
                return false;
            } 
        }
        last->m_Next = new_node;
        last = m_Begin;
        next = m_Begin->m_Next;
        bool swap = true;
        const int size = Size();
        CNode * h ;
        while(swap){
            swap = false;
            h = m_Begin;
            for(int i = 0; i < (int)size; i++){               
                if((strcmp(last->value,next->value)) > 0){
                    swap = true;
                    CNode * tmp = next->m_Next;
                    CNode * tmp2 = last->m_Next;
                    next->m_Next = last;
                    last->m_Next = tmp;
                    next = next->m_Next;
                    last = last->m_Next;
                    if(i != 0){
                        h->m_Next = tmp2;
                        h = h->m_Next;
                    }         
                }       
            }
        }
        return true;  
    }
    
    bool Remove ( const char * value ){
        CNode * prev = m_Begin; 
        CNode * current = m_Begin->m_Next;
        if(prev->value == value){
            m_Begin = m_Begin->m_Next;
            delete prev;
            return true;
        }
        while(current != NULL){
            if(current->value == value){
                prev->m_Next = current->m_Next;
                delete current;
                return true;
            }
            prev = current;
            current = current->m_Next;
        }
        return false;
    }

    bool Empty () const {
        CNode * ptr = m_Begin;
        if(ptr == NULL){
            return true;
        }else{
            return false;
        }
    }

    size_t Size () const {
        CNode * ptr = m_Begin;
        int count = 0;
        while(ptr != NULL){
            count++;
            ptr=ptr->m_Next;
        }
        return count;
    }

    bool Contains ( const char * value ) const{
        CNode *ptr; 
	    ptr = m_Begin;
        while(ptr != NULL){
            if(ptr->value == value){
                return true;
            }
        ptr=ptr->m_Next;
        }
        return false;
    }

    friend class ::CLinkedSetTester;
};

#ifndef __PROGTEST__
#include <cassert>

struct CLinkedSetTester
{
    static void test0()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        assert( !x0 . Empty() );
    }

    static void test1()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CLinkedSet x1 ( x0 );
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        x1 = x0;
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

};

int main ()
{
    CLinkedSetTester::test0();
    CLinkedSetTester::test1();
    CLinkedSetTester::test2();
    return 0;
}
#endif /* __PROGTEST__ */
