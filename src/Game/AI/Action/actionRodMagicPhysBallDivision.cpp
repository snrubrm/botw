#include "Game/AI/Action/actionRodMagicPhysBallDivision.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

RodMagicPhysBallDivision::RodMagicPhysBallDivision(const InitArg& arg) : RodMagicPhysBall(arg) {}

// Inline-only in the original (name is a guess; repeated three times in the destructor).
static void deleteLinkedActor(ksys::act::BaseProcLink& link) {
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: regalloc only (the original keeps two of the three link addresses in registers and recomputes
// `this + 0x1e0` for the member destruction).
RodMagicPhysBallDivision::~RodMagicPhysBallDivision() {
    deleteLinkedActor(_1e0);
    deleteLinkedActor(_1f0);
    deleteLinkedActor(_200);
}

bool RodMagicPhysBallDivision::init_(sead::Heap* heap) {
    if (!ChemicalPhysBall::init_(heap))
        return false;
    sub_710023C72C();
    return true;
}

void RodMagicPhysBallDivision::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getTranslation(_210);
    RodMagicPhysBall::enter_(params);
}

void RodMagicPhysBallDivision::leave_() {
    RodMagicPhysBall::leave_();
}

void RodMagicPhysBallDivision::loadParams_() {
    RodMagicPhysBall::loadParams_();
    getStaticParam(&mDivNum_s, "DivNum");
    getStaticParam(&mDivDist_s, "DivDist");
    getStaticParam(&mDivAngle_s, "DivAngle");
    getStaticParam(&mChildName_s, "ChildName");
}

void RodMagicPhysBallDivision::calc_() {
    RodMagicPhysBall::calc_();
}

}  // namespace uking::action
