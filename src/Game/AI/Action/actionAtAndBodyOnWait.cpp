#include "Game/AI/Action/actionAtAndBodyOnWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

AtAndBodyOnWait::AtAndBodyOnWait(const InitArg& arg) : AtOnWait(arg) {}

AtAndBodyOnWait::~AtAndBodyOnWait() = default;

bool AtAndBodyOnWait::init_(sead::Heap* heap) {
    return AtOnWait::init_(heap);
}

void AtAndBodyOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    AtOnWait::enter_(params);
    if (auto* body = sub_71000504E8(mBodyName_s)) {
        if (!body->isAddedToWorld())
            body->setTransform(mActor->getMtx());
        body->addToWorld();
    }
}

void AtAndBodyOnWait::leave_() {
    AtOnWait::leave_();
    if (auto* body = sub_71000504E8(mBodyName_s))
        body->removeFromWorld();
}

void AtAndBodyOnWait::loadParams_() {
    AtOnWait::loadParams_();
    getStaticParam(&mBodyName_s, "BodyName");
}

void AtAndBodyOnWait::calc_() {
    AtOnWait::calc_();
}

// NON_MATCHING: the instructions up to the name comparison match; the original compares the names with a plain
// per-character loop (bound 0x80000, true when the bound is reached), sead's SafeString::isEqual gives the 3x unrolled form
ksys::phys::RigidBody* AtAndBodyOnWait::sub_71000504E8(const sead::SafeString& name) {
    auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!set)
        return nullptr;
    auto& bodies = set->getRigidBodies();
    for (s32 i = 0; i < bodies.size(); ++i) {
        if (auto* body = bodies[i]) {
            if (body->getHkBodyName() == name)
                return body;
        }
    }
    return nullptr;
}

}  // namespace uking::action
