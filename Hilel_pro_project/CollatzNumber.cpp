#include "CollatzNumber.h"

//------------------------PUBLIC METHODS--------------------------------------
CollatzNumber::CollatzNumber(int rangeTo, short numberOfThreads)
{
    m_rangeTo           =   rangeTo;
    m_numberOfThreads   =   numberOfThreads;

    m_currentIndex.store(rangeTo);

    m_cache.resize(rangeTo+1);
    for (auto& atom : m_cache)
    {
        atom.store(0);
    }
};

void CollatzNumber::Calculating()
{
    auto startTime=std::chrono::high_resolution_clock::now();

    ThreadsManager(this->m_numberOfThreads);
//TODO try catch

    auto endTime=std::chrono::high_resolution_clock::now();
    timeOfCalculating=std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime);
};

std::pair<int, unsigned long long> CollatzNumber::GetLongestWay()
{
    result.first=this->m_longestWay.load().first;
    result.second=this->m_longestWay.load().second;
    return result;
};

std::chrono::milliseconds CollatzNumber::GetTime()const
{
    return timeOfCalculating;
};

CollatzNumber::~CollatzNumber()
{

};

//------------------------PRIVATE METHODS--------------------------------------

void CollatzNumber::ThreadsManager(short threads)
{

    for (size_t n=0; n<threads; ++n){
        m_vecThreads.push_back(std::thread(&CollatzNumber::Computing,this));
    }

    for (auto&thread : m_vecThreads){
        thread.join();
    }

};

void CollatzNumber::Computing()
{
    unsigned long long currentNumber;
    std::vector<unsigned long long> localStack;

    int index=m_currentIndex.fetch_add(1);




};


