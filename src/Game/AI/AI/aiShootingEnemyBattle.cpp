#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ShootingEnemyBattle::ShootingEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

ShootingEnemyBattle::~ShootingEnemyBattle() = default;

bool ShootingEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void ShootingEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    _b4 = false;
    _b0 = 0;
}

void ShootingEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void ShootingEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mOutScreenAttackNum_s, "OutScreenAttackNum");
    getStaticParam(&mOutScreenDist_s, "OutScreenDist");
    getStaticParam(&mOutScrnAtkOffset_s, "OutScrnAtkOffset");
    getStaticParam(&mOutScrnAtkOffsetY_s, "OutScrnAtkOffsetY");
}

void ShootingEnemyBattle::m38() {
    if (!_b4 && _b0 < *mOutScreenAttackNum_s) {
        sub_7100569CA0();
        return;
    }
    EnemyBattle::m38();
}

bool ShootingEnemyBattle::m39() {
    return m40();
}

void ShootingEnemyBattle::sub_7100569CA0() {
    sub_7100569DC8(&_b8);
    sead::Vector3f pos = sub_71005D93CC(mActor);
    pos += _b8;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("画面外攻撃", &params);
    ++_b0;
}

}  // namespace uking::ai
