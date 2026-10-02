#include "Game/AI/AI/aiDragonReturn.h"
#include "Game/Actor/actDragon.h"

namespace uking::ai {

DragonReturn::DragonReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonReturn::~DragonReturn() = default;

bool DragonReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = false;
    _9c = false;
    sub_710036D5BC();
    _98 = *mAvoidStartDistance_s;
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor))
        dragon->_1f70.set(0x20000000);
}

void DragonReturn::leave_() {
    _a0.fadeXLink();
}

void DragonReturn::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mChangeMoveHeight_s, "ChangeMoveHeight");
    getStaticParam(&mFinishHeight_s, "FinishHeight");
    getStaticParam(&mAngle_s, "Angle");
    getStaticParam(&mAvoidStartDistance_s, "AvoidStartDistance");
    getStaticParam(&mReturnStartFrame_s, "ReturnStartFrame");
}

}  // namespace uking::ai
