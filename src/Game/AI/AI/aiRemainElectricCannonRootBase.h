#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainElectricCannonRootBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonRootBase, ksys::act::ai::Ai)
public:
    explicit RemainElectricCannonRootBase(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override { return false; }

    virtual bool m34() { return false; }
    virtual bool m35();
    virtual void m36();
    virtual void m37() { m40(); }
    virtual void m38();
    virtual bool m39();
    virtual void m40();
    virtual f32 m41() { return *mSearchMaxDist_s; }

protected:
    // static_param at offset 0x38
    const float* mSearchMaxDist_s{};
    // static_param at offset 0x40
    const float* mSearchMinDist_s{};
    // static_param at offset 0x48
    const float* mSearchDistMargin_s{};
    bool _50 = false;
    bool _51 = false;
    sead::Vector3f _54;
};
KSYS_CHECK_SIZE_NX150(RemainElectricCannonRootBase, 0x60);

}  // namespace uking::ai
