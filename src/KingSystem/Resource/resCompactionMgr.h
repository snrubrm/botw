#pragma once

#include <time/seadTickTime.h>

namespace ksys::res {

class CompactionMgr {
public:
    struct InitArg {};

    struct CalcArg {
        bool pause_compaction;
    };

    CompactionMgr();
    virtual ~CompactionMgr();

    bool init(const InitArg& arg);
    void stopCompactionIfTooLong(const CalcArg& arg);

private:
    sead::TickTime _8;
    sead::TickTime _10;
    bool _18 = false;
};

}  // namespace ksys::res
