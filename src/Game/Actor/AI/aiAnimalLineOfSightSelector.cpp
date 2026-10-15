#include "Game/Actor/AI/aiAnimalLineOfSightSelector.h"
#include <math/seadMathCalcCommon.h>
#include <limits>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_7100742478.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalLineOfSightSelector::AnimalLineOfSightSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalLineOfSightSelector::~AnimalLineOfSightSelector() = default;

bool AnimalLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: gear and row enum temporaries and child-selection branches differ.
void AnimalLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    auto* rideable = mActor->m132();
    auto* controller = mActor->getCharacterController();
    if (!nav || !rideable || !controller) {
        setFailed();
        return;
    }
    _6c = true;
    _60.reset(*mGearUpRestrictionFrames_s);
    const sead::Vector3f velocity = controller->get64();
    s32 gear = *mStartGear_s;
    while (gear > *mMinGear_s) {
        const act::Rideable::Gear probe_gear(sead::Mathi::max(gear, 1));
        s32 row = rideable->_130;
        const auto* speed = &act::sUnk_7102603058;
        if (probe_gear != act::Rideable::Gear::_0 && rideable->_170) {
            if (row >= rideable->_178)
                row = 0;
            speed = &rideable->_170->mGears[row][int(probe_gear) - 1];
        }
        if (sub_7100742664(nullptr, nav, &velocity, speed->mSpeed * rideable->_164, 10.0f))
            break;
        --gear;
    }
    switch (gear) {
    case 1: changeChild("Gear1", params); _70 = 1; break;
    case 2: changeChild("Gear2", params); _70 = 2; break;
    case 3: changeChild("Gear3", params); _70 = 3; break;
    case 4: changeChild("Gear4", params); _70 = 4; break;
    default: changeChild("Gear1", params); setFailed(); _70 = 1; break;
    }
}

// NON_MATCHING: gear/row enum temporaries and line-of-sight branch layout differ.
void AnimalLineOfSightSelector::calc_() {
    auto* nav = mActor->m45();
    auto* rideable = mActor->m132();
    auto* controller = mActor->getCharacterController();
    if (!nav || !rideable || !controller) {
        setFailed();
        return;
    }
    if (_6c) {
        _60.update();
        if (_60.value <= std::numeric_limits<f32>::epsilon())
            _6c = false;
    }
    const sead::Vector3f velocity = controller->get64();
    const auto canMove = [&](act::Rideable::Gear gear) {
        s32 row = rideable->_130;
        const auto* speed = &act::sUnk_7102603058;
        if (gear != act::Rideable::Gear::_0 && rideable->_170) {
            if (row >= rideable->_178)
                row = 0;
            speed = &rideable->_170->mGears[row][int(gear) - 1];
        }
        return sub_7100742664(nullptr, nav, &velocity, speed->mSpeed * rideable->_164, 10.0f);
    };
    if (!canMove(act::Rideable::Gear(_70)))
        gearDown();
    else if (!_6c && canMove(act::Rideable::Gear(_70 + 1)))
        gearUp();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void AnimalLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalLineOfSightSelector::loadParams_() {
    getStaticParam(&mStartGear_s, "StartGear");
    getStaticParam(&mMinGear_s, "MinGear");
    getStaticParam(&mMaxGear_s, "MaxGear");
    getStaticParam(&mGearUpRestrictionFrames_s, "GearUpRestrictionFrames");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalLineOfSightSelector::gearDown() {
    const s32 gear = s32(sead::MathCalcCommon<f64>::clamp2(f64(*mMinGear_s), f64(_70 - 1), f64(*mMaxGear_s)));
    if (gear == _70)
        return;
    if (auto* wolf = sead::DynamicCast<act::WolfLink>(mActor))
        wolf->_1698 |= 0x100;
    _70 = gear;
    changeToGear(gear);
}

void AnimalLineOfSightSelector::gearUp() {
    const s32 gear = s32(sead::MathCalcCommon<f64>::clamp2(f64(*mMinGear_s), f64(_70 + 1), f64(*mMaxGear_s)));
    if (gear == _70)
        return;
    if (gear == *mMaxGear_s) {
        if (auto* wolf = sead::DynamicCast<act::WolfLink>(mActor))
            wolf->_1698 &= ~0x100;
    }
    _70 = gear;
    changeToGear(gear);
}

void AnimalLineOfSightSelector::changeToGear(s32 gear) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    switch (gear) {
    case 1:
        changeChild("Gear1", &pack);
        break;
    case 2:
        changeChild("Gear2", &pack);
        break;
    case 3:
        changeChild("Gear3", &pack);
        break;
    case 4:
        changeChild("Gear4", &pack);
        break;
    }
    _6c = true;
    _60 = ksys::Timer(*mGearUpRestrictionFrames_s, *mGearUpRestrictionFrames_s);
}

}  // namespace uking::ai
