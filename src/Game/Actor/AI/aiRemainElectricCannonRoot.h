#pragma once

#include "Game/Actor/AI/aiLargeCannonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainElectricCannonRoot : public LargeCannonRoot {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonRoot, LargeCannonRoot)
public:
    explicit RemainElectricCannonRoot(const InitArg& arg);
    ~RemainElectricCannonRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;
    f32 m41() override;

protected:
    // static_param at offset 0x60
    const float* mSearchMaxDistLoiter_s{};
};
KSYS_CHECK_SIZE_NX150(RemainElectricCannonRoot, 0x68);

}  // namespace uking::ai
