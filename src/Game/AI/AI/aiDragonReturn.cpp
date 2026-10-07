#include "Game/AI/AI/aiDragonReturn.h"
#include "Game/Actor/actDragon.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/VFR.h"

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

void DragonReturn::sub_710036D5BC() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || !dragon->getCharacterController())
        return;
    _80 = 0;
    const f32 speed = dragon->x_0();
    _84 = speed * (1.0f / ksys::VFR::instance()->getDeltaFrame());
    sead::Vector3f front;
    sub_7100010168(dragon, &front);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(dragon->getMtx().getTranslation(), "TargetPos", -1);
    params.addVec3(-front, "FrontDir", -1);
    changeChild("移動", &params);
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
