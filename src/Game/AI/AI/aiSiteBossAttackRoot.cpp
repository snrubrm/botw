#include "Game/AI/AI/aiSiteBossAttackRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {


SiteBossAttackRoot::SiteBossAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossAttackRoot::~SiteBossAttackRoot() = default;

bool SiteBossAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossAttackRoot::calc_() {
    if (!sead::DynamicCast<ksys::act::Actor>(_60[0].getProc(nullptr, nullptr)))
        sub_7100571EB4(*mEquipWeapon_s, 0);
    if (sub_71005DBB60(mActor, 0) == -1)
        sub_710057201C(*mEquipWeapon_s);
    switch (*mEquipWeapon_s) {
    case 0:
        sub_71005721F4();
        break;
    case 1:
        sub_7100572360();
        break;
    case 2:
        sub_71005724C8();
        break;
    case 3:
        sub_7100572634();
        break;
    }
}

void SiteBossAttackRoot::sub_7100571EB4(s32 kind, s32 slot) {
    if (kind == 0) {
        sub_71005721F4();
        return;
    }
    if (slot > 1)
        return;

    auto& handle = _40[slot];
    if (handle.isAllocatedOrFailed()) {
        if (!handle.hasProcCreationFailed()) {
            if (handle.isProcReady()) {
                auto* actor = sead::DynamicCast<ksys::act::Actor>(handle.getProc());
                _60[slot].acquire(actor, false);
            }
            return;
        }
        handle.deleteProcIfFailed();
    }

    if (kind > 4)
        return;
    ksys::act::ActorCreator::instance()->requestCreateActor(
        sWeaponNames[kind], ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &handle,
        nullptr, nullptr, 1);
}

void SiteBossAttackRoot::sub_710057201C(s32 kind) {
    if (kind == 0 || kind > 3)
        return;

    if (!sead::DynamicCast<ksys::act::Actor>(_60[0].getProc(nullptr, nullptr)))
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(_60[0].getProc(nullptr, nullptr));
    auto* weapon = sead::DynamicCast<act::Weapon>(actor);
    if (_40[0].isProcReady())
        _40[0].releaseAndWakeProc();
    else if (weapon)
        weapon->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    sub_71005D8A30(mActor, weapon, false);
}

void SiteBossAttackRoot::sub_71005721F4() {
    if (isCurrentChild("弓装備"))
        return;

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.resetBit(1);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("弓装備", &pack);
}

void SiteBossAttackRoot::sub_7100572360() {
    if (isCurrentChild("小剣装備"))
        return;

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.setBit(1);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("小剣装備", &pack);
}

void SiteBossAttackRoot::sub_71005724C8() {
    if (isCurrentChild("大剣装備"))
        return;

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.resetBit(1);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("大剣装備", &pack);
}

void SiteBossAttackRoot::sub_7100572634() {
    if (isCurrentChild("槍装備"))
        return;

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.resetBit(1);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("槍装備", &pack);
}

void SiteBossAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossAttackRoot::loadParams_() {
    getStaticParam(&mEquipWeapon_s, "EquipWeapon");
}

}  // namespace uking::ai
