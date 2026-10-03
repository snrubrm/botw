#include "Game/AI/Action/actionSetGetFlag.h"
#include "Game/gameItemUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SetGetFlag::SetGetFlag(const InitArg& arg) : SetGetFlagBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SetGetFlag::~SetGetFlag() {
    ;
}

bool SetGetFlag::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlag::loadParams_() {
    SetGetFlagBase::loadParams_();
}

const sead::SafeString& SetGetFlag::m32() {
    return _20;
}

void SetGetFlag::m33() {}

bool SetGetFlag::oneShot_() {
    if (!ksys::act::hasOneTagAtLeast(mActor, sub_710073BB1C()))
        return false;
    return SetGetFlagBase::oneShot_();
}

}  // namespace uking::action
