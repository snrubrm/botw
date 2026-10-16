#include "Game/Actor/AI/aiRodRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

RodRoot::RodRoot(const InitArg& arg) : WeaponRootAI(arg), _f0() {}

RodRoot::~RodRoot() {
    xlink::kill(_f0.mELink);
}

bool RodRoot::init_(sead::Heap* heap) {
    *mMagicCreateUnit_a = &_118;
    return WeaponRootAI::init_(heap);
}

// NON_MATCHING: the original keeps the 1-based counter (`sub w1, w20, #1` per call); clang rewrites the loop
// around the 0-based value
void RodRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor)) {
        if (auto* rod = weapon->getParam()->getRes().mGParamList->getRod())
            _114 = rod->mChargeMagicNum.ref();
    }
    _110 = -1;
    sub_71005531E8();
    sub_71005535F8();
    for (s32 i = 1; i <= _114; ++i) {
        sub_7100553E5C(i - 1);
        if (i > 7)
            break;
    }
}

void RodRoot::leave_() {
    if (_118._8.isAllocatedOrFailed())
        _118._8.deleteProc();
    for (s32 i = 0; i < _114; ++i) {
        if (i <= 7) {
            if (_118._18[i].isAllocatedOrFailed())
                _118._18[i].deleteProc();
        }
    }
    WeaponRootAI::leave_();
    _110 = -1;
}

void RodRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

void RodRoot::calc_() {
    WeaponRootAI::calc_();
    sub_71005539C0();
    sub_71005531E8();
    sub_7100553CF0();
}

// 0x71005531e8
void RodRoot::sub_71005531E8() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* as_list = weapon->getASList();
    if (!as_list)
        return;

    if (auto* parent = weapon->getParentActor()) {
        auto* chemical = parent->getChemicalStuff();
        if (chemical && chemical->_c0 == 1) {
            as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
            return;
        }
        if (ksys::act::isEnemyProfile(parent)) {
            auto* enemy = sead::DynamicCast<act::Enemy>(parent);
            if (enemy && enemy->_e84.isOnBit(16)) {
                if (_110 == 2)
                    return;
                as_list->sub_710115B01C(0, 1, true);
                _110 = 2;
                return;
            }
        }
    }

    f32 rate = 1.0f;
    as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
    if (weapon->_d38) {
        const s32 max = weapon->_d38->sub_71002EF74C();
        const s32 charge = weapon->_d38 ? s32(weapon->_d38->_14) : 0;
        if (max > 0 && max > charge)
            rate = static_cast<f32>(charge) / static_cast<f32>(max);
    }
    if (auto* rod = sead::DynamicCast<act::Weapon>(mActor)) {
        if (!rod->_d38 || !(rod->_d38->_18 & 1))
            rate = 1.0f;
    }

    f32 value = rate;
    bool ready = true;
    if (auto* rod = sead::DynamicCast<act::Weapon>(mActor)) {
        auto* charge = rod->_d38;
        ready = charge && ((charge->_18 & 1) ? !(charge->_10 > 0.0f) : charge->sub_71002E999C());
    }
    if (ready) {
        if (rate >= 1.0f) {
            if (_110 == 1)
                return;
            if (as_list->sub_710115AA68("ChemFull"))
                as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemFull", 0, 1, true);
            _110 = 1;
            return;
        }
    } else {
        value = 0.0f;
    }

    as_list = weapon->getASList();
    if (_110 != 0) {
        if (as_list->sub_710115AA68("ChemCharge"))
            as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemCharge", 0, 1, true);
        _110 = 0;
    }
    if (as_list->x_7(0, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        as_list->sub_710115F1D8(0, 1, value);
}

// 0x71005535f8
// NON_MATCHING: stack slots / scheduling of the position and key setup.
void RodRoot::sub_71005535F8() {
    _118._8.deleteProc();
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* rod = weapon->getParam()->getRes().mGParamList->getRod();
    if (!rod || rod->mMagicName.ref().isEmpty())
        return;

    s32 scale_time;
    f32 scale;
    f32 range;
    const char* body_name;
    if (weapon->m142()) {
        scale_time = rod->mScaleTimeByEnemy.ref();
        scale = rod->mMagicRadiusByEnemy.ref();
        range = rod->mMagicRangeByEnemy.ref();
        body_name = "AtkEnemyBody";
    } else {
        scale_time = rod->mScaleTime.ref();
        scale = rod->mMagicRadius.ref();
        range = rod->mMagicRange.ref();
        body_name = "AtkPlayerBody";
    }
    const s32 power = rod->mMagicPower.ref();

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    pack->add(power, "AttackPower");
    pack->add(static_cast<f32>(scale_time), "ScaleTime");
    pack->add(range, "Range");
    ksys::act::ActorCreator::addScale(pack, scale);
    pack->add(sead::SafeString(body_name), "RigidBodyName");
    u32 flags;
    if ((weapon->_af8._0 | 1) == 7)
        flags = weapon->_af8._4;
    else if (weapon->_d08)
        flags = weapon->_cf4;
    else
        flags = weapon->_c20._4;
    pack->add(bool(flags >> 30 & 1), "AttackAttrEventKill");
    pack->addResourceLane(2);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        rod->mMagicName.ref().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_118._8,
        &pack, nullptr, 2);
}

