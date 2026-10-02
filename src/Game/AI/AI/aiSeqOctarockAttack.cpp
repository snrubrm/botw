#include "Game/AI/AI/aiSeqOctarockAttack.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SeqOctarockAttack::SeqOctarockAttack(const InitArg& arg) : SeqThreeAction(arg) {}

SeqOctarockAttack::~SeqOctarockAttack() = default;

bool SeqOctarockAttack::init_(sead::Heap* heap) {
    return SeqThreeAction::init_(heap);
}

void SeqOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqThreeAction::enter_(params);
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
}

void SeqOctarockAttack::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && !isCurrentChild("先行動")) {
        if (isCurrentChild("中行動")) {
            if (auto* lod = mActor->getLodState())
                lod->mFlags26.reset(1);
        }
    }
    sub_71005DB3EC(mActor);
    SeqThreeAction::calc_();
}

void SeqOctarockAttack::leave_() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
    SeqThreeAction::leave_();
}

void SeqOctarockAttack::loadParams_() {
    SeqThreeAction::loadParams_();
}

}  // namespace uking::ai
