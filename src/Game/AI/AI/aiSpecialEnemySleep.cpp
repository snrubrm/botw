#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

SpecialEnemySleep::SpecialEnemySleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpecialEnemySleep::~SpecialEnemySleep() = default;

// NON_MATCHING: the original gives the first SafeString temporary its own stack slot (frame 0x60)
bool SpecialEnemySleep::isChangeable() const {
    if (isCurrentChild("起き上がる")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return true;
    }
    return (isCurrentChild("待機") || isCurrentChild("横になる")) &&
           getCurrentChild()->isChangeable();
}

bool SpecialEnemySleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpecialEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SpecialEnemySleep::leave_() {
    if (isActorDeletedOrDeleting())
        return;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    if (_50) {
        awareness->sub_7100D7E9BC(0);
    } else {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->disable();
    }
}

void SpecialEnemySleep::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

void SpecialEnemySleep::m35() {
    if (_51) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
    sead::Vector3f pos;
    if (m39(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("待機", &pack);
    } else {
        changeChild("待機");
    }
}

}  // namespace uking::ai
