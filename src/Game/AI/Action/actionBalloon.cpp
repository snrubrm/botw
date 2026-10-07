#include "Game/AI/Action/actionBalloon.h"
#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::action {

Balloon::Balloon(const InitArg& arg) : BalloonBase(arg) {}

Balloon::~Balloon() {
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_118, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    _110 = nullptr;
}

bool Balloon::init_(sead::Heap* heap) {
    if (!BalloonBase::init_(heap))
        return false;
    sub_71000B782C(mActor->getMtx().m[1][3]);
    // The original calls the sibling class's helper directly on this object (it only reads
    // Action+0x8, so the layout is compatible); reached through BalloonBase.
    static_cast<OctarockBalloonBase*>(static_cast<BalloonBase*>(this))->sub_71000B8928(0.1f);
    if (!sub_71005D6D10() && !sub_71000B70DC())
        return false;
    return true;
}

void Balloon::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void Balloon::leave_() {
    BalloonBase::leave_();
}

void Balloon::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
    getMapUnitParam(&mRopeHungActOffset_m, "RopeHungActOffset");
}

void Balloon::calc_() {
    BalloonBase::calc_();
}

void Balloon::m35(ksys::phys::RigidBody* a, ksys::phys::RigidBody* b,
                  ksys::act::RopeBase* rope) {
    if (!rope)
        return;
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityRope);
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityGroundObject);
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityObject);
}

}  // namespace uking::action
