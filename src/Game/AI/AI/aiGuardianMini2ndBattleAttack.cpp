#include "Game/AI/AI/aiGuardianMini2ndBattleAttack.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

GuardianMini2ndBattleAttack::GuardianMini2ndBattleAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMini2ndBattleAttack::~GuardianMini2ndBattleAttack() {
    if (_68.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_68, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _68.reset();
    }
}

bool GuardianMini2ndBattleAttack::init_(sead::Heap* heap) {
    sub_7100412CDC();
    return true;
}

void GuardianMini2ndBattleAttack::sub_7100412CDC() {
    if (mAscendingCurrentName_s.isEmpty())
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(ksys::act::ActorCreator::instance()->createActor(
        mAscendingCurrentName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        nullptr, true, false));
    if (actor)
        _68.acquire(actor, false);
}

void GuardianMini2ndBattleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = ksys::Timer(0, 0);
    sub_7100412DE8();
}

void GuardianMini2ndBattleAttack::sub_7100412DE8() {
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_88);
    if (auto* actor = mActor) {
        actor->getDamageMgr();
        setDamageCallbackTiming(actor, 5, &_b8);
        if (auto* chemical = actor->getChemicalStuff()) {
            chemical->sub_7100D90C2C(true);
            chemical->sub_7100D90CD8(true);
            chemical->sub_7100D90D7C(true);
        }
    }

    mActor->getHomePos(&_58);
    _58.y = mActor->getMtx().getTranslation().y;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘予兆", &params);
}

void GuardianMini2ndBattleAttack::calc_() {
    if (isCurrentChild("戦闘予兆")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            changeChild("戦闘予兆終了");
    } else if (isCurrentChild("戦闘予兆終了")) {
        const f32 value = sub_71005DB4DC(mActor);
        sub_71005DB44C(mActor, value, 0.0f);
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            const f32 time = *mAscendingCurrentTime_s;
            _78.previous_value = _78.value = time;
            _78.rate = -1.0f;
            changeChild("戦闘攻撃");
        }
    } else if (isCurrentChild("戦闘攻撃")) {
        if (!(_78.value <= sead::Mathf::epsilon())) {
            _78.update();
            if (_78.value <= sead::Mathf::epsilon() && _68.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_68, &accessor);
                accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
            }
        }
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (_68.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_68, &accessor);
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
            changeChild("戦闘攻撃終了");
        }
    } else {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && isCurrentChild("戦闘攻撃終了"))
            setFinished();
    }
}

void GuardianMini2ndBattleAttack::leave_() {
    sub_71005DA114(mActor, &_88);
    if (auto* actor = mActor) {
        sub_71005DA114(actor, &_b8);
        if (auto* chemical = actor->getChemicalStuff()) {
            chemical->sub_7100D90C2C(false);
            chemical->sub_7100D90CD8(false);
            chemical->sub_7100D90D7C(false);
        }
    }

    if (_68.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_68, &accessor);
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void GuardianMini2ndBattleAttack::loadParams_() {
    getStaticParam(&mAscendingCurrentName_s, "AscendingCurrentName");
    getStaticParam(&mAscendingCurrentTime_s, "AscendingCurrentTime");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

void GuardianMini2ndBattleAttack::Unk_71023f78a8::call(s32* a1, s32* a2, u32* a3, u32* a4,
                                                       s32* a5, u64 a6) {
    if (mOwner && (mOwner->isCurrentChild("戦闘攻撃") || mOwner->isCurrentChild("戦闘攻撃終了"))) {
        if (*a5 >= 0x14 && *a5 <= 0x16)
            *mOwner->mGuardianMiniChanceTimeState_a = 1;
        if (*a5 == 0xf && !isSlowTimeMaybe())
            *a5 = 2;
        return;
    }

    if (*a5 != -1)
        *a5 = 1;
    if (*a4 != u32(-1))
        *a4 = -1;
}

void GuardianMini2ndBattleAttack::Unk_71023f78e0::call(s32* a1, s32* a2, u32* a3, u32* a4,
                                                       s32* a5, u64 a6) {
    if (mOwner && (mOwner->isCurrentChild("戦闘攻撃") || mOwner->isCurrentChild("戦闘攻撃終了")))
        return;

    if (*a4 >= 9 && *a4 <= 11) {
        *a2 = 0;
        *a4 = -1;
        *a5 = 1;
    }
}

}  // namespace uking::ai
