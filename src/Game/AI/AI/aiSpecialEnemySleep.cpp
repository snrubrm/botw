#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

SpecialEnemySleep::SpecialEnemySleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpecialEnemySleep::~SpecialEnemySleep() = default;

bool SpecialEnemySleep::isChangeable() const {
    return (isCurrentChild("起き上がる") && getCurrentChild()->isFinishedOrFailed()) ||
           ((isCurrentChild("待機") || isCurrentChild("横になる")) &&
            getCurrentChild()->isChangeable());
}

bool SpecialEnemySleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpecialEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    _54 = ksys::Timer(*mAwakeDelayTime_s, *mAwakeDelayTime_s);
    _52 = false;
    if (auto* awareness = mActor->getAwareness()) {
        _50 = awareness->sub_7100D7E964();
        _51 = awareness->_260[0] ? awareness->_260[0]->_50 : false;
        awareness->enable();
    }

    if (mActor->getRootAi()->getI() == 5) {
        changeChild("横になる");
        return;
    }

    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EAE4(0);
        awareness->sub_7100D7EAE4(2);
        if (!*mIsAwakenByHearing_s)
            awareness->sub_7100D7EAE4(1);
    }
    changeChild("睡眠");
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
