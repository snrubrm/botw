#include "Game/AI/AI/aiLastBossNormalWarpRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

// 0x71002c67e8 / 0x71002c65c8 (declaration only; the first argument of the former is 0 here).
void sub_71002C67E8(f32 a1, ksys::act::Actor* actor, bool a3);
void sub_71002C65C8(ksys::act::Actor* actor, bool a1, bool a2);

namespace uking::ai {

LastBossNormalWarpRoot::LastBossNormalWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
LastBossNormalWarpRoot::~LastBossNormalWarpRoot() {
    ;
}

bool LastBossNormalWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossNormalWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->sub_71002D3944();
}

bool LastBossNormalWarpRoot::isChangeable() const {
    return false;
}

void LastBossNormalWarpRoot::leave_() {
    if (*mIsReturnHome_d && !*mIsKeepDisableDraw_s) {
        sub_71002C67E8(0.0f, mActor, *mIsPartsWarpEffectSync_d);
        sub_71002C65C8(mActor, false, *mIsPartsWarpEffectSync_d);
        m38();
        return;
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (auto* part : enemy->_1128.mList) {
            if (!part->mLink.hasProc())
                continue;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&part->mLink, &accessor);
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1518 = 0;
        boss->sub_71002D39D8();
    }
}

void LastBossNormalWarpRoot::loadParams_() {
    getStaticParam(&mIsKeepDisableDraw_s, "IsKeepDisableDraw");
    getStaticParam(&mSleepPartsActorName_s, "SleepPartsActorName");
    getDynamicParam(&mIsReturnHome_d, "IsReturnHome");
    getDynamicParam(&mIsForceWarp_d, "IsForceWarp");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossNormalWarpRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child || (!child->isFinished() && !child->isFailed()))
        return;

    if (isCurrentChild("ワープ前行動")) {
        m36();
    } else if (isCurrentChild("ワープ")) {
        m37();
    } else if (isCurrentChild("ワープ後行動")) {
        if (child->isFinished() && !*mIsReturnHome_d)
            setFinished();
        else
            setFailed();
    }
}

void LastBossNormalWarpRoot::m34() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(*mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ前行動", &pack);
}

void LastBossNormalWarpRoot::m35(ksys::act::ai::InlineParamPack* params) {
    params->addBool(*mIsReturnHome_d, "IsReturnHome", -1);
    params->addBool(*mIsForceWarp_d, "IsForceWarp", -1);
}

void LastBossNormalWarpRoot::m36() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(*mIsPartsActorTgOn_d, "IsPartsActorTgOn", -1);
    pack.addBool(*mIsReturnHome_d && *mIsKeepDisableDraw_s, "IsKeepDisableDraw", -1);
    m35(&pack);
    changeChild("ワープ", &pack);
}

void LastBossNormalWarpRoot::m37() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(*mIsReturnHome_d && *mIsKeepDisableDraw_s, "IsKeepDisableDraw", -1);
    pack.addBool(*mIsPartsActorTgOn_d, "IsPartsActorTgOn", -1);
    pack.addBool(*mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ後行動", &pack);
}

void LastBossNormalWarpRoot::m38() {
    sub_71007A3540(mActor);
    if (*mIsPartsActorTgOn_d) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            for (auto* part : enemy->_1128.mList) {
                if (!part->mLink.hasProc())
                    continue;
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&part->mLink, &accessor);
                if (accessor.isStateCalc()) {
                    mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                        ksys::MessageType(0x8000030), nullptr, true);
                    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
                        boss->_1518 = 0;
                }
            }
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->sub_71002D39D8();
}

}  // namespace uking::ai
