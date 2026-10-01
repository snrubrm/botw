#include "Game/AI/AI/aiGolemFireREnemyBattle.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

GolemFireREnemyBattle::GolemFireREnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

GolemFireREnemyBattle::~GolemFireREnemyBattle() = default;

bool GolemFireREnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void GolemFireREnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void GolemFireREnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void GolemFireREnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mPlayerRecoverFromFallFrames_s, "PlayerRecoverFromFallFrames");
}

bool GolemFireREnemyBattle::m42() {
    if (_98.value <= sead::Mathf::epsilon())
        return false;
    return true;
}

void GolemFireREnemyBattle::calc_() {
    EnemyBattle::calc_();
    _98.update();

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc() && player.x_9() != -1)
        _98.value = _98.previous_value = *mPlayerRecoverFromFallFrames_s;
}

}  // namespace uking::ai
