#include "Game/AI/AI/aiHangedLamp.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HangedLamp::HangedLamp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HangedLamp::~HangedLamp() = default;

bool HangedLamp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HangedLamp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mDisableImpulseByArrow_s)
        setDamageCallbackTiming(mActor, 2, &_38);
    changeChild("待機");
}

void HangedLamp::calc_() {
    const s32* life = mActor->getLife();
    if (life && *life <= 0 && isCurrentChild("待機"))
        changeChild("発火");
}

void HangedLamp::leave_() {
    if (*mDisableImpulseByArrow_s)
        sub_71005DA114(mActor, &_38);
}

void HangedLamp::loadParams_() {
    getStaticParam(&mDisableImpulseByArrow_s, "DisableImpulseByArrow");
}

}  // namespace uking::ai
