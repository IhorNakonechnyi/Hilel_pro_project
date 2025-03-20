#ifndef COLLATZNUMBER_H
#define COLLATZNUMBER_H

#include<QPair>
#include<QHash>
#include<QString>
#include<unordered_map>


class CollatzNumber
{
private:
    QPair<int,int> m_longestWay;//first number, second way to 1
    //bool isResult=false;

    const int m_rangeFrom=1;
    int m_rangeTo=1;

    short m_numberOfThreads=1;

    std::unordered_map<int,int> CollatzeTree;
    QPair<int, int> LongestWay;

    //void Preprocessing();
    void ThreadsManager();
    void Computing();
    void QueueManager();


public:
    CollatzNumber()=delete;
    CollatzNumber(int rangeTo, short numberOfThreads):m_rangeTo(rangeTo), m_numberOfThreads(numberOfThreads){};
    ~CollatzNumber(){};

    CollatzNumber(const CollatzNumber &other)=delete;
    CollatzNumber(CollatzNumber &&other)=delete;
    CollatzNumber operator =(const CollatzNumber &other)=delete;
    CollatzNumber operator =(CollatzNumber &&other)=delete;

    QPair<int, int> GetLongestWay(){return LongestWay;};

};

#endif // COLLATZNUMBER_H
