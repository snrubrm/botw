#pragma once

#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SignalSendingMagneStickAcceptor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SignalSendingMagneStickAcceptor, ksys::act::ai::Ai)
public:
    explicit SignalSendingMagneStickAcceptor(const InitArg& arg);
    ~SignalSendingMagneStickAcceptor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_710056BD78(ksys::act::ActorConstDataAccess* acc);

    // map_unit_param at offset 0x38
    const float* mMagneStickMaxSearchDistance_m{};
};

}  // namespace uking::ai
