#pragma once

#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveRemains : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveRemains, ksys::act::ai::Ai)
public:
    explicit RailMoveRemains(const InitArg& arg);
    ~RailMoveRemains() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    virtual ksys::map::Rail* m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual bool m39();
    virtual bool m40();
    virtual f32 m41();
    virtual f32 m42();
    virtual f32 m43();
    virtual void m44();
    virtual Unk_71024f15c0* m45();
    virtual void m46();
    virtual void m47(sead::Vector3f* out);

protected:
    // static_param at offset 0x38
    const float* mReactivateTime_s{};
    // static_param at offset 0x40
    const float* mFrontCheckMinDist_s{};
    // static_param at offset 0x48
    const float* mFrontDirUpdateInterval_s{};
    // static_param at offset 0x50
    const float* mSpeedScale_s{};
    // static_param at offset 0x58
    const float* mInitPosByRailRatio_s{};
    Unk_71024f15c0* _60{};
    sead::Vector3f _68;
    sead::Vector3f _74 = {0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(RailMoveRemains, 0x80);

}  // namespace uking::ai
