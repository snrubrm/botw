#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleLineBeam : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SimpleLineBeam, ksys::act::ai::Action)
public:
    explicit SimpleLineBeam(const InitArg& arg);
    ~SimpleLineBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const int* mType_s{};
    // static_param at offset 0x28
    const bool* mIsGuarantee_s{};
    // static_param at offset 0x30
    const bool* mIsGuardPierces_s{};
    // static_param at offset 0x38
    const bool* mIsSetAtIgnoreObstacle_s{};
    void* _40{};
    int _48 = 0;
};

}  // namespace uking::action
