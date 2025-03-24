#ifndef COLLATZNUMBER_H
#define COLLATZNUMBER_H

#include<QString>
#include<vector>
#include<atomic>
#include<utility>
#include<chrono>
#include<thread>


class CollatzNumber
{
private:
//base data
    const int m_rangeFrom=1;
    int m_rangeTo;
    short m_numberOfThreads;

//operating data
    std::atomic<std::pair<int,unsigned long long>> m_longestWay;
    std::vector<std::atomic<int>> m_cache;
    std::atomic<int> m_currentIndex=0;
    std::vector<std::thread> m_vecThreads;

//indication
    short percentageOfProcessing=0;
    bool isFinished=false;

//results
    std::pair<int, unsigned long long> result;
    std::chrono::milliseconds timeOfCalculating;

//methods
    void ThreadsManager(short threads);

public slots:
    void Computing();

public:
    CollatzNumber(int rangeTo, short numberOfThreads);
    ~CollatzNumber();

//banned
    CollatzNumber()=delete;
    CollatzNumber(const CollatzNumber &other)=delete;
    CollatzNumber(CollatzNumber &&other)=delete;
    CollatzNumber operator =(const CollatzNumber &other)=delete;
    CollatzNumber operator =(CollatzNumber &&other)=delete;

//core method
    void Calculating();

//interface
    std::pair<int, unsigned long long> GetLongestWay();
    std::chrono::milliseconds GetTime()const;
};

#endif // COLLATZNUMBER_H
