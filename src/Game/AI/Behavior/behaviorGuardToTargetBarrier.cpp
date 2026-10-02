#include "Game/AI/Behavior/behaviorGuardToTargetBarrier.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::behavior {

GuardToTargetBarrier::GuardToTargetBarrier(const InitArg& arg) : GuardFrontBarrier(arg) {}

GuardToTargetBarrier::~GuardToTargetBarrier() = default;

bool GuardToTargetBarrier::m6(sead::Heap* heap) {
    return GuardFrontBarrier::m6(heap);
}

void GuardToTargetBarrier::m7() {
    GuardFrontBarrier::m7();
}

void GuardToTargetBarrier::m8() {
    GuardFrontBarrier::m8();
}

void GuardToTargetBarrier::m9() {
    GuardFrontBarrier::m9();
}

void GuardToTargetBarrier::m15(sead::Matrix34f* out) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir = sub_71005D9330(mActor);
    dir -= pos;
    dir.y = 0;
    dir.normalize();
    ksys::util::sub_71011F00EC(out, dir, sead::Vector3f::ey, pos, false);
}

void GuardToTargetBarrier::loadParams() {
    GuardFrontBarrier::loadParams();
}

}  // namespace uking::behavior
