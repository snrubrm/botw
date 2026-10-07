#include "Game/AI/AI/aiDragonTurn.h"
#include "Game/Actor/actDragon.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

DragonTurn::DragonTurn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonTurn::~DragonTurn() = default;

bool DragonTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sead::IsDerivedFrom<act::Dragon>(mActor))
        return;
    sub_7100371E4C();
    _74 = *mAvoidStartDistance_s;
    mFlags.set(Flag::Changeable);
}

void DragonTurn::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the zero-vector pair store uses the advanced member address.
void DragonTurn::sub_7100371E4C() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || !dragon->getCharacterController())
        return;
    _58 = 1;
    _5c = 0;
    const f32 speed = dragon->x_0();
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    _78.set(0, 0, 0);
    _60 = speed * (1.0f / delta);
    sead::Vector3f front;
    sub_7100010168(dragon, &front);
    sead::Vector3f target;
    sub_7100372E30(&target, &front);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(-front, "FrontDir", -1);
    changeChild("移動", &params);
}

// NON_MATCHING: interpolation vector loads are scheduled before the weight subtraction.
bool DragonTurn::sub_7100372E30(sead::Vector3f* target, const sead::Vector3f* front) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    *target = *mTargetPos_d;
    sead::Vector3f direction = *target - dragon->getMtx().getTranslation();
    direction.normalize();
    const f32 dot = direction.dot(*front);
    if (dot < -0.9f) {
        _58 = 0;
        return false;
    }
    if (dot > -0.4f) {
        const sead::Vector3f position = dragon->getMtx().getTranslation();
        *target = position + dragon->sub_710001014C().getBase(0) * 100.0f;
        _78 = *target;
        _84 = 150;
        return true;
    }
    *target = *mTargetVec_d * (1.0f - _58) + *mTargetPos_d;
    return false;
}

void DragonTurn::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAvoidStartDistance_s, "AvoidStartDistance");
    getDynamicParam(&mTargetVec_d, "TargetVec");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
