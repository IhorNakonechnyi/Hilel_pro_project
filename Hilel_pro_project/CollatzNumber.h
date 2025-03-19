#ifndef COLLATZNUMBER_H
#define COLLATZNUMBER_H

#include<QPair>
#include<QHash>
#include<QString>
#include<unordered_map>


class CollatzNumber
{
private:
    int m_longestWay=0;
    int m_counter=0;
    bool isResult=false;

    const int m_rangeFrom=1;
    int m_rangeTo=1;

    short m_numberOfThreads=1;

    std::unordered_map<int,QPair<int,int>> CollatzeTree;


    void Preprocessing();
    void ThreadsManager();
    void Computing();
    QPair<int, int> LongestWay();



public:
    CollatzNumber()=delete;
    CollatzNumber(int rangeTo, short numberOfThreads):m_rangeTo(rangeTo), m_numberOfThreads(numberOfThreads){};
    ~CollatzNumber();

    CollatzNumber(const CollatzNumber &other)=delete;
    CollatzNumber(CollatzNumber &&other)=delete;
    CollatzNumber operator =(const CollatzNumber &other)=delete;
    CollatzNumber operator =(CollatzNumber &&other)=delete;

    QPair<int, int> GetLongestWay();

};

#endif // COLLATZNUMBER_H
