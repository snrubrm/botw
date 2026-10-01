#include "Game/AI/AI/aiAssassinMiddleDlcGrabAdapter.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::ai {

namespace {
ksys::util::InitConstants sInitConstants;
sead::FixedSafeString<64> sAncientBallName("DgnObj_RemainsLithograghBall_AoC");
sead::FixedSafeString<64> sGrabFlagName("BalladOfHeroGerudo_AssasinGrabAncientBall");
}  // namespace

AssassinMiddleDlcGrabAdapter::AssassinMiddleDlcGrabAdapter(const InitArg& arg)
    : TargetActorGrabAdapter(arg) {}

AssassinMiddleDlcGrabAdapter::~AssassinMiddleDlcGrabAdapter() = default;

bool AssassinMiddleDlcGrabAdapter::init_(sead::Heap* heap) {
    return TargetActorGrabAdapter::init_(heap);
}

void AssassinMiddleDlcGrabAdapter::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorGrabAdapter::enter_(params);
    _48 = false;
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    if (acc.getName() == sAncientBallName)
        _48 = true;
}

void AssassinMiddleDlcGrabAdapter::calc_() {
    TargetActorGrabAdapter::calc_();
}

void AssassinMiddleDlcGrabAdapter::leave_() {
    TargetActorGrabAdapter::leave_();
    if (_48) {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(mTargetActor_d, &acc);
        if (!acc.hasProc()) {
            auto* gdm = ksys::gdt::Manager::instance();
            if (gdm)
                gdm->setBool(true, sGrabFlagName);
        }
    }
}

void AssassinMiddleDlcGrabAdapter::loadParams_() {
    TargetActorGrabAdapter::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
