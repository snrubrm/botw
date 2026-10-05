#include "Game/AI/AI/aiGanonBattleOnFloorRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

GanonBattleOnFloorRoot::GanonBattleOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnFloorRoot::~GanonBattleOnFloorRoot() = default;

bool GanonBattleOnFloorRoot::init_(sead::Heap* heap) {
    _50 = ksys::Timer(900.0f, 900.0f);
    _5c = false;
    return true;
}

// NON_MATCHING: boolean argument branch scheduling differs.
void GanonBattleOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _50.previous_value = _50.value;
    _50.rate = -1.0f;
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (boss && boss->_14e8.isOnBit(13)) {
        sub_71003E1EE0(true);
        boss->_14e8.resetBit(13);
        return;
    }
    sub_71003E1EE0(testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) || *mIsNoWait_d);
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
