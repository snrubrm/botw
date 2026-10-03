#include "Game/AI/Behavior/behaviorGiantGuardWeakPoint.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71025be918.h"
#include "Game/Actor/actGiantEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::behavior {

GiantGuardWeakPoint::GiantGuardWeakPoint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GiantGuardWeakPoint::m8() {
    auto* actor = mActor;
    const f32 delay = *mDelayTime_s;
    _128 = ksys::Timer(delay, delay);
    _134 = sub_71007271D4(actor);
    _135 = _134 && sub_7100726F20(actor);
}

void GiantGuardWeakPoint::loadParams() {
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mDelayTime_s, "DelayTime");
    getStaticParam(&mWeakPointArmorIdx_s, "WeakPointArmorIdx");
    getStaticParam(&mGuardAngleRange_s, "GuardAngleRange");
    getStaticParam(&mRestLifeRate_s, "RestLifeRate");
    getStaticParam(&mGuardStartAS_s, "GuardStartAS");
    getStaticParam(&mGuardLoopAS_s, "GuardLoopAS");
    getStaticParam(&mGuardEndAS_s, "GuardEndAS");
    getStaticParam(&mGuardTgName_s, "GuardTgName");
    getStaticParam(&mPartialBoneName_s, "PartialBoneName");
    getAITreeVariable(&mGiantPartBoneUnit_a, "GiantPartBoneUnit");
}

GiantGuardWeakPoint::~GiantGuardWeakPoint() = default;

// NON_MATCHING: the original converts the unit to its data base with branches (null / `unit + 8`); we get a csel
// (with `Unk_71025be918Data* data = ...` first the addresses of the string members are computed late instead)
bool GiantGuardWeakPoint::m6(sead::Heap* heap) {
    if (!_138.acquire(heap, static_cast<Unk_71025afb58**>(mGiantPartBoneUnit_a), mActor))
        return false;
    return _a8.sub_710001C000(*mTargetBone_s, mGuardTgName_s, mGuardStartAS_s, mGuardLoopAS_s,
                              mGuardEndAS_s, mPartialBoneName_s,
                              sead::DynamicCast<Unk_71025be918>(*_138._0));
}

// NON_MATCHING: block layout of the timer branch (the original lays out the timer update first and keeps `&_128` in
// a register before the compare)
void GiantGuardWeakPoint::m7() {
    if (_134) {
        if (!_135 || !(_135 = sub_7100726F20(mActor))) {
            if (u32(_a8._c - 1) < 2)
                _a8.sub_710001C13C();
            return;
        }
    }

    if (u32(_a8._c - 1) < 2) {
        if (sub_7100625848()) {
            const f32 delay = *mDelayTime_s;
            _128 = ksys::Timer(delay, delay);
        } else if (!(_128.value <= sead::Mathf::epsilon())) {
            _128.update();
        } else {
            const f32 delay = *mDelayTime_s;
            _128 = ksys::Timer(delay, delay);
            _a8.sub_710001C13C();
        }
    } else {
        auto* life = mActor->getLife();
        const f32 life_value = life ? *life : 1.0f;
        if (!(life_value <= mActor->getMaxLife() * *mRestLifeRate_s) || !sub_7100625848()) {
            const f32 delay = *mDelayTime_s;
            _128 = ksys::Timer(delay, delay);
        } else if (!(_128.value <= sead::Mathf::epsilon())) {
            _128.update();
        } else {
            const f32 delay = *mDelayTime_s;
            _128 = ksys::Timer(delay, delay);
            _a8.sub_710001C0D8();
        }
    }
    _a8.sub_710001C1DC();
}

void GiantGuardWeakPoint::m9() {
    _a8.sub_710001C194();
}

// NON_MATCHING: register assignment of the direction vector components
bool GiantGuardWeakPoint::sub_7100625848() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const s32 state = sub_71005D9744(actor);
    if (state != 5 && state != 2)
        return false;
    auto* target = sub_71005D9050(actor);
    if (!target || !ksys::act::isPlayerProfile(target))
        return false;

    bool is_x;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        is_x = accessor.m179();
    }
    if (!is_x) {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (!accessor.x_29())
            return false;
    }

    sead::Vector3f camera_pos;
    if (!ksys::sub_7100D8C6AC(&camera_pos))
        return false;
    sead::Vector3f camera_dir;
    if (!ksys::sub_7100D8C7FC(&camera_dir))
        return false;

    sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (*mWeakPointArmorIdx_s >= 0) {
        if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor)) {
            const s32 idx = *mWeakPointArmorIdx_s;
            if (u32(idx) < 4) {
                auto* part = sead::DynamicCast<ksys::act::Actor>(
                    giant->_14c8._8[idx].getProc(nullptr, nullptr));
                if (part)
                    pos = part->getMtx().getTranslation();
            }
        }
    }

    sead::Vector3f direction = pos - camera_pos;
    direction.normalize();
    return direction.dot(camera_dir) >= std::cos(*mGuardAngleRange_s);
}

}  // namespace uking::behavior
