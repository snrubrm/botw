#include "Game/gameLastBossMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(LastBossMgr)

// The 0x71025c5de0 static (name from its address; the float tables and the 0x148 message id are
// filled by the TU's static initialiser 0x71006781f0). Only the message id is modelled so far.
struct Unk_71025C5DE0 {
    u8 _0[0x148];
    ksys::MesTransceiverId mId;
};
KSYS_VISIBILITY_HIDDEN Unk_71025C5DE0 sUnk_71025C5DE0;

// NON_MATCHING: the safe-array member is not value-initialised in the original (it zeroes
// 0x38..0x238 before constructing the links and zeroes the id block from 0x240).
LastBossMgr::LastBossMgr() : _560(0) {}

void LastBossMgr::clear() {
    mBossLink.reset();
    mMesTransceiverId = sUnk_71025C5DE0.mId;
    for (u32 i = 0; i < 32; ++i) {
        auto& link = mLinks[i];
        link.reset();
        mLinkIds[i] = sUnk_71025C5DE0.mId;
    }
}

// NON_MATCHING: two loop base registers are allocated the other way round (x24/x25).
LastBossMgr::~LastBossMgr() {
    clear();
}

void LastBossMgr::postCalc() {
    if (!mBossLink.hasProc())
        mMesTransceiverId = sUnk_71025C5DE0.mId;

    for (u32 i = 0; i < 32; ++i) {
        if (!mLinks[i].hasProc())
            mLinkIds[i] = sUnk_71025C5DE0.mId;
    }
}

void LastBossMgr::sub_7100677FFC(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    if (!mActorLink.hasProc())
        mActorLink.acquire(actor, false);
}

void LastBossMgr::sub_7100677F24(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    for (u32 i = 0; i < 32; ++i) {
        if (mLinks[i].hasProc() && mLinks[i].hasProcById(actor)) {
            mLinks[i].reset();
            mLinkIds[i] = sUnk_71025C5DE0.mId;
            break;
        }
    }
}

// NON_MATCHING: the slot loop compares the last index with `<= 31` in the original; clang folds our
// `i < 32` to a `#0x20` compare.
void LastBossMgr::sub_7100677E58(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    for (u32 i = 0; i < 32; ++i) {
        if (!mLinks[i].hasProc()) {
            mLinks[i].acquire(actor, false);
            mLinkIds[i] = *actor->getMesTransceiverId();
            break;
        }
    }
}

void LastBossMgr::sub_710067807C(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    if (mActorLink.hasProc() && mActorLink.hasProcById(actor))
        mActorLink.reset();
}

}  // namespace uking
