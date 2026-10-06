#include "Game/AI/Action/actionSwarmLevelFlyMove.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SwarmLevelFlyMove::SwarmLevelFlyMove(const InitArg& arg) : LevelFlyMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwarmLevelFlyMove::~SwarmLevelFlyMove() {
    ;
}

bool SwarmLevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMoveBase::init_(heap);
}

void SwarmLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMoveBase::enter_(params);
}

void SwarmLevelFlyMove::leave_() {
    LevelFlyMoveBase::leave_();
}

void SwarmLevelFlyMove::loadParams_() {
    LevelFlyMoveBase::loadParams_();
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
}

void SwarmLevelFlyMove::calc_() {
    LevelFlyMoveBase::calc_();
}

// NON_MATCHING: same instructions; the original schedules the 0.1f constant load before the multiply and stores `target`
// to the stack after it (register naming differs)
void SwarmLevelFlyMove::m35(ksys::VFRValue* speed, const sead::Vector3f& from,
                            const sead::Vector3f& to, f32 limit) {
    if (!speed)
        return;

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, from, to, sead::Vector3f::ey);
    const f32 target = *mXZSpeed_s;
    speed->chase(target, target * 0.1f);
    speed->updateStats();
}

}  // namespace uking::action
