#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class BeamExplodeBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BeamExplodeBase, ksys::act::ai::Ai)
public:
    explicit BeamExplodeBase(const InitArg& arg);
    ~BeamExplodeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    virtual void m34();

protected:
    // static_param at offset 0x38
    const float* mMaxDistance_s{};
    // static_param at offset 0x40
    const bool* mIsDelete_s{};
    ksys::phys::RigidBody* _48{};
    ksys::phys::RigidBody* _50{};
};

}  // namespace uking::ai
