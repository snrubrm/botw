#include "Game/AI/Action/actionArrowShootMoveForLargeObject.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ArrowShootMoveForLargeObject::ArrowShootMoveForLargeObject(const InitArg& arg)
    : ArrowShootMove(arg) {}

ArrowShootMoveForLargeObject::~ArrowShootMoveForLargeObject() = default;

void ArrowShootMoveForLargeObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
    _170 = false;
}

void ArrowShootMoveForLargeObject::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mRayCastDist_s, "RayCastDist");
    getStaticParam(&mCallSEKeyAtStick_s, "CallSEKeyAtStick");
    getDynamicParam(&mIsReInitShoot_d, "IsReInitShoot");
}

void ArrowShootMoveForLargeObject::calc_() {
    ArrowShootMove::calc_();
}

float ArrowShootMoveForLargeObject::m32() {
    return *mRayCastDist_s * 0.5f;
}

bool ArrowShootMoveForLargeObject::m35(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.hasProc() &&
           (accessor.hasTag(ksys::act::tags::IsIceMakerBlock) || accessor.getName() == "GanonTornado");
}

f32 ArrowShootMoveForLargeObject::m41() {
    return *mRayCastDist_s;
}

}  // namespace uking::action
