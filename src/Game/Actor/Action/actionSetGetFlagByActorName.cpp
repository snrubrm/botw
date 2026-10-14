#include "Game/Actor/Action/actionSetGetFlagByActorName.h"
#include "Game/gameItemUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SetGetFlagByActorName::SetGetFlagByActorName(const InitArg& arg) : SetFlag(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SetGetFlagByActorName::~SetGetFlagByActorName() {
    ;
}

bool SetGetFlagByActorName::init_(sead::Heap* heap) {
    return SetFlag::init_(heap);
}

void SetGetFlagByActorName::loadParams_() {
    SetFlag::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
}

// NON_MATCHING: epilogue scheduling (the bool mask of the SetFlag::oneShot_ result is placed before the frame
// restore in the original).
bool SetGetFlagByActorName::oneShot_() {
    const sead::SafeString names = sub_710073BB1C();
    sead::FixedSafeString<32> name;
    for (auto it = names.tokenBegin(","); names.tokenEnd(",") != it; ++it) {
        it.get(&name);
        if (ksys::act::hasTag(mActorName_d, name))
            return SetFlag::oneShot_();
    }
    return false;
}

const sead::SafeString& SetGetFlagByActorName::m32() {
    return _30;
}

void SetGetFlagByActorName::m33() {}

}  // namespace uking::action
