#include "Game/AI/Action/actionLastBossFlyWait.h"
#include "KingSystem/System/VFR.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossFlyWait::LastBossFlyWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossFlyWait::~LastBossFlyWait() = default;

bool LastBossFlyWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossFlyWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsResetEndTime_d || _84.value <= 0.0f) {
        _78.reset(*mTime_s);
        const f32 range = *mEndTimeRandRange_s;
        const f32 rand = sead::GlobalRandom::instance()->getF32();
        const f32 end_time = *mEndTime_s + range * rand;
        _84.reset(end_time);
    }
    _90 = mActor->getMtx().m[1][3] + *mBaseYOffset_s;
    _94 = 0.5f;
    _98 = 0;
    playAS(mWaitAS_s.cstr(), true, 0, 0, -1.0f);
    if (*mEndTime_s <= 0.0f)
        setFinished();
}

void LastBossFlyWait::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void LastBossFlyWait::loadParams_() {
    getStaticParam(&mDamageCounter_s, "DamageCounter");
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mMoveRate_s, "MoveRate");
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mEndTimeRandRange_s, "EndTimeRandRange");
    getStaticParam(&mBaseYOffset_s, "BaseYOffset");
    getStaticParam(&mIsChemicalOff_s, "IsChemicalOff");
    getStaticParam(&mWaitAS_s, "WaitAS");
    getDynamicParam(&mIsResetEndTime_d, "IsResetEndTime");
}

void LastBossFlyWait::calc_() {
    _78.update();
    if (_78.value <= sead::Mathf::epsilon()) {
        _78 = ksys::Timer(*mTime_s, *mTime_s);
        _94 = -_94;
    }
    if (auto* controller = mActor->getCharacterController()) {
        sead::Matrix34f mtx;
        m32(&mtx);
        controller->sub_7100F5F938(mtx);
    }
    if (*mIsChemicalOff_s) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD780(mActor, 0x3b, &query, 0, 0))
            m34();
    }
    if (auto* manager = sub_710072BA90(mActor)) {
        if (s32(manager->getDamage()) >= 1) {
            const s32 count = _98++;
            if (*mDamageCounter_s >= 1 && *mDamageCounter_s <= count)
                setFinished();
        }
    }
    if (*mEndTime_s >= 0.0f) {
        _84.update();
        if (_84.value <= sead::Mathf::epsilon())
            setFinished();
    }
}

bool LastBossFlyWait::isChangeable() const {
    return true;
}

// NON_MATCHING: matrix/velocity registers differ and discarded Y scaling is removed.
void LastBossFlyWait::m32(sead::Matrix34f* mtx) {
    auto matrix = mActor->getMtx();
    const auto initial_position = matrix.getTranslation();
    auto position = initial_position;
    position.y += (_90 + *mAmplitude_s * _94 - position.y) * *mMoveRate_s;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (!velocity.isNan() && (velocity.x != 0.0f || velocity.z != 0.0f)) {
            velocity *= 1.0f / 30.0f;
            velocity.y = 0.0f;
            auto* vfr = ksys::VFR::instance();
            const f32 frame_rate = vfr->getFrameRate();
            const f32 factor = frame_rate * vfr->getDeltaTime();
            velocity.x = (factor * velocity.x) * 0.98f;
            velocity.z = (factor * velocity.z) * 0.98f;
            position += velocity;
        }
    }
    if (position.isNan())
        position = initial_position;
    matrix.setTranslation(position);
    *mtx = matrix;
}

}  // namespace uking::action
