#include "Game/AI/AI/aiRemainsFireBattleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

RemainsFireBattleMove::RemainsFireBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsFireBattleMove::~RemainsFireBattleMove() = default;

bool RemainsFireBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsFireBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: the original keeps &mActor in a callee-saved register (frame with x22) and tests the
// damage with `cmp #0; b.le`; the player position is copied like in sub_7100540FE4
void RemainsFireBattleMove::calc_() {
    if (isCurrentChild("待機")) {
        auto* mgr = mActor->getDamageMgr();
        if (mgr && mgr->getField50() == 4) {
            const s32 damage = mgr->getDamage();
            if (damage > 0) {
                changeChild("移動");
                return;
            }
        }
    }

    if (mActor->checkBasicSig() && !isCurrentChild("攻撃")) {
        sub_7100540FE4();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃")) {
            changeChild("待機");
            mActor->getLodState()->mFlags10.reset(0x40);
            if (!_80) {
                _50._18.y(mActor);
                sub_71005E02E0(mActor, &_50, nullptr);
            }
            sub_71005E02E0(mActor, &_38, nullptr);
            return;
        }
        isCurrentChild("移動");
    }

    if (isCurrentChild("攻撃"))
        getCurrentChild()->setDynamicParam(getPlayerPosition(), "TargetPos");
}

// NON_MATCHING: `&_50` is computed before the payload lock (scheduling)
bool RemainsFireBattleMove::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;
    if (!sead::DynamicCast<RemainsFireBattleMove>(other))
        return false;
    _80 = false;
    _50._18.y(mActor);
    sub_71005E02E0(mActor, &_50, nullptr);
    return true;
}

void RemainsFireBattleMove::leave_() {
    mActor->getLodState()->mFlags10.reset(0x40);
}

void RemainsFireBattleMove::handlePendingChildChange_() {
    const sead::SafeString name = mChildren[mPendingChildIdx]->getName();
    if (name == "攻撃") {
        sub_7100540FE4();
        return;
    }
    if (name == "移動")
        changeChild("移動");
    else
        changeChild("待機");
}

// NON_MATCHING: the original copies the player position x/y (8 bytes) before z
void RemainsFireBattleMove::sub_7100540FE4() {
    mActor->getLodState()->mFlags10.set(0x40);
    ksys::act::ai::InlineParamPack params;
    const sead::Vector3f pos = getPlayerPosition();
    params.addVec3(pos, "TargetPos", -1);
    changeChild("攻撃", &params);
}

void RemainsFireBattleMove::loadParams_() {}

bool RemainsFireBattleMove::handleAck_(const ksys::MessageAck& ack) {
    if (!_50.sub_710070E070(ack))
        return false;
    if (_50._14)
        _80 = true;
    return true;
}

}  // namespace uking::ai
