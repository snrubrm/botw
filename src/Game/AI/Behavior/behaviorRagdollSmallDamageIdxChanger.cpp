#include "Game/AI/Behavior/behaviorRagdollSmallDamageIdxChanger.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::behavior {

RagdollSmallDamageIdxChanger::RagdollSmallDamageIdxChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
RagdollSmallDamageIdxChanger::~RagdollSmallDamageIdxChanger() {
    ;
}

bool RagdollSmallDamageIdxChanger::m6(sead::Heap* heap) {
    return true;
}

void RagdollSmallDamageIdxChanger::sub_applyKey_() {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* handler = actor->_868) {
            _40 = handler->_c8;
            handler->sub_71006EE280(mKeyName_s);
        }
        _44 = true;
    }
}

void RagdollSmallDamageIdxChanger::sub_restoreKey_() {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* handler = actor->_868)
            handler->_c8 = _40;
    }
    _44 = false;
}

void RagdollSmallDamageIdxChanger::m7() {
    if (!*mIsChinkCheck_s)
        return;
    if (mActor->getASList()->x(5, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        if (_44)
            sub_restoreKey_();
    } else if (!_44) {
        sub_applyKey_();
    }
}

void RagdollSmallDamageIdxChanger::m8() {
    _44 = false;
    sub_applyKey_();
}

void RagdollSmallDamageIdxChanger::m9() {
    if (_44)
        sub_restoreKey_();
}

void RagdollSmallDamageIdxChanger::loadParams() {
    getStaticParam(&mIsChinkCheck_s, "IsChinkCheck");
    getStaticParam(&mKeyName_s, "KeyName");
}

}  // namespace uking::behavior
