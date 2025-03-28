#ifndef COLLATZNUMBER_H
#define COLLATZNUMBER_H

#include<QString>
#include<QObject>
#include<QMetaObject>
#include<vector>
#include<atomic>
#include<utility>
#include<chrono>
#include<thread>
#include<shared_mutex>



class CollatzNumber : public QObject
{
    Q_OBJECT

private:
//base data
    const int m_rangeFrom=1;
    const int m_rangeTo=1;
    const short m_numberOfThreads=1;

//operating data
    std::vector<std::thread> m_vecThreads;
    const unsigned long long m_edge;
    //std::atomic<unsigned long long> m_currentIndex;
    std::atomic<unsigned long long>* m_cache= nullptr;
    std::shared_mutex m_cacheMutex;
    std::shared_mutex m_longestWayMutex;

//indication
    bool                isFinished  =   false;
    std::atomic<bool>   isStopped   =   false;

//results
    std::pair<int,unsigned long long> m_longestWay;
    std::chrono::milliseconds timeOfCalculating;

//methods
    void ThreadsManager(short threads);
    void TaskManager(int start, int end);
    void CalcCollatz(int number, int end);

public slots:
    void StopProcessing();

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
    bool Success()const;
    std::pair<int, unsigned long long> GetLongestWay();
    std::chrono::milliseconds GetTime()const;
};

#endif // COLLATZNUMBER_H
