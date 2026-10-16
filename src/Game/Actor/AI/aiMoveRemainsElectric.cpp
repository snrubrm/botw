#include "Game/Actor/AI/aiMoveRemainsElectric.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "Game/Actor/aiUnk_710073033C.h"
#include "Game/Actor/actRemains.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

// File-scope names set up by this file's static initializer 0x71004b2f2c (placeholder names = addresses).
static const sead::SafeString sUnk_71025bab88 = "RemainsElectricCannon";
static const sead::SafeString sUnk_71025bab98 = "RemainsElectric_WeakPoint";
static const sead::SafeString sUnk_71025baba8 = "WeakPoint";
static const sead::SafeString sUnk_71025babb8 = "DamageFoot";
// Weak point name suffixes and the bones they are attached to.
static const sead::SafeString sUnk_71025babc8[4] = {"FL", "FR", "BL", "BR"};
static const sead::SafeString sUnk_71025bac08[4] = {"Arm_10_L", "Arm_10_R", "Leg_10_L", "Leg_10_R"};

// NON_MATCHING: the original zeroes 0x80..0x308 with one memset before the (out-of-line) SafeArray
// constructor; ours stores the params separately (`_a8{}` gives the memset but inlines the constructor).
MoveRemainsElectric::MoveRemainsElectric(const InitArg& arg) : RailMoveRemains(arg) {
    for (s32 i = 0; i < 4; ++i) {
        _a8[i].mActorName.format("%s_%s", sUnk_71025baba8.cstr(), sUnk_71025babc8[i].cstr());
        _a8[i].mBoneName.format("%s", sUnk_71025bac08[i].cstr());
    }
}

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

// Creates the cannon (RemainsElectricCannon) at the actor, binds it to the Spine_1 bone with CannonOffset
// and links it as a calc child (_308).
// NON_MATCHING: base address of the static name (data layout) and the offset load order in the matrix.
void MoveRemainsElectric::sub_71004B1A00() {
    auto* actor = mActor;
    ksys::act::BaseProcLink link;
    link.acquire(actor, false);

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
    auto* cannon = ksys::act::ActorCreator::instance()->createActor(
        sUnk_71025bab88.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(cannon)) {
        if (auto* binding = enemy->_f38) {
            binding->x(mActor);
            binding->_30.getKey() = {};
            binding->_28 = "Spine_1";
            const auto& offset = *mCannonOffset_s;
            binding->_68 = sead::Matrix34f(1, 0, 0, offset.x, 0, 1, 0, offset.y, 0, 0, 1, offset.z);
        }
        enemy->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
        enemy->setConnectedCalcParent(actor, false);
        _308.acquire(enemy, false);
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

// Starts the weak point AS (WeakPoint<suffix>) in slots 0 .. 3, except for the far LOD actor.
// NON_MATCHING: the base address of the file-scope name table (our .bss places the TU statics differently).
void MoveRemainsElectric::sub_71004B2288() {
    if (mActor->getName().findIndex("_Far") != -1)
        return;
    for (s32 i = 0; i < 4; ++i) {
        sead::FormatFixedSafeString<32> name("WeakPoint%s", sUnk_71025babc8[i].cstr());
        changeAS(name.cstr(), false, 2, i);
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
