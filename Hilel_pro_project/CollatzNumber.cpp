#include "CollatzNumber.h"

//------------------------PUBLIC METHODS--------------------------------------

CollatzNumber::CollatzNumber(int rangeTo, short numberOfThreads)
    :   m_rangeTo(rangeTo),
        m_numberOfThreads(numberOfThreads),
        m_edge((std::numeric_limits<unsigned long long>::max() - 1)/3),
        m_longestWay(1,1)
{
    //m_currentIndex.store(2);
    this->m_cache =  new std::atomic <unsigned long long>[rangeTo+1]{0};
    m_cache[1].store(0);
    m_cache[2].store(1);
};

CollatzNumber::~CollatzNumber()
{

};

void CollatzNumber::Calculating()
{
    auto startTime=std::chrono::high_resolution_clock::now();

    ThreadsManager(m_numberOfThreads);

    auto endTime=std::chrono::high_resolution_clock::now();
    timeOfCalculating=std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime);
};

bool CollatzNumber::Success()const
{
    return isFinished;
};

std::pair<int, unsigned long long> CollatzNumber::GetLongestWay()
{
    return {this->m_longestWay.first,
            this->m_longestWay.second};
};

std::chrono::milliseconds CollatzNumber::GetTime()const
{
     return timeOfCalculating;
};

//--------------------------PRIVATE--------------------------------------

void CollatzNumber::ThreadsManager(short threads)
{

    m_vecThreads.clear();

    int start=3;
    int end=m_rangeTo/m_numberOfThreads;


    for (size_t n = 0; n < threads; ++n) {
        m_vecThreads.emplace_back(std::thread(&CollatzNumber::TaskManager, this,start, end));
        if(n==threads+1)
            m_vecThreads.emplace_back(std::thread(&CollatzNumber::TaskManager, this,start, m_rangeTo));

        start=end+1;
        end+=m_rangeTo/m_numberOfThreads;
    }

    for (auto& thread : m_vecThreads) {
        if (thread.joinable())
            thread.join();
    }
};

void CollatzNumber::TaskManager(int start, int end)
{
    int currentNumber=start;
    while(currentNumber <= end)
    {
        if (isStopped.load())
            return;

        ++currentNumber;

        CalcCollatz(currentNumber, end);
    }

    if(currentNumber >= m_rangeTo)
        isFinished = true;
};

void CollatzNumber::CalcCollatz(int number, int end)
{
    unsigned long long tempNumber = number;
    unsigned long long tempWay = 0;
    std::vector<unsigned long long> localStack;
    localStack.reserve(100000);
    bool flag=false;

    {
        std::shared_lock<std::shared_mutex> lock(m_cacheMutex);
        if(m_cache[number].load() == std::numeric_limits<unsigned long long>::max()){
            return;
        }
    }

    while(tempNumber != 1)
    {        
        if(tempNumber <= m_rangeTo){
            std::shared_lock<std::shared_mutex> lock(m_cacheMutex);
            if (m_cache[tempNumber].load() != 0)
            {
                if(m_cache[tempNumber].load()==std::numeric_limits<unsigned long long>::max()){
                    flag = true;
                }
                tempWay = m_cache[tempNumber].load();
                break;
            }
        }

        localStack.push_back(tempNumber);

        if(tempNumber%2 == 0){
            tempNumber /= 2;}
        else if (tempNumber <= m_edge){
            tempNumber = tempNumber * 3 + 1;}
        else{
            flag = true;
            break;
        }    
    }

    if(localStack.empty())
        return;

    for (auto it = localStack.rbegin(); it != localStack.rend(); ++it)
    {
        if(flag){
            std::shared_lock<std::shared_mutex> lock(m_cacheMutex);
            m_cache[*it].store(std::numeric_limits<unsigned long long>::max());
            continue;
        }

        if(*it < m_rangeTo)
        {
            std::shared_lock<std::shared_mutex> lock(m_cacheMutex);
            m_cache[*it].store(tempWay+1);
        }

        ++tempWay;
    }

    {
        std::unique_lock<std::shared_mutex> writeLockResult(m_longestWayMutex);
        if(tempWay > m_longestWay.second)
        {
            m_longestWay.second = tempWay;
            m_longestWay.first = number;
        }
    }

};


//------------------------PUBLIC SLOTS--------------------------------------

void CollatzNumber::StopProcessing()
{
    isStopped.store(true);
    for (auto& thread : m_vecThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
};
