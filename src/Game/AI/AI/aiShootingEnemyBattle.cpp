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

// NON_MATCHING: the original reads _b4 before the sub_71005D93CC call; a `const bool done = _b4;` local
// before the call matches (borderline, not applied)
void ShootingEnemyBattle::calc_() {
    if (!_b4 && !m44())
        _b4 = true;

    if (!isCurrentChild("画面外攻撃")) {
        EnemyBattle::calc_();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
        } else {
            sub_7100381ED4();
            m37();
        }
        return;
    }

    const sead::Vector3f& target = sub_71005D93CC(mActor);
    if (_b4)
        child->setDynamicParam(target, "TargetPos");
    else
        child->setDynamicParam(target + _b8, "TargetPos");
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
