#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonFarAttackRootOnWall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonFarAttackRootOnWall, ksys::act::ai::Ai)
public:
    explicit GanonFarAttackRootOnWall(const InitArg& arg);
    ~GanonFarAttackRootOnWall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003E8884();

    void sub_71003E9150();

protected:
    // static_param at offset 0x38
    const int* mPillarMax_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mViewPos_d{};
    int _50{};
    int _54{};
};

}  // namespace uking::ai
