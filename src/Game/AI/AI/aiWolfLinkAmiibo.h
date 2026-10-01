#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkAmiibo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkAmiibo, ksys::act::ai::Ai)
public:
    explicit WolfLinkAmiibo(const InitArg& arg);
    ~WolfLinkAmiibo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100600A6C();

protected:
    // static_param at offset 0x38
    const int* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x40
    const float* mAreaThreshold_s{};
    // static_param at offset 0x48
    const float* mAreaSearchRadius_s{};
    sead::Vector3f _50 = sead::Vector3f::zero;
    bool _5c = false;
    // Navigation query handle (HavokAI::destroyQuery in the destructor).
    void* _60{};
    bool _68 = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkAmiibo, 0x70);

}  // namespace uking::ai
