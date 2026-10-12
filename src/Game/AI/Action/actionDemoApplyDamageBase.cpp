#include "Game/AI/Action/actionDemoApplyDamageBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DemoApplyDamageBase::DemoApplyDamageBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoApplyDamageBase::~DemoApplyDamageBase() = default;

bool DemoApplyDamageBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DemoApplyDamageBase::oneShot_() {
    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    const s32 damage = *mValue_d;
    *mActor->getLife() = life > damage ? life - damage : 0;
    return true;
}

void DemoApplyDamageBase::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
