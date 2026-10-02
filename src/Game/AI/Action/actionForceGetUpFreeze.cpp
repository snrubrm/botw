#include "Game/AI/Action/actionForceGetUpFreeze.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForceGetUpFreeze::ForceGetUpFreeze(const InitArg& arg) : Freeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForceGetUpFreeze::~ForceGetUpFreeze() {
    ;
}

bool ForceGetUpFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void ForceGetUpFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
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
    Freeze::enter_(params);
}

void ForceGetUpFreeze::leave_() {
    Freeze::leave_();
}

void ForceGetUpFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpFreeze::calc_() {
    if (_88 == 2) {
        Freeze::calc_();
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
