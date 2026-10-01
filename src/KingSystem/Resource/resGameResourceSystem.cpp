#include "KingSystem/Resource/resGameResourceSystem.h"

namespace ksys::res {

SEAD_SINGLETON_DISPOSER_IMPL(GameResourceSystem)

GameResourceSystem::~GameResourceSystem() {
    if (mCompactionMgr)
        delete mCompactionMgr;
    mCompactionMgr = nullptr;
}

bool GameResourceSystem::init(const InitArg& arg) {
    mCompactionMgr = new (arg.heap) CompactionMgr;
    CompactionMgr::InitArg mgr_arg;
    return mCompactionMgr->init(mgr_arg);
}

void GameResourceSystem::calc() {
    CompactionMgr::CalcArg arg;
    arg.pause_compaction = mPauseCompaction;
    mCompactionMgr->stopCompactionIfTooLong(arg);
}

void GameResourceSystem::pauseCompaction() {
    mPauseCompaction = true;
    CompactionMgr::CalcArg arg;
    arg.pause_compaction = mPauseCompaction;
    mCompactionMgr->stopCompactionIfTooLong(arg);
}

void GameResourceSystem::resumeCompaction() {
    mPauseCompaction = false;
    CompactionMgr::CalcArg arg;
    arg.pause_compaction = mPauseCompaction;
    mCompactionMgr->stopCompactionIfTooLong(arg);
}

}  // namespace ksys::res
