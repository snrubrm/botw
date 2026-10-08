#include "Game/AI/Action/actionEquipedRod.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"

namespace uking::action {

EquipedRod::EquipedRod(const InitArg& arg) : EquipedAction(arg) {}

EquipedRod::~EquipedRod() = default;

// NON_MATCHING: same stores; the original stores `_90` and `_94` separately (the typeinfo guard address load is scheduled
// between them) where ours merges them into one `stp`.
void EquipedRod::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
    _7c = 0.0f;
    _80 = 0.0f;
    _88 = nullptr;
    _84 = -1.0f;
    auto* actor = mActor;
    _90 = -1.0f;
    _94 = 0;
    _98 = 0;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor);
    if (weapon) {
        if (auto* rod = weapon->getParam()->getRes().mGParamList->getRod()) {
            _9c = rod->mChargeMagicInterval.ref();
            _a0 = rod->mChargeMagicNum.ref();
            _78 = rod->mMagicRange.ref();
        }
    }
}

bool EquipedRod::sub_7100111C48() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon)
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(weapon->getParentActor());
    return player && player->m296() == 1;
}

void EquipedRod::leave_() {
    EquipedAction::leave_();
}

void EquipedRod::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mMagicCreateYOffset_s, "MagicCreateYOffset");
    getStaticParam(&mMagicShootVelOffset_s, "MagicShootVelOffset");
    getStaticParam(&mIsAxisYTop_s, "IsAxisYTop");
    getStaticParam(&mIsCreateWeaponPosOffset_s, "IsCreateWeaponPosOffset");
    getStaticParam(&mCreatePosOffset_s, "CreatePosOffset");
    getStaticParam(&mAxisYAngle_s, "AxisYAngle");
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

void EquipedRod::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
