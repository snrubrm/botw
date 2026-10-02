#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BattleCloseMoveAction::BattleCloseMoveAction(const InitArg& arg) : BattleCloseMoveActionBase(arg) {}

bool BattleCloseMoveAction::init_(sead::Heap* heap) {
    return BattleCloseMoveActionBase::init_(heap);
}

void BattleCloseMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveActionBase::enter_(params);
}

void BattleCloseMoveAction::leave_() {
    BattleCloseMoveActionBase::leave_();
}

void BattleCloseMoveAction::calc_() {
    BattleCloseMoveActionBase::calc_();
}

ksys::act::Unk_7100d78e50* BattleCloseMoveAction::m33(int idx) {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_8.size() > idx)
        return ksys::act::sub_7100D78E30(&awareness->_8, idx);
    return nullptr;
}

bool BattleCloseMoveAction::m34(ksys::act::Unk_7100d78e50* entry) {
    return ksys::act::isPlayerProfile(&entry->_0.mLink) || ksys::act::isWeaponProfile(&entry->_0.mLink);
}

}  // namespace uking::action
