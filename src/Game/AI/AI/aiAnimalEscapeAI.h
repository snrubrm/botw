#pragma once

#include "Game/AI/AI/aiAnimalRoamBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AnimalEscapeAI : public AnimalRoamBase {
    SEAD_RTTI_OVERRIDE(AnimalEscapeAI, AnimalRoamBase)
public:
    explicit AnimalEscapeAI(const InitArg& arg);
    ~AnimalEscapeAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34(const sead::Vector3f* pos) override;
    virtual void m36();
    virtual bool m37();
    virtual void m38(ksys::act::ai::InlineParamPack* params) {}

    // 0x7100305314 / 0x7100305ae0 (placeholder names)
    void changeToEscape();
    void changeToStuckOnTerrain();
    // 0x71003051c0 (placeholder name)
    void sub_71003051C0();

protected:
    // static_param at offset 0xa8
    const int* mNumTimesAllowStuck_s{};
    // static_param at offset 0xb0
    const float* mContinueDistance_s{};
    // static_param at offset 0xb8
    const float* mShouldEscapeDistance_s{};
    // static_param at offset 0xc0
    const float* mShouldEscapeDistanceRand_s{};
    // static_param at offset 0xc8
    const float* mPenaltyScale_s{};
    // static_param at offset 0xd0
    const float* mNavMeshRadiusScale_s{};
    // static_param at offset 0xd8
    const float* mFramesStuckOnTerrainAction_s{};
    // static_param at offset 0xe0
    const bool* mIsSendGoalPos_s{};
    // static_param at offset 0xe8
    const bool* mIsUseBeforeAction_s{};
    // static_param at offset 0xf0
    const bool* mIsDynamicallyOffsetNavChar_s{};
    // dynamic_param at offset 0xf8
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x100
    bool* mIsUseTerritory_a{};
    sead::Vector3f _108;
    sead::Vector3f _114{0, 0, 0};
    sead::Vector3f _120;
    f32 _12c = 1.0f;
    ksys::Timer _130{150, 150};
    ksys::Timer _13c;
    f32 _148 = 0;
    s32 _14c = 0;
    bool _150 = false;
};

}  // namespace uking::ai
