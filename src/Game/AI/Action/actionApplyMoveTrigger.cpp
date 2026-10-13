#include "Game/AI/Action/actionApplyMoveTrigger.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ApplyMoveTrigger::ApplyMoveTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyMoveTrigger::~ApplyMoveTrigger() = default;

bool ApplyMoveTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: native switch keeps separate converted vectors; common mode logic changes
// branches, stack layout and register allocation.
void ApplyMoveTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Matrix34f home;
    mActor->getHomeMtx(&home);
    const sead::Vector3f position = home.getTranslation();
    sead::Vector3f force;
    home.getBase(force, 2);
    force *= *mApplyForceValue_m;

    const int type = *mForceType_m;
    if (type >= 0 && type <= 3) {
        const bool convert = type < 2;
        const bool use_position = type == 1 || type == 3;
        if (convert)
            force *= 1.0f / 30.0f;
        _40.sub_7100D3D3C4(use_position ? 1 : 0, &force,
                          use_position ? &position : nullptr, convert);
    }
    _60 = false;
}

void ApplyMoveTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyMoveTrigger::loadParams_() {
    getStaticParam(&mIsOnDebugDraw_s, "IsOnDebugDraw");
    getMapUnitParam(&mTriggerType_m, "TriggerType");
    getMapUnitParam(&mForceType_m, "ForceType");
    getMapUnitParam(&mApplyForceValue_m, "ApplyForceValue");
}

void ApplyMoveTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
