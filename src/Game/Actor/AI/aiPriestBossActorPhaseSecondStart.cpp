#include "Game/Actor/AI/aiPriestBossActorPhaseSecondStart.h"
#include "Game/Actor/aiUnk_710071E0D8.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PriestBossActorPhaseSecondStart::PriestBossActorPhaseSecondStart(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossActorPhaseSecondStart::~PriestBossActorPhaseSecondStart() = default;

bool PriestBossActorPhaseSecondStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossActorPhaseSecondStart::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710050E7E0();
}

void PriestBossActorPhaseSecondStart::calc_() {
    if (isCurrentChild("共通")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            actSetVisible(true, mActor);
            setFinished();
        }
    } else {
        sub_710050E7E0();
    }
}

void PriestBossActorPhaseSecondStart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossActorPhaseSecondStart::sub_710050E7E0() {
    ksys::act::ai::InlineParamPack params;
    auto* unit = sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (unit) {
        if (unit->isFlagOn(Unk_7102450fa8::Flag::_0) || unit->isFlagOn(Unk_7102450fa8::Flag::_4) ||
            unit->_38 == Unk_7102450fa8::Phase::_1) {
            setFinished();
            return;
        }

        sead::Vector3f pos;
        if (!unit->sub_7100719B78(&pos, unit->sub_7100719534(mActor)))
            return;

        params.addVec3(pos, "AppearPosition", -1);
        params.addVec3(getPlayerPosition(), "TargetPos", -1);
        *mEquipWeaponBufIndex_a = sub_710050EAD4();
        mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
    }
    changeChild("共通", &params);
}

s32 PriestBossActorPhaseSecondStart::sub_710050EAD4() {
    if (auto* unit = sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))) {
        unit->sub_7100719D5C(mActor);
    }
    if (!sead::GlobalRandom::instance()->getBool())
        return 1;
    auto* unit = sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (unit && !unit->sub_7100719B88(mActor))
        return 1;
    return 0;
}

void PriestBossActorPhaseSecondStart::loadParams_() {
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
