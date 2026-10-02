#include "Game/AI/Behavior/behaviorCancelMessageSendToPartsBase.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::behavior {

CancelMessageSendToPartsBase::CancelMessageSendToPartsBase(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
CancelMessageSendToPartsBase::~CancelMessageSendToPartsBase() {
    ;
}

bool CancelMessageSendToPartsBase::m6(sead::Heap* heap) {
    return true;
}

void CancelMessageSendToPartsBase::m7() {}

void CancelMessageSendToPartsBase::m8() {
    if (*mIsEnter_s) {
        m14();
        sub_710062C280();
    }
}

void CancelMessageSendToPartsBase::m9() {
    if (*mIsLeave_s) {
        m14();
        sub_710062C280();
    }
}

void CancelMessageSendToPartsBase::loadParams() {
    getStaticParam(&mIsEnter_s, "IsEnter");
    getStaticParam(&mIsLeave_s, "IsLeave");
    getStaticParam(&mIsChangeChild_s, "IsChangeChild");
    getStaticParam(&mPartsName_s, "PartsName");
}

void CancelMessageSendToPartsBase::m11() {
    if (*mIsChangeChild_s) {
        m14();
        sub_710062C280();
    }
}

// NON_MATCHING: the original computes the name argument before `enemy + 0x1128` (should use lane1's
// inline Enemy::getActorPartsActor wrapper, which is on decomp but not on this branch yet)
void CancelMessageSendToPartsBase::sub_710062C280() {
    auto* sender = m15();
    if (!sender)
        return;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->_1128.getActorPartsActor(mPartsName_s);
        if (link.hasProc())
            sender->sub_710070DCC0(&link, true);
    }
}

}  // namespace uking::behavior
