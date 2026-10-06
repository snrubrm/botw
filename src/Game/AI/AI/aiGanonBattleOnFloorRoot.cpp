#include "Game/AI/AI/aiGanonBattleOnFloorRoot.h"
#include "Game/Actor/actLastBoss.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

// 0x71002d2a80 (declaration only; the source namespace is unknown): the player is neither dead nor in the state
// checked by 0x6debec(.., 8).
bool sub_71002D2A80();

namespace uking::ai {

GanonBattleOnFloorRoot::GanonBattleOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnFloorRoot::~GanonBattleOnFloorRoot() = default;

bool GanonBattleOnFloorRoot::init_(sead::Heap* heap) {
    _50 = ksys::Timer(900.0f, 900.0f);
    _5c = false;
    return true;
}

void GanonBattleOnFloorRoot::sub_71003E1EE0(bool no_wait) {
    if (!sub_71002D2A80()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
        return;
    }
    if (!_5c) {
        const f32 dx = mActor->getMtx().getTranslation().x - mTargetPos_d->x;
        const f32 dz = mActor->getMtx().getTranslation().z - mTargetPos_d->z;
        const f32 dist2 = dx * dx + dz * dz;
        const f32 range2 = *mFarAttackDist_s * *mFarAttackDist_s;
        bool far_attack;
        if (!(dist2 >= range2) && dist2 >= range2 * 0.5f)
            far_attack = sead::GlobalRandom::instance()->getU32(100) < 50;
        else
            far_attack = dist2 >= range2;
        if (far_attack) {
            _5c = true;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("遠距離攻撃", &pack);
            return;
        }
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(no_wait, "IsCounter", -1);
    pack.addBool(_5c, "IsPrevBeam", -1);
    changeChild("近接攻撃", &pack);
    _5c = false;
}

void GanonBattleOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _50.previous_value = _50.value;
    _50.rate = -1.0f;
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (boss && boss->_14e8.isOnBit(13)) {
        sub_71003E1EE0(true);
        boss->_14e8.resetBit(13);
        return;
    }
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) || *mIsNoWait_d)
        sub_71003E1EE0(true);
    else
        sub_71003E1EE0(false);
}

void GanonBattleOnFloorRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    _50.update();
    if (_50.value <= sead::Mathf::epsilon()) {
        _50.reset(900.0f, 0.0f);
        if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
            boss->_14e4 = 2;
    }
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed())
            _5c = false;
        if (isCurrentChild("待機") || _50.value <= sead::Mathf::epsilon())
            setFinished();
        else
            sub_71003E1EE0(false);
    }
}

void GanonBattleOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleOnFloorRoot::loadParams_() {
    getStaticParam(&mFarAttackDist_s, "FarAttackDist");
    getDynamicParam(&mIsNoWait_d, "IsNoWait");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GanonBattleOnFloorRoot::isFinished() const {
    auto* child = getCurrentChild();
    if (child && (isCurrentChild("近接攻撃") || isCurrentChild("遠距離攻撃")))
        return child->isFinished();
    return ActionBase::isFinished();
}

}  // namespace uking::ai
