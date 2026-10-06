#include "Game/AI/Action/actionForkASHoldLinearMove.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASHoldLinearMove::ForkASHoldLinearMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASHoldLinearMove::~ForkASHoldLinearMove() = default;

bool ForkASHoldLinearMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASHoldLinearMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASHoldLinearMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASHoldLinearMove::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mRotRestRatio_s, "RotRestRatio");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mMoveDir_s, "MoveDir");
    getStaticParam(&mGravityTransReduce_s, "GravityTransReduce");
}

void ForkASHoldLinearMove::calc_() {
    auto* actor = mActor;
    if (sub_71005DD798(actor, 47, nullptr, 0, 0)) {
        sead::Vector3f dir = *mMoveDir_s;
        dir.normalize();
        dir.rotate(actor->getMtx());
        dir *= *mMoveSpeed_s;
        ksys::act::sub_7100EE5980(actor, dir);
    } else if (*mGravityTransReduce_s) {
        sub_7100738428(actor, *mPosRestRatio_s);
    } else {
        sub_7100738488(actor, *mPosRestRatio_s, -sead::Vector3f::ey);
    }
    sub_7100738AA8(actor, *mRotRestRatio_s);
}

}  // namespace uking::action
