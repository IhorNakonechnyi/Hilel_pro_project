#ifndef COLLATZNUMBER_H
#define COLLATZNUMBER_H

#include<QString>
#include<vector>
#include<atomic>
#include<utility>
#include<chrono>
#include<limits>



class CollatzNumber
{
private:
    std::pair<std::atomic<unsigned long long>,std::atomic<unsigned long long>> m_longestWay;//first number, second way to 1

    std::vector<std::atomic<unsigned long long>> cache;

    short percentage=0;
    const int m_rangeFrom=1;
    int m_rangeTo;

    short m_numberOfThreads;

    std::chrono::milliseconds timeOfLastCalculating;

    void Preprocessing();
    void ThreadsManager();
    void Computing();
    void QueueManager();


public:
    CollatzNumber()=delete;
    CollatzNumber(int rangeTo, short numberOfThreads);
    ~CollatzNumber(){};

    CollatzNumber(const CollatzNumber &other)=delete;
    CollatzNumber(CollatzNumber &&other)=delete;
    CollatzNumber operator =(const CollatzNumber &other)=delete;
    CollatzNumber operator =(CollatzNumber &&other)=delete;

    std::pair<int, unsigned long long> GetLongestWay();
    std::chrono::milliseconds GetTime()const;

};

#endif // COLLATZNUMBER_H
