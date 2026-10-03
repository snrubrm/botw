#include "Game/AI/Action/actionArrowShootMoveForLargeObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
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
    if (*mIsReInitShoot_d)
        sub_71000A2A64();
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

void ArrowShootMoveForLargeObject::m36(bool* out, const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasTag(ksys::act::tags::IsIceMakerBlock)) {
        *out = false;
        return;
    }
    mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr,
                        true);
    ksys::eft::searchAndEmitELink(mActor, "Fade");
    m42();
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void ArrowShootMoveForLargeObject::m42() {
    if (_170 || mCallSEKeyAtStick_s.isEmpty())
        return;
    auto* actor = mActor;
    ksys::eft::searchAndEmitSLink(actor, mCallSEKeyAtStick_s.cstr(), false);
    _170 = true;
}

}  // namespace uking::action
