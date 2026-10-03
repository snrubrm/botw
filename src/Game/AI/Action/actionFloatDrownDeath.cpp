#include "Game/AI/Action/actionFloatDrownDeath.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

FloatDrownDeath::FloatDrownDeath(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FloatDrownDeath::~FloatDrownDeath() = default;

bool FloatDrownDeath::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FloatDrownDeath::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_71005D8748(mActor, sead::Vector3f::zero, true, false, nullptr, false);
    if (auto* cc = mActor->getCharacterController())
        _40.changeMotionType(cc, ksys::act::MotionType::Hover);
}

void FloatDrownDeath::leave_() {
    _40.resetMotionType(_40.sub_710072ACF8(mActor));
}

void FloatDrownDeath::loadParams_() {
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatSpeed_s, "FloatSpeed");
    getStaticParam(&mASName_s, "ASName");
}

void FloatDrownDeath::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
