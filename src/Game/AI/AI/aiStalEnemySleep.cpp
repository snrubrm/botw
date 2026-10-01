#include "Game/AI/AI/aiStalEnemySleep.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

StalEnemySleep::StalEnemySleep(const InitArg& arg) : SpecialEnemySleep(arg) {}

StalEnemySleep::~StalEnemySleep() = default;

bool StalEnemySleep::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void StalEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getBase(_70, 0);
    _70.normalize();
    SpecialEnemySleep::enter_(params);
    _7c = isRootAiParamINot5();
}

void StalEnemySleep::leave_() {
    SpecialEnemySleep::leave_();
    _7c = false;
}

void StalEnemySleep::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mUseAwarenessWakeUp_s, "UseAwarenessWakeUp");
    getStaticParam(&mUseNoticeActiveWakeUp_s, "UseNoticeActiveWakeUp");
}

void* StalEnemySleep::m37(int* x) {
    if (!*mUseAwarenessWakeUp_s)
        return nullptr;
    return SpecialEnemySleep::m37(x);
}

bool StalEnemySleep::m39(sead::Vector3f* pos) {
    if (!pos)
        return false;
    pos->set(_70);
    return true;
}

}  // namespace uking::ai
