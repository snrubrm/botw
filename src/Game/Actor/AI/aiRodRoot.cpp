#include "Game/Actor/AI/aiRodRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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
