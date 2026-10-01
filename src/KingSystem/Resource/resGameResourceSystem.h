#pragma once

#include <heap/seadDisposer.h>
#include <time/seadTickTime.h>

namespace ksys::res {

// TODO: move to its own file once the remaining functions are decompiled
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

// Also known as game::ResourceSystem (?)
class GameResourceSystem {
    SEAD_SINGLETON_DISPOSER(GameResourceSystem)
    GameResourceSystem() = default;
    virtual ~GameResourceSystem();

public:
    struct InitArg {
        sead::Heap* heap;
    };

    bool init(const InitArg& arg);

    void calc();
    void pauseCompaction();
    void resumeCompaction();

private:
    CompactionMgr* mCompactionMgr = nullptr;
    bool mPauseCompaction = false;
};

class ScopedCompactionPauser {
public:
    ScopedCompactionPauser() { GameResourceSystem::instance()->pauseCompaction(); }
    ~ScopedCompactionPauser() { GameResourceSystem::instance()->resumeCompaction(); }
    ScopedCompactionPauser(const ScopedCompactionPauser&) = delete;
    ScopedCompactionPauser(ScopedCompactionPauser&&) = delete;
    auto operator=(const ScopedCompactionPauser&) = delete;
    auto operator=(ScopedCompactionPauser&&) = delete;
};

}  // namespace ksys::res
