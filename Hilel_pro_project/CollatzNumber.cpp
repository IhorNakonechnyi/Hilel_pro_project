#include "CollatzNumber.h"

//------------------------PUBLIC METHODS--------------------------------------

CollatzNumber::CollatzNumber(int rangeTo, short numberOfThreads)
    :   m_rangeTo(rangeTo),
        m_numberOfThreads(1),
        m_edge((std::numeric_limits<unsigned long long>::max() - 1)/3),
        m_longestWay(1,1)
{
    m_currentIndex.store(2);

    m_cache = new std::atomic<unsigned long long>[m_rangeTo+1];
    for (int i = 0; i <= m_rangeTo; ++i) {
        m_cache[i].store(0);
    }
    m_cache[1].store(0);
};

CollatzNumber::~CollatzNumber()
{
    delete[] m_cache;
    m_cache = nullptr;
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
    return {this->m_longestWay.first.load(),
            this->m_longestWay.second.load()};
};

std::chrono::milliseconds CollatzNumber::GetTime()const
{
     return timeOfCalculating;
};

//--------------------------PRIVATE--------------------------------------

void CollatzNumber::ThreadsManager(short threads)
{/*
    for (auto& thread : m_vecThreads) {
        if (thread.joinable())
            thread.join();
    }
    m_vecThreads.clear();

    for (size_t n = 0; n < threads; ++n) {
        m_vecThreads.emplace_back(std::thread(&CollatzNumber::TaskManager, this));
    }

    for (auto& thread : m_vecThreads) {
        if (thread.joinable())
            thread.join();
    }*/
    TaskManager();
};

void CollatzNumber::TaskManager()
{
    while(true)
    {
        if (isStopped.load())
            return;

        int currentNumber = m_currentIndex.fetch_add(1);

        if(currentNumber >= m_rangeTo)
        {
            isFinished = true;
            return;
        }

        CalcCollatz(currentNumber);
    }


};

void CollatzNumber::CalcCollatz(int number)
{
    unsigned long long tempNumber = number;
    unsigned long long tempWay = 0;
    std::vector<unsigned long long> localStack;
    localStack.reserve(1000);

    while(tempNumber != 1)
    {
        if (m_cache[tempNumber].load() != 0 )
        {
            tempWay = m_cache[tempNumber].load();
            break;
        }

        localStack.push_back(tempNumber);

        if(tempNumber%2 == 0){
            tempNumber /= 2;}
        else if (tempNumber <= m_edge){
            tempNumber = tempNumber * 3 + 1;}
        else{
            break;
        }
    }

    for (auto it = localStack.rbegin(); it != localStack.rend(); ++it)
    {
        if(*it <= m_rangeTo){
            m_cache[*it].store(tempWay+1);
        }
        ++tempWay;
    }

    unsigned long long prevWay = m_longestWay.second.load();

    while (tempWay > prevWay && !m_longestWay.second.compare_exchange_weak(prevWay, tempWay));

    {
        //std::unique_lock<std::shared_mutex> writeLock(m_longestWayMutex);
        if(tempWay > m_longestWay.second.load())
        {
            m_longestWay.second.store(tempWay);
            m_longestWay.first.store(number);
        }
    }

};


//------------------------PUBLIC SLOTS--------------------------------------

void CollatzNumber::UpdateTextBox(int number, unsigned long long way)
{
    QString message = "Number: " + QString::number(number) + "\tWay: " + QString::number(way);

    emit UpdateUI(message);
};

void CollatzNumber::StopProcessing()
{
    isStopped.store(true);
    for (auto& thread : m_vecThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
};
