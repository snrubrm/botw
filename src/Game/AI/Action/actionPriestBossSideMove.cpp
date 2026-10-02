#include "Game/AI/Action/actionPriestBossSideMove.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PriestBossSideMove::PriestBossSideMove(const InitArg& arg) : MoveBase(arg) {}

PriestBossSideMove::~PriestBossSideMove() = default;

bool PriestBossSideMove::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

// NON_MATCHING: the original reloads _100 (and getASList()) after the isEmpty check
void PriestBossSideMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    int dir = *mRotDir_s;
    if (dir == 1)
        dir = sead::GlobalRandom::instance()->getBool() ? 0 : 2;
    _100 = dir;
    if (mASName_s.isEmpty())
        return;
    mActor->getASList()->x_6(9, 0, (_100 - 1) * 90.0f);
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, 0, 0, -1.0f);
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
