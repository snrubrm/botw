#include "Game/AI/Action/actionAirOctaMgr.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

AirOctaMgr::AirOctaMgr(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaMgr::~AirOctaMgr() {
    _60.freeBuffer();
}

bool AirOctaMgr::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaMgr::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaMgr::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaMgr::loadParams_() {
    getStaticParam(&mLeaveDistance_s, "LeaveDistance");
    getStaticParam(&mLeaveDownY_s, "LeaveDownY");
    getStaticParam(&monGraundEscapeDist_s, "onGraundEscapeDist");
    getStaticParam(&mPlayerLostTime_s, "PlayerLostTime");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mReactHorn_m, "ReactHorn");
}

void AirOctaMgr::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

Unk_7102362e80::~Unk_7102362e80() = default;

bool uking::action::Unk_7102362ea8::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.isPlayerProfile();
}

bool uking::action::Unk_7102362ed0::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.isFlyingBalloon();
}
