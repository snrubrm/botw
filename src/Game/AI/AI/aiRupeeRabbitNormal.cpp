#include "Game/AI/AI/aiRupeeRabbitNormal.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RupeeRabbitNormal::RupeeRabbitNormal(const InitArg& arg) : PreyNormal(arg) {}

RupeeRabbitNormal::~RupeeRabbitNormal() = default;

bool RupeeRabbitNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void RupeeRabbitNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
    const f32 time = sead::GlobalRandom::instance()->getF32Range(0.0f, 45.0f);
    _348 = ksys::Timer(time, time);
    mActor->getLodState()->mFlags10.reset(0x40);
}

void RupeeRabbitNormal::calc_() {
    PreyNormal::calc_();
    if (isCurrentChild("逃走") || isCurrentChild("ダメージ逃走")) {
        auto* lod_state = mActor->getLodState();
        if (!lod_state->mFlags10.isOn(0x40))
            lod_state->mFlags10.set(0x40);
    }
}

void RupeeRabbitNormal::leave_() {
    PreyNormal::leave_();
}

void RupeeRabbitNormal::loadParams_() {
    PreyNormal::loadParams_();
    getMapUnitParam(&mDeleteEndNushiTime_m, "DeleteEndNushiTime");
}

bool RupeeRabbitNormal::m42() {
    if (*mDeleteEndNushiTime_m && !ksys::gdt::getFlag_AnimalMaster_Appearance(false)) {
        _348.update();
        if (_348.value <= sead::Mathf::epsilon())
            return true;
    }
    return false;
}

// NON_MATCHING: the original m2 spills the ActorConstDataAccess::sub_7100D1443C() result (a 32-bit value) to the stack
// and reloads it
// 0x7100554de8
bool Unk_710241b1f8::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    const auto& profile = accessor.getProfile();
    if (profile == "Prey" || profile == "CapturedActor")
        return false;
    if (accessor.getName() == "GameRomHorseNushi") {
        if (accessor.sub_7100D1443C() > 0)
            return accessor.sub_7100D1443C() > 2;
    }
    return true;
}

// NON_MATCHING: regalloc (the original keeps &filter in x19 and the result in x20, recomputing &filter in each branch)
ksys::act::Unk_7100d78e50* RupeeRabbitNormal::m43(s32 idx, bool skip_own_target) {
    if (!_d8)
        return nullptr;

    Unk_710241b1f8 filter;
    if (skip_own_target)
        return sub_7100501B84(idx, &filter);

    if (!_d8->_260[idx])
        return nullptr;
    return ksys::act::sub_7100D7EEE8(&_d8->_260[idx]->_8, &filter);
}

}  // namespace uking::ai
