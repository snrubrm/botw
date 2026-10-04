#include "Game/AI/Action/actionLynelMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

LynelMove::LynelMove(const InitArg& arg) : AnimalMove(arg) {}

LynelMove::~LynelMove() = default;

bool LynelMove::init_(sead::Heap* heap) {
    return AnimalMove::init_(heap);
}

void LynelMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMove::enter_(params);
    _88.sub_710070F9CC(mActor);
}

void LynelMove::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76314();
    _88.sub_710070F9CC(mActor);
    AnimalMove::leave_();
}

void LynelMove::loadParams_() {
    AnimalMove::loadParams_();
    getStaticParam(&mTimeForCalcCheckCliffDist_s, "TimeForCalcCheckCliffDist");
    _88.sub_710070F984(this);
}

void LynelMove::calc_() {
    AnimalMove::calc_();
    const sead::Vector3f* target = m32();
    sead::Vector3f dir = *target - mActor->getMtx().getTranslation();
    dir.y = 0.0f;
    const f32 length = dir.normalize();
    _88.sub_710070FA84(mActor, &dir, length);
}

bool LynelMove::m34(const sead::Vector3f& pos, float x) {
    const f32 dist = *mTimeForCalcCheckCliffDist_s * (ksys::VFR::instance()->getDeltaFrame() * x);
    if (dist > 0.0f && sub_710072FEC4(mActor, pos, dist, nullptr, true, nullptr))
        return false;
    return true;
}

}  // namespace uking::action
