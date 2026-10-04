#include "Game/AI/Action/actionLynelNavMeshMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

LynelNavMeshMove::LynelNavMeshMove(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

LynelNavMeshMove::~LynelNavMeshMove() = default;

bool LynelNavMeshMove::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void LynelNavMeshMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
    _80.sub_710070F9CC(mActor);
}

void LynelNavMeshMove::leave_() {
    _80.sub_710070F9CC(mActor);
    AnimalMoveGuidedBase::leave_();
}

void LynelNavMeshMove::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
    _80.sub_710070F984(this);
}

void LynelNavMeshMove::calc_() {
    AnimalMoveGuidedBase::calc_();
    auto* nav = mActor->m45();
    if (!nav)
        return;
    sead::Vector3f diff = *mTargetPos_d - mActor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    _80.sub_710070FA84(mActor, &nav->_248, dist);
}

}  // namespace uking::action
