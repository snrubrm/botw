#include "Game/AI/Action/actionPriestBossSideMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PriestBossSideMove::PriestBossSideMove(const InitArg& arg) : MoveBase(arg) {}

PriestBossSideMove::~PriestBossSideMove() = default;

bool PriestBossSideMove::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void PriestBossSideMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void PriestBossSideMove::leave_() {
    MoveBase::leave_();
}

void PriestBossSideMove::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mRotDir_s, "RotDir");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossSideMove::calc_() {
    MoveBase::calc_();
}

void PriestBossSideMove::m32(sead::Vector3f* dir) {
    if (!dir)
        return;
    mActor->getMtx().getBase(*dir, 0);
    dir->y = 0;
    dir->normalize();
    if (_100 == 0)
        dir->negate();
}

}  // namespace uking::action
