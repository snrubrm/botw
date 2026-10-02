#include "Game/AI/Action/actionForceGetUpWaterFloatFreeze.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForceGetUpWaterFloatFreeze::ForceGetUpWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForceGetUpWaterFloatFreeze::~ForceGetUpWaterFloatFreeze() {
    ;
}

bool ForceGetUpWaterFloatFreeze::init_(sead::Heap* heap) {
    return WaterFloatFreeze::init_(heap);
}

void ForceGetUpWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(false);

    sead::Matrix34f mtx;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::util::sub_71011F00EC(&mtx, mActor->getMtx().getBase(2), sead::Vector3f::ey, pos, false);
    ksys::act::sub_7100EE58C0(mActor, mtx);
    if (auto* controller = mActor->getCharacterController()) {
        sub_710072C1B4(controller, mtx.getBase(2));
    }
    _88 = 0;
    WaterFloatFreeze::enter_(params);
}

void ForceGetUpWaterFloatFreeze::leave_() {
    WaterFloatFreeze::leave_();
}

void ForceGetUpWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpWaterFloatFreeze::calc_() {
    if (_88 == 2) {
        WaterFloatFreeze::calc_();
        return;
    }
    if (_88 == 1) {
        ksys::act::sub_7100EE5980(mActor, sead::Vector3f::zero);
        ksys::act::sub_7100EE5A14(mActor, sead::Vector3f::zero);
        ++_88;
    } else {
        _88 = 1;
    }
}

}  // namespace uking::action
