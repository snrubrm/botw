#include "Game/AI/Action/actionBattleCloseSlippedWalkBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BattleCloseSlippedWalkBase::BattleCloseSlippedWalkBase(const InitArg& arg)
    : BattleCloseActionWithAcc(arg) {}

BattleCloseSlippedWalkBase::~BattleCloseSlippedWalkBase() = default;

bool BattleCloseSlippedWalkBase::init_(sead::Heap* heap) {
    return BattleCloseActionWithAcc::init_(heap);
}

void BattleCloseSlippedWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseActionWithAcc::enter_(params);
}

void BattleCloseSlippedWalkBase::leave_() {
    BattleCloseActionWithAcc::leave_();
}

void BattleCloseSlippedWalkBase::loadParams_() {
    BattleCloseActionWithAcc::loadParams_();
}

void BattleCloseSlippedWalkBase::calc_() {
    BattleCloseActionWithAcc::calc_();
}

ksys::act::Unk_71024dc858* BattleCloseSlippedWalkBase::m33(int idx) {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_8.size() > idx)
        return ksys::act::sub_7100D78E30(&awareness->_8, idx);
    return nullptr;
}

bool BattleCloseSlippedWalkBase::m34(ksys::act::Unk_71024dc858* entry) {
    return ksys::act::isPlayerProfile(&entry->mLink) || ksys::act::isWeaponProfile(&entry->mLink);
}

}  // namespace uking::action
