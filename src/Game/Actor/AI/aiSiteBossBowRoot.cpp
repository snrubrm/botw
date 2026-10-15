#include "Game/Actor/AI/aiSiteBossBowRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

void sub_71002C65C8(ksys::act::Actor* actor, bool a1, bool a2);

namespace uking::ai {

static const char* const sUnitNames[] = {"Unit_A", "Unit_B", "Unit_C", "Unit_D"};

// 0x7100575448: deletes the parts actor of the unit
void SiteBossBowRoot::sub_7100575448(s32 index) {
    sead::SafeString name = u32(index) < 4 ? sUnitNames[index] : "";
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->getActorPartsActor(name).hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&boss->getActorPartsActor(name), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        boss->sub_7100D3CFEC(name);
    }
}

void SiteBossBowRoot::sub_7100576744(s32 index) {
    sead::SafeString name = u32(index) < 4 ? sUnitNames[index] : "";
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->getActorPartsActor(name).hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&boss->getActorPartsActor(name), &accessor);
            if (accessor.isStateSleep())
                accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
}

SiteBossBowRoot::SiteBossBowRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossBowRoot::~SiteBossBowRoot() {
    sub_7100575448(0);
    sub_7100575448(1);
    sub_7100575448(2);
    sub_7100575448(3);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066BC04();
}

bool SiteBossBowRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossBowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss) {
        if (_120 == 1)
            boss->_1558.set(0x20000);
        if (ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R))
            boss->_1534 = 8;
        else
            boss->_1534 = *mIsRemainBoss_s ? 0 : 4;
        boss->_1558.set(0x800000);
    }

    bool disable_draw = !ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R);
    if (!disable_draw) {
        auto* life = boss->getLife();
        disable_draw = life && *life < 1;
    }
    if (disable_draw && ksys::gdt::getFlag_DisableDraw_ChildDevice(false)) {
        _120 = 2;
    } else if (_120 == 0) {
        if (boss) {
            for (s32 i = 0; i < 4; ++i)
                boss->_1560.sub_710066D708(i);
            for (s32 i = 0; i < 4; ++i)
                boss->_1560.sub_710066C13C(nullptr, i);
            boss->_1558.set(0x20000);
        }
        _120 = 1;
    }

    if (ksys::gdt::getFlag_DisableDraw_ChildDevice(false) ||
        (getCurrentChild() && isCurrentChild("出現デモ待ち"))) {
        sub_71002C65C8(mActor, true, true);
        _124 = true;
    } else {
        _124 = false;
    }
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7))
        boss->_1558.reset(0x40000);
}

void SiteBossBowRoot::calc_() {
    SiteBossRoot::calc_();
    if (getCurrentChild() && isCurrentChild("出現デモ待ち")) {
        _124 = true;
        sub_71002C65C8(mActor, true, true);
        return;
    }
    if (_120 == 0) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            boss->_1560.sub_710066D708(0);
            boss->_1560.sub_710066D708(1);
            boss->_1560.sub_710066D708(2);
            boss->_1560.sub_710066D708(3);
            boss->_1560.sub_710066C13C(nullptr, 0);
            boss->_1560.sub_710066C13C(nullptr, 1);
            boss->_1560.sub_710066C13C(nullptr, 2);
            boss->_1560.sub_710066C13C(nullptr, 3);
            if (!boss->_1558.isOn(0x100))
                boss->_1558.set(0x20000);
        }
        _120 = 1;
    } else if (_120 == 1) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            boss->_1560.sub_710066C13C(nullptr, 0);
            boss->_1560.sub_710066C13C(nullptr, 1);
            boss->_1560.sub_710066C13C(nullptr, 2);
            boss->_1560.sub_710066C13C(nullptr, 3);
            if (!boss->_1558.isOn(0x100))
                boss->_1558.set(0x20000);
        }
        _120 = 2;
    }
}

void SiteBossBowRoot::leave_() {
    SiteBossRoot::leave_();
    if (!isActorGoingBackToRootAi()) {
        _120 = 0;
        sub_7100576744(0);
        sub_7100576744(1);
        sub_7100576744(2);
        sub_7100576744(3);
    }
    if (!mActor->getRootAi()->isActorDeletedOrDeleting() && _124) {
        _124 = false;
        sub_71002C65C8(mActor, false, true);
    }
}

void SiteBossBowRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mArrowRainAttackPower_s, "ArrowRainAttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mReflectArrowAttackPower_s, "ReflectArrowAttackPower");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai
