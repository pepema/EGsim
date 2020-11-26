#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H
#include "can_opener.h"
#include "cluster_updater.h"

class yourStuff : public QObject
{
    Q_OBJECT
public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);

private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame *const _frame);
    void readMyEngineFrame(const unsigned char *const _data);
    void timerEvent(QTimerEvent *) override;
    void SetIcons(__u8 data1, __u8 data2);

    //signals:
    //    void die();

private:
    size_t Counter;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;
    _icons icons;
};

#endif // YOUR_STUFF_H
