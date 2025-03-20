#include "CollatzNumber.h"

//------------------------PUBLIC METHODS--------------------------------------
CollatzNumber::CollatzNumber(int rangeTo, short numberOfThreads)
{
    m_rangeTo           =   rangeTo;
    m_numberOfThreads   =   numberOfThreads;
};


std::pair<int, unsigned long long> CollatzNumber::GetLongestWay()
{
    auto startTime=std::chrono::high_resolution_clock::now();

    this->Computing();

    std::pair<int,unsigned long long> result;
    result.first=this->m_longestWay.first;
    result.second=this->m_longestWay.second;

    auto endTime=std::chrono::high_resolution_clock::now();
    timeOfLastCalculating=std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime);
    return result;
};

std::chrono::milliseconds CollatzNumber::GetTime()const
{
    return timeOfLastCalculating;
};


//------------------------PRIVATE METHODS--------------------------------------

void CollatzNumber::ThreadsManager()
{

};
void CollatzNumber::Computing()
{
    std::vector<unsigned long long> localStack;
    unsigned long long currentNumber=this->m_rangeFrom;

    while(currentNumber!=1)
    {
        if(currentNumber<=std::numeric_limits<unsigned long long>::max())
        {

        };
    }


};
void CollatzNumber::QueueManager()
{

};