// 0x7100553e5c
// NON_MATCHING: stack slots / scheduling of the position and key setup; the index test is scheduled earlier.
void RodRoot::sub_7100553E5C(s32 idx) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* rod = weapon->getParam()->getRes().mGParamList->getRod();
    if (!rod || idx >= 8 || rod->mMagicName.ref().isEmpty())
        return;

    const f32 scale = rod->mMagicRadius.ref();
    const s32 scale_time = rod->mScaleTime.ref();
    const f32 range = rod->mMagicRange.ref();
    const s32 power = rod->mMagicPower.ref();
    auto& handle = _118._18[idx];
    handle.deleteProc();
    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    pack->add(power, "AttackPower");
    pack->add(static_cast<f32>(scale_time), "ScaleTime");
    pack->add(range, "Range");
    ksys::act::ActorCreator::addScale(pack, scale);
    pack->add(sead::SafeString("AtkPlayerBody"), "RigidBodyName");
    pack->addResourceLane(2);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        rod->mMagicName.ref().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &handle,
        &pack, nullptr, 2);
}

// 0x71005539c0
void RodRoot::sub_71005539C0() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;

    if (weapon->m188()) {
        xlink::kill(_f0.mELink);
        return;
    }

    if (auto* rod = sead::DynamicCast<act::Weapon>(mActor)) {
        auto* charge = rod->_d38;
        if (!charge || ((charge->_18 & 1) ? charge->_10 > 0.0f : !charge->sub_71002E999C())) {
            xlink::kill(_f0.mELink);
            sub_71012412E4(weapon, 0x1b, 0.0f, false);
            return;
        }
    }

    f32 value = 0.0f;
    s32 max = 0;
    if (auto* charge = weapon->_d38) {
        value = charge->_14;
        max = charge->sub_71002EF74C();
    }
    sub_71012412E4(weapon, 0x1b, value / max, false);
    if (!_f0.mELink.isActive())
        xlinkSearchAndEmit(weapon, "Active", 2, &_f0);
}

// NON_MATCHING: the original reloads handle->mUnit through the array base (ldr [x22, #0x130]) while we
// reuse the element pointer already computed for the call (one register differs).
void RodRoot::sub_7100553CF0() {
    if (_118._8.hasProcCreationFailed() || !_118._8.isAllocatedOrFailed()) {
        if (_118._8.hasProcCreationFailed())
            _118._8.deleteProcIfFailed();
        sub_71005535F8();
    }
    for (s32 i = 0; i < _114; ++i) {
        if (i <= 7) {
            auto& handle = _118._18[i];
            if (handle.hasProcCreationFailed() || !handle.isAllocatedOrFailed()) {
                if (handle.hasProcCreationFailed())
                    handle.deleteProcIfFailed();
                sub_7100553E5C(i);
            }
        }
    }
}

}  // namespace uking::ai
