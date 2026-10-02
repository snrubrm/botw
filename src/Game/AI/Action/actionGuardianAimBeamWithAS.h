#pragma once

#include "Game/AI/Action/actionGuardianAimBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianAimBeamWithAS : public GuardianAimBeam {
    SEAD_RTTI_OVERRIDE(GuardianAimBeamWithAS, GuardianAimBeam)
public:
    explicit GuardianAimBeamWithAS(const InitArg& arg);
    ~GuardianAimBeamWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(const char* name) override;
    f32 m33() override;


    // static_param at offset 0x160
    const bool* mIsChangeable_s{};
    // static_param at offset 0x168
    sead::SafeString mASName_s{};
    bool _178 = false;
};

}  // namespace uking::action
