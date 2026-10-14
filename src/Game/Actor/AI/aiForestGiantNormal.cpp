#include "Game/Actor/AI/aiForestGiantNormal.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/aiRandomTimer.h"

namespace uking::ai {

ForestGiantNormal::ForestGiantNormal(const InitArg& arg) : EnemyNormal(arg) {}

ForestGiantNormal::~ForestGiantNormal() = default;

bool ForestGiantNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

// NON_MATCHING: the original stores max alone first, then value / min as one 8-byte store
void ForestGiantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _3dc.value = 0;
    _3dc.min = 120;
    _3dc.max = 120;
    EnemyNormal::enter_(params);
    _3d8 = false;
}

// NON_MATCHING: the original keeps a separate DynamicCast per _e90 store at the end (ours merges them); the
// rest matches.
void ForestGiantNormal::calc_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e80.isOnBit(0))
            _3dc.reset();
        else
            _3dc.update();
    }

    const auto isWaiting = [this] {
        return isCurrentChild("待機") || isCurrentChild("初期待機") || isCurrentChild("諦め") ||
               isCurrentChild("見失い");
    };

    auto* child = getCurrentChild();
    bool waiting = false;
    bool changeable = true;
    if (child->isFinished() || child->isFailed())
        waiting = isWaiting();
    else if (!child->isChangeable())
        changeable = false;
    else if (!isCurrentChild("暗闇目覚め"))
        waiting = isWaiting();

    if (waiting && _3d8) {
        EnemyNormal::calc_();
        if (child == getCurrentChild()) {
            _3ac.resetBit(3);
            changeChild("暗闇目覚め");
        }
        _3d8 = false;
    } else {
        if (changeable)
            _3d8 = false;
        EnemyNormal::calc_();
    }

    if ((isCurrentChild("プレイヤー発見") || isCurrentChild("攻撃反応") || isCurrentChild("怒り") ||
         isCurrentChild("見失い")) &&
        !sub_71005E0384(mActor)) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e90 = 4;
    } else {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e90 = 1;
    }
}

void ForestGiantNormal::leave_() {
    EnemyNormal::leave_();
}

void ForestGiantNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSleepingHearAwnRatio_s, "SleepingHearAwnRatio");
}

bool ForestGiantNormal::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000015) {
        _3d8 = false;
        return false;
    }
    if (message->getType() == 0x3000016) {
        _3d8 = true;
        return false;
    }
    return EnemyNormal::handleMessage_(message);
}

void ForestGiantNormal::m34() {
    if (mActor->getRootAi()->getI() == 5) {
        EnemyNormal::m34();
        return;
    }
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m48(&pos);
    params.addVec3(pos, "CentralPos", -1);
    changeChild("初期待機", &params);
}

bool ForestGiantNormal::m54() {
    if (isCurrentChild("初期待機"))
        return true;
    return EnemyNormal::m54();
}

void ForestGiantNormal::m60(Unk3* out) {
    EnemyNormal::m60(out);
    if (out->_0 == 0 && isCurrentChild("プレイヤー発見"))
        out->_0 = 3;
}

bool ForestGiantNormal::m63(Unk3* result) {
    if (result->_0 != 3)
        return false;

    const auto& pos = sub_71005D98D8(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤー見失い", &params);
    return true;
}

bool ForestGiantNormal::m68(Unk2* out, Unk1* info) {
    if (!EnemyNormal::m68(out, info))
        return false;
    if (_3dc.value <= 0.0f)
        return true;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && out->_0 && enemy->_c38(0) == *out->_0)
        return false;
    return true;
}

}  // namespace uking::ai
