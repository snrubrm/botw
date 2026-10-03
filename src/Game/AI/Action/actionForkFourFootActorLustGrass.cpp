#include "Game/AI/Action/actionForkFourFootActorLustGrass.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModel.h"

namespace uking::action {

ForkFourFootActorLustGrass::ForkFourFootActorLustGrass(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkFourFootActorLustGrass::~ForkFourFootActorLustGrass() = default;

bool ForkFourFootActorLustGrass::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel()) {
        _b0[0].search(model, mNode1Name_s);
        _b0[1].search(model, mNode2Name_s);
        _b0[2].search(model, mNode3Name_s);
        _b0[3].search(model, mNode4Name_s);
    }
    _190 = -1;
    _198 = -1;
    return true;
}

void ForkFourFootActorLustGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    _88._8._10 = *mMinRadius_s;
    _88._8._14 = *mMinRadius_s;
    _88._8._18 = *mMinRadius_s;
    _88._8._1c = *mMinRadius_s;
    _1a0 = false;
    mFlags.set(Flag::Changeable);
}

void ForkFourFootActorLustGrass::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFourFootActorLustGrass::loadParams_() {
    getStaticParam(&mMaxRadius_s, "MaxRadius");
    getStaticParam(&mMinRadius_s, "MinRadius");
    getStaticParam(&mNode1Name_s, "Node1Name");
    getStaticParam(&mNode2Name_s, "Node2Name");
    getStaticParam(&mNode3Name_s, "Node3Name");
    getStaticParam(&mNode4Name_s, "Node4Name");
    getStaticParam(&mWorldOffset_s, "WorldOffset");
    getStaticParam(&mRadSpd_s, "RadSpd");
    getAITreeVariable(&mGanonBeastGrudgeMarkMgr_a, "GanonBeastGrudgeMarkMgr");
}

void ForkFourFootActorLustGrass::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkFourFootActorLustGrass::hasUpdateForPreDeleteCb() {
    return true;
}

bool ForkFourFootActorLustGrass::updateForPreDelete() {
    _88._8._0.sub_71007444AC();
    return true;
}

}  // namespace uking::action
