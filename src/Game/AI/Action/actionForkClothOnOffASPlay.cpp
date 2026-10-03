#include "Game/AI/Action/actionForkClothOnOffASPlay.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

ForkClothOnOffASPlay::ForkClothOnOffASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkClothOnOffASPlay::~ForkClothOnOffASPlay() = default;

bool ForkClothOnOffASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkClothOnOffASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkClothOnOffASPlay::leave_() {
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.reset(2);
}

void ForkClothOnOffASPlay::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mClothOffASName_s, "ClothOffASName");
}

void ForkClothOnOffASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
