#pragma once

#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoBeastGanonGrudgeDrop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoBeastGanonGrudgeDrop, ksys::act::ai::Action)
public:
    explicit DemoBeastGanonGrudgeDrop(const InitArg& arg);
    ~DemoBeastGanonGrudgeDrop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mGrudeRainObject_s{};
    // dynamic_param at offset 0x30
    int* mTimer_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mASName_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mFallPoint1_d{};
    ksys::act::BaseProcHandle _50;
    f32 _60 = 0.0f;
    bool _64 = false;
    u8 _65[0x3];
};
KSYS_CHECK_SIZE_NX150(DemoBeastGanonGrudgeDrop, 0x68);

}  // namespace uking::action
