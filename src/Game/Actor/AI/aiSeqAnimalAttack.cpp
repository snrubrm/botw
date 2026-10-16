#include "Game/Actor/AI/aiSeqAnimalAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007398C0.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::ai {

SeqAnimalAttack::SeqAnimalAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqAnimalAttack::~SeqAnimalAttack() = default;

bool SeqAnimalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqAnimalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _54 = false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_c48._8.hasProc()) {
            _48 = enemy->_c48._18;
            {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_48, "TargetPos", -1);
                changeChild("攻撃前", &pack);
            }
            if (auto* control = sub_71007398C0(mActor)) {
                const f32 value = 0.7f;
                control->sub_7100D8A9D0(value);
            }
            return;
        }
    }
    setFailed();
}

// 0x71005607cc
// NON_MATCHING: register allocation and load order of the position in front of the actor.
void SeqAnimalAttack::calc_() {
    if (hasAttackInfo(mActor))
        _54 = true;

    if (isCurrentChild("攻撃前")) {
        const auto& mtx = mActor->getMtx();
        const sead::Vector3f pos = mtx.getBase(2) * 7.5f + mtx.getTranslation();
        sub_71005DB068(mActor, pos);
    } else if (isCurrentChild("攻撃")) {
        sub_71005DB3EC(mActor);
    } else {
        const sead::Vector3f pos = sub_71005D960C(mActor);
        sub_71005DB068(mActor, pos);
    }

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !enemy->_c48._8.hasProc()) {
        setFailed();
        return;
    }

    const sead::Vector3f target = enemy->_c48._18;
    _48 = target;
    getCurrentChild()->setDynamicParam(_48, "TargetPos");

    if (getCurrentChild()->isFinished()) {
        if (isCurrentChild("攻撃前")) {
            _48 = target;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_48, "TargetPos", -1);
            changeChild("攻撃", &pack);
            return;
        }
        if (isCurrentChild("攻撃") && *mIsUseAfterAttackState_s) {
            sead::Vector3f dir = target - mActor->getMtx().getTranslation();
            dir.normalize();
            if (_54) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_48, "TargetPos", -1);
                changeChild("攻撃ヒット後", &pack);
                return;
            }
            if (!sub_710072FEC4(mActor, dir, 5.0f, nullptr, true, nullptr)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_48, "TargetPos", -1);
                changeChild("攻撃ハズレ後", &pack);
                return;
            }
        }
        setFinished();
        return;
    }

    if (getCurrentChild()->isFailed())
        setFailed();
}

void SeqAnimalAttack::leave_() {
    _54 = false;
    sub_71005DB3EC(mActor);
    if (auto* control = sub_71007398C0(mActor))
        control->_9c = control->_98;
}

void SeqAnimalAttack::loadParams_() {
    getStaticParam(&mIsUseAfterAttackState_s, "IsUseAfterAttackState");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SeqAnimalAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool SeqAnimalAttack::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!getCurrentChild()->isFinished())
        return false;
    if (!*mIsUseAfterAttackState_s)
        return isCurrentChild("攻撃");
    return isCurrentChild("攻撃ヒット後") || isCurrentChild("攻撃ハズレ後");
}

}  // namespace uking::ai
