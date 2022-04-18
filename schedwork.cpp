

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper_function(int maxShifts, DailySchedule& sched, const AvailabilityMatrix& avail);
bool checker(size_t temp, size_t maxShifts);
bool Check_Availability(size_t x, DailySchedule& sched, size_t maxShifts, const AvailabilityMatrix& avail, size_t section);
bool atIndex(int& rows, DailySchedule& sched, int& columns);
bool booleanIndex(int& x, DailySchedule& sched, int& y);
bool CheckInvalid(int& x, DailySchedule& sched, int& y);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    vector<Worker_T> sched_vector;


    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    bool answer;

    for(size_t i =0; i < avail.size(); i++){
        sched.push_back(sched_vector);
        for(size_t j = 0; j < dailyNeed; j++){
        sched[i].push_back(-1);
        }
    }

    answer =  helper_function(maxShifts, sched, avail);
    return answer;
}

bool helper_function(int maxShifts, DailySchedule& sched, const AvailabilityMatrix& avail){
    int rows = 0;
    int columns = 0;
    bool flag; 

    if(atIndex(rows, sched, columns) == false){
        flag = true;
        return flag;
    }
    for(size_t i = 0; i < avail[0].size(); i++){
        if(Check_Availability(rows, sched,maxShifts, avail, i) == true){
            sched[rows][columns] = i;
            if(helper_function(maxShifts, sched, avail)){
                flag = true;
                return flag;
            }
            sched[rows][columns] = INVALID_ID;
        }
    }
    flag = false;
    return flag; 
}

bool Check_Availability(size_t x, DailySchedule& sched, size_t maxShifts, const AvailabilityMatrix& avail, size_t section){
    size_t temp = 0;
    bool flag = false;
    
    if(!avail[x][section]){
        flag = false;
    }
    else if(avail[x][section]){
        for(size_t i =0; i < sched.size(); i++){
            for(size_t j = 0; j < sched[0].size(); j++){
                if(sched[i][j] == section){
                    temp = temp + 1;
                }
            }
        }
        flag = checker(temp, maxShifts);
    }
    return flag;
}

bool atIndex(int& rows, DailySchedule& sched, int& columns){
    int& x = rows;
    int& y = columns;
    bool flag = booleanIndex(x, sched, y);
    return flag;
}

bool checker(size_t temp, size_t maxShifts){
    bool flag;
    if(temp < maxShifts){
        flag = true;
    }
    else if(temp >= maxShifts){
        flag = false;
    }
    return flag;
}

bool booleanIndex(int& x, DailySchedule& sched, int& y){
    for(x = 0; x < (int)sched.size(); x++){
        for(y = 0; y < (int)sched[x].size(); y++){
            bool flag = CheckInvalid(x, sched, y);
            if(flag == true){
                return flag;
            }
        }
    }
    return false;
}

bool CheckInvalid(int& x, DailySchedule& sched, int& y){
    if(sched[x][y]==INVALID_ID){
         return true;
    }
    return false;
}

















