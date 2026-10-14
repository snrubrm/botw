#include "Game/Actor/AI/aiGanonBattleOnWallRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/aiUnk_71002C52DC.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonBattleOnWallRoot::GanonBattleOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnWallRoot::~GanonBattleOnWallRoot() = default;

bool GanonBattleOnWallRoot::init_(sead::Heap* heap) {
    _60 = ksys::Timer(900.0f, 900.0f);
    return true;
}

void GanonBattleOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        _48 = controller->_70;
        _48.normalize();
    }
    _54 = 0;
    _58 = 0;
    auto* life = mActor->getLife();
    _5c = life ? *life : 1;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: block layout (the original shares the 落下攻撃 change between both callers) and the up-vector
// interpolation scheduling (same as GanonApproachOnWallRoot::calc_).
void GanonBattleOnWallRoot::calc_() {
    sub_71005DB068(mActor, *mTargetPos_d);
    if (isCurrentChild("落下攻撃")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
    } else {
        auto* controller = mActor->getCharacterController();
        if (!controller) {
            setFailed();
            return;
        }
        sead::Vector3f up;
        sub_71002C62EC(&up, mActor, 10.0f);
        const f32 max_step = ksys::VFR::instance()->getDeltaFrame() * 0.1f;
        const sead::Vector3f diff = up - _48;
        const f32 length = diff.length();
        if (length > max_step)
            _48 += diff * (1.0f / length) * max_step;
        else
            _48 = up;
        _48.normalize();
        controller->sub_7100F5EDE8(_48);
        controller->sub_7100F5EE1C(_48 * 29.0f);

        auto* damage_mgr = sub_710072BA90(mActor);
        if (damage_mgr && s32(damage_mgr->getDamage()) > 0) {
            ++_54;
            if (damage_mgr->checkDamageFlags(1) || damage_mgr->checkDamageFlags(0))
                _54 += 2;
        }
        const s32 prev_life = _5c;
        auto* life = mActor->getLife();
        _5c = life ? *life : 1;
        if (!sub_71002C5E00(mActor, prev_life, 0.5f) && sub_71002C52DC(mActor, 0.5f)) {
            _60 = ksys::Timer(900.0f, 900.0f);
            _54 = 0;
            _58 = 0;
            return;
        }
        if (_54 > 2 || _60.value <= sead::Mathf::epsilon()) {
            _60 = ksys::Timer(900.0f, 900.0f);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("落下攻撃", &pack);
            return;
        }
    }

    if (isCurrentChild("待機")) {
        _60.update();
        sead::Vector3f pos;
        sub_71002C64A0(&pos, mActor);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
    } else if (isCurrentChild("移動")) {
        _60.update();
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
        if (auto* controller = mActor->getCharacterController()) {
            _48 = controller->_70;
            _48.normalize();
        }
        if (_58 > 2) {
            _60 = ksys::Timer(900.0f, 900.0f);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("落下攻撃", &pack);
            return;
        }
    } else if (isCurrentChild("遠距離攻撃")) {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        sead::Vector3f pos;
        sub_71002C64A0(&pos, mActor);
        getCurrentChild()->setDynamicParam(pos, "ViewPos");
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("移動", &pack);
        return;
    } else {
        return;
    }
    changeToWaitOrLongRangeAttack();
}

void GanonBattleOnWallRoot::changeToWaitOrLongRangeAttack() {
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (boss && boss->getActorPartsActor("FireBall").hasProcInCalcState())
        changeToWait();
    else
        changeToLongRangeAttack();
}

void GanonBattleOnWallRoot::changeToWait() {
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void GanonBattleOnWallRoot::changeToLongRangeAttack() {
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(pos, "ViewPos", -1);
    changeChild("遠距離攻撃", &pack);
    ++_58;
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
