#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableThrown : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReflectableThrown, ksys::act::ai::Ai)
public:
    explicit ReflectableThrown(const InitArg& arg);
    ~ReflectableThrown() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual float m35() { return _6c; }

protected:
    bool sub_710053DA04(int* out) const;
    void sub_710053DBA0(int type);

    // static_param at offset 0x38
    const bool* mIsReflectByGuard_s{};
    // static_param at offset 0x40
    const bool* mIsReflectByArrow_s{};
    // static_param at offset 0x48
    sead::SafeString mHitColName_s{};
    // static_param at offset 0x58
    const float* mRefSpeedRatioByJustGuard_s{};
    sead::Vector3f _60 = sead::Vector3f::zero;
    float _6c = 0;
    Unk_7102450af8 _70;
};

}  // namespace uking::ai
