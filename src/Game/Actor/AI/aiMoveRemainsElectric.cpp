#include "Game/Actor/AI/aiMoveRemainsElectric.h"
#include "Game/Actor/aiUnk_710073033C.h"
#include "Game/Actor/actRemains.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

MoveRemainsElectric::MoveRemainsElectric(const InitArg& arg) : RailMoveRemains(arg) {}

// NON_MATCHING: runtime-cast control flow is simplified before the unrolled part cleanup.
MoveRemainsElectric::~MoveRemainsElectric() {
    if (_308.hasProc()) {
        ksys::act::ActorLinkConstDataAccess actor;
        ksys::act::acquireActor(&_308, &actor);
        actor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _308.reset();
    }
    if (auto* remains = sead::DynamicCast<act::Remains>(mActor)) {
        auto* parts = remains->m101();
        for (auto& part : _a8) {
            if (parts) {
                auto& link = parts->getActorPartsActor(part.mActorName);
                if (link.hasProc()) {
                    ksys::act::ActorLinkConstDataAccess actor;
                    ksys::act::acquireActor(&link, &actor);
                    actor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
            }
            remains->_b98.sub_7100D3CFEC(part.mActorName);
        }
    }
}

bool MoveRemainsElectric::init_(sead::Heap* heap) {
    if (!RailMoveRemains::init_(heap))
        return false;
    if (mActor->getName().findIndex("_Far") == -1) {
        sub_71004B1A00();
        if (!ksys::gdt::getFlag_Enter_RemainsElectric(false) && *mIsJoinRemainsBattle_m)
            sub_71004B1C40(heap);
    }
    return true;
}

// NON_MATCHING: the repeated name search retains different SafeString setup.
void MoveRemainsElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
    if (mActor->getName().findIndex("_Far") == -1 && !_318) {
        _320.sub_7100720AF4();
        _320._10 = 4;
        _320._8 = 100;
        _318 = true;
    }
    sub_71004B2288();
    if (mActor->getName().findIndex("_Far") == -1 &&
        !ksys::gdt::getFlag_Enter_RemainsElectric(false) && *mIsJoinRemainsBattle_m) {
        _370.initWithName(mActor, "Demo347_3", "Demo");
        _370.loadEvent();
    }
}

// NON_MATCHING: the repeated name search retains different SafeString setup.
bool MoveRemainsElectric::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!RailMoveRemains::reenter_(other, true))
        return false;
    if (!sead::DynamicCast<MoveRemainsElectric>(other))
        return false;
    if (mActor->getName().findIndex("_Far") == -1 && !_318) {
        _320.sub_7100720AF4();
        _320._10 = 4;
        _320._8 = 100;
        _318 = true;
    }
    sub_71004B2288();
    if (mActor->getName().findIndex("_Far") == -1 &&
        !ksys::gdt::getFlag_Enter_RemainsElectric(false) && *mIsJoinRemainsBattle_m) {
        _370.initWithName(mActor, "Demo347_3", "Demo");
        _370.loadEvent();
    }
    return true;
}

void MoveRemainsElectric::leave_() {
    for (auto& part : _a8)
        part.mHandle.fadeXLink();
    if (_370.mEventFlow)
        _370.unloadEvent();
    RailMoveRemains::leave_();
}

// NON_MATCHING: the native branches acquire the actor separately.
void MoveRemainsElectric::calc_() {
    sub_71004B2718();
    const bool moving = isCurrentChild("移動");
    if (_308.hasProc()) {
        ksys::act::ActorLinkConstDataAccess actor;
        ksys::act::acquireActor(&_308, &actor);
        if (moving) {
            if (actor.isStateSleep())
                actor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        } else {
            if (actor.isStateCalc())
                actor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    if (mActor->getName().findIndex("_Far") == -1)
        _320.sub_7100720B28();
    if (_370.mEventFlow && _370.mLink._8 && isCurrentChild("一時停止")) {
        if (_31c > 0.0f)
            ksys::Timer::update(&_31c, -1.0f);
        if (_31c <= 0.0f)
            _370.sendMessageToEventMgrActor(mActor);
    }
    RailMoveRemains::calc_();
}

bool MoveRemainsElectric::m39() {
    if (mActor->getName().endsWith("_Far") || ksys::gdt::getFlag_Enter_RemainsElectric(false) ||
        !*mIsJoinRemainsBattle_m || !ksys::gdt::getFlag_Electric_Relic_Battle(false) ||
        !mActor->m101())
        return false;
    for (const auto& part : _a8) {
        if (part.mLife > 0)
            return false;
    }
    _31c = *mDemoCallWaitTime_s;
    return true;
}

void MoveRemainsElectric::loadParams_() {
    RailMoveRemains::loadParams_();
    getStaticParam(&mReactiveRange_s, "ReactiveRange");
    getStaticParam(&mDemoCallWaitTime_s, "DemoCallWaitTime");
    getStaticParam(&mCannonOffset_s, "CannonOffset");
    getStaticParam(&mWeakPointOffset_s, "WeakPointOffset");
    getMapUnitParam(&mIsJoinRemainsBattle_m, "IsJoinRemainsBattle");
}

bool MoveRemainsElectric::m40() {
    auto& player = uking::act::PlayerInfo::getSomeProcLink();
    if (!player.hasProc())
        return false;
    return !sub_710073033C(mActor, &player, *mReactiveRange_s);
}

f32 MoveRemainsElectric::m43() {
    if (auto* as_list = mActor->getASList()) {
        if (as_list->_14.isValid())
            return as_list->sub_710115D2D4().length();
    }
    return RailMoveRemains::m43();
}

}  // namespace uking::ai
