#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Resource/resHandle.h"

namespace ksys::act {

Schedule::Schedule(Actor* actor) : mActor(actor) {}

bool Schedule::allocRes(sead::Heap* heap) {
    mHeap = heap;
    if (!heap)
        return false;
    mResHandle = new (heap) res::Handle;
    return mResHandle != nullptr;
}

void Schedule::freeRes() {
    if (mHeap && mResHandle) {
        mResHandle->~Handle();
        mHeap->free(mResHandle);
        mResHandle = nullptr;
    }
}

void Schedule::reset() {
    _2f8 &= 2;
    sub_7100D192C0(nullptr, &sead::SafeString::cNullChar, false);
    if (auto* mgr = qst::Manager::instance())
        mgr->auto4(mActor);
    x_6(mActor);
    _2e8 = 0;
    _68 = sead::SafeString::cEmptyString;
    _78 = &sead::SafeString::cNullChar;
    _88 = sead::SafeString::cEmptyString;
    _98 = sead::SafeString::cEmptyString;
    _a8 = sead::SafeString::cEmptyString;
    _b8 = sead::SafeString::cEmptyString;
}

}  // namespace ksys::act
