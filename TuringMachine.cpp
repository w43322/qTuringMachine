#include "TuringMachine.h"

TuringMachine::TuringMachine(const QStringList &_K,
                             const QStringList &_Sigma,
                             const QStringList &_Gamma,
                             const QStringList &_Delta,
                             const QString &_q0,
                             const QString &_B,
                             const QStringList &_F,
                             const QString &_str,
                             const int &_pos)
{
    for(QString i:_K)
        K.insert(i);
    for(QString i:_Sigma)
        Sigma.insert(i[0].toLatin1());
    for(QString i:_Gamma)
        Gamma.insert(i[0].toLatin1());
    for(QString i:_Delta)
    {
        QStringList __Delta=i.split(QRegExp("(\\ )"));
        Delta.insert(make_pair(
                         make_pair(__Delta[0],__Delta[1][0].toLatin1()),
                         make_tuple(__Delta[2],__Delta[3][0].toLatin1(),
                                    __Delta[4][0].toLatin1())
                         ));
    }
    q0=_q0;
    B=_B[0].toLatin1();
    for(QString i:_F)
        F.insert(i);

    sta=q0;
    str=B+_str+B;
    pos=_pos;
}
QString TuringMachine::Str()
{
    return str;
}
QString TuringMachine::Sta()
{
    return sta;
}
QString TuringMachine::Pointer()
{
    QString res;
    for(int i=0;i<pos;++i)
        res+=' ';
    res+='^';
    return res;
}
int TuringMachine::Step()
{
    if(F.find(sta)!=F.end())
        return QTM_FINISHED;//finished
    auto it=Delta.find(make_pair(sta,str[pos].toLatin1()));
    if(it!=Delta.end())
    {
        sta=get<0>(it->second);
        str[pos]=get<1>(it->second);
        if(!str.endsWith(B))
            str+=B;
        switch(get<2>(it->second))
        {
        case 'R':++pos;break;
        case 'L':--pos;break;
        default:break;
        }
        return QTM_OK;//success
    }
    else
        return QTM_ERROR;//fail
}
void TuringMachine::Reset(const QString &_str)
{
    str=B+_str+B;
    pos=1;
    sta=q0;
}
