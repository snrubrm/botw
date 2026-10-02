#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>

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

bool ShootingEnemyBattle::m40() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !(enemy->_e68.value <= sead::Mathf::epsilon()))
        return false;
    return sub_710072DDB8(sub_71005D9330(mActor), mActor->getMtx(), *mAttackAngle_s);
}

void ShootingEnemyBattle::sub_7100569DC8(sead::Vector3f* out) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = sub_71005D93CC(mActor);
    dir -= pos;
    dir.normalize();
    sead::Vector3f side;
    side.setCross(dir, sead::Vector3f::ey);
    side.normalize();

    const f32 offset = *mOutScrnAtkOffset_s;
    const s32 sign = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    sead::Vector3f result = side * f32(sign) * offset;
    result.y += *mOutScrnAtkOffsetY_s;
    *out = result;
}

}  // namespace uking::ai
