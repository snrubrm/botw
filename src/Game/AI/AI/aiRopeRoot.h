#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class RopeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RopeRoot, ksys::act::ai::Ai)
public:
    explicit RopeRoot(const InitArg& arg);
    ~RopeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mRopeFlag_m{};
    // map_unit_param at offset 0x40
    const bool* mRopeAlwaysUpdateRigidParam_m{};
    ksys::act::BaseProcLink _48;
    // DynamicCast of mActor to the rope actor class (RTTI used by CSV Rope::m3; not in the repo yet)
    ksys::act::Actor* _58{};
};

}  // namespace uking::ai
