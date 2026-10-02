#include "Game/AI/AI/aiGanonBattleOnWallRoot.h"
#include "Game/Actor/actLastBoss.h"

namespace uking::ai {

GanonBattleOnWallRoot::GanonBattleOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnWallRoot::~GanonBattleOnWallRoot() = default;

bool GanonBattleOnWallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBattleOnWallRoot::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        if (boss->_14f8._30.isOnBit(2))
            _60 = ksys::Timer(900, 900);
    }
}

void GanonBattleOnWallRoot::loadParams_() {
    getStaticParam(&mGuardianActivateHP_s, "GuardianActivateHP");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
