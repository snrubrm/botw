#include "Game/AI/Action/actionAtAndBodyOnWait.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

AtAndBodyOnWait::AtAndBodyOnWait(const InitArg& arg) : AtOnWait(arg) {}

AtAndBodyOnWait::~AtAndBodyOnWait() = default;

bool AtAndBodyOnWait::init_(sead::Heap* heap) {
    return AtOnWait::init_(heap);
}

void AtAndBodyOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    AtOnWait::enter_(params);
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

}  // namespace uking::action
