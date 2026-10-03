#include "Game/AI/AI/aiGanonBeamOnFloor.h"
#include "Game/AI/aiUnk_71002C52DC.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

GanonBeamOnFloor::GanonBeamOnFloor(const InitArg& arg) : LastBossShootNormalArrowRoot(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
GanonBeamOnFloor::~GanonBeamOnFloor() { ; }

bool GanonBeamOnFloor::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void GanonBeamOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
    mFlags.set(Flag::Changeable);
    _2d4 = false;
    _2d5 = false;
}

void GanonBeamOnFloor::calc_() {
    LastBossShootNormalArrowRoot::calc_();

    if (!isCurrentChild("準備")) {
        if (auto* controller = mActor->getCharacterController()) {
            sub_71007377D4(controller, 0.98f);
            sub_7100738660(controller, 0.8f);
        }
        return;
    }

    const bool was_turning = _2d4;
    auto* as_list = mActor->getASList();
    if (as_list && as_list->x(41, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        sub_71003E4208();
        sub_7100740F1C(_298, mActor);
    }

    if (_2d4) {
        if (as_list &&
            !as_list->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            changeAS(mTurnAS_s.cstr(), true, 0, 0);
        }
    } else if (was_turning) {
        changeAS("Attack_Eye_Loop", true, 0, 0);
    }
}

void GanonBeamOnFloor::leave_() {
    LastBossShootNormalArrowRoot::leave_();
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.reset(0x200);
}

void GanonBeamOnFloor::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
    getStaticParam(&mKeepMinDist_s, "KeepMinDist");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mWalkAS_s, "WalkAS");
    getStaticParam(&mTurnAS_s, "TurnAS");
}

bool GanonBeamOnFloor::m38() {
    if (LastBossShootNormalArrowRoot::m38())
        return true;
    if (sub_71002C52DC(mActor, 0.5f))
        return false;
    return _a0 > 0;
}

}  // namespace uking::ai
