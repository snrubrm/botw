#include "Game/AI/AI/aiSandwormRNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

SandwormRNormal::SandwormRNormal(const InitArg& arg) : SandwormNormal(arg) {}

SandwormRNormal::~SandwormRNormal() = default;

bool SandwormRNormal::init_(sead::Heap* heap) {
    return SandwormNormal::init_(heap);
}

void SandwormRNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SandwormNormal::enter_(params);
}

void SandwormRNormal::calc_() {
    SandwormNormal::calc_();
}

void SandwormRNormal::leave_() {
    SandwormNormal::leave_();
}

void SandwormRNormal::loadParams_() {
    SandwormNormal::loadParams_();
}

bool SandwormRNormal::m44(const sead::Vector3f& pos) {
    bool far = true;
    if (mActor->checkBasicSig())
        far = (getPlayerPosition() - pos).squaredLength() > 1.0f;
    return SandwormNormal::m44(pos) && far;
}

}  // namespace uking::ai
