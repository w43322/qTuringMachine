#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include<QStringList>
#include<set>
#include<map>

#define QTM_OK 0
#define QTM_FINISHED 1
#define QTM_ERROR -1

using std::pair;
using std::tuple;
using std::set;
using std::map;
using std::make_pair;
using std::make_tuple;
using std::get;

typedef pair<QString,char> QC;
typedef tuple<QString,char,char> QCC;

class TuringMachine
{
private:
    set<QString>K;   //all status
    set<char>Sigma;  //all possible input char
    set<char>Gamma;  //all possible char
    map<QC,QCC>Delta;//trans function
    QString q0;      //starting status
    char B;          //retaining char
    set<QString>F;   //ending status
    QString sta;     //now status
    QString str;     //string
    int pos;         //reader position on string
public:
    TuringMachine(const QStringList &_K,
                  const QStringList &_Sigma,
                  const QStringList &_Gamma,
                  const QStringList &_Delta,
                  const QString &_q0,
                  const QString &_B,
                  const QStringList &_F,
                  const QString &_str="",
                  const int &_pos=1);
    QString Str();
    QString Sta();
    QString Pointer();
    int Step();
    void Reset(const QString &_str);
};

#endif // TURINGMACHINE_H
