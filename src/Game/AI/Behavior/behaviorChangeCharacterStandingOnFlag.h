#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ChangeCharacterStandingOnFlag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ChangeCharacterStandingOnFlag, ksys::act::ai::Behavior)
public:
    explicit ChangeCharacterStandingOnFlag(const InitArg& arg);
    ~ChangeCharacterStandingOnFlag() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mChangeScaleLimit_s{};
    /* 0x30 */ const bool* mSetValue_s{};
};
KSYS_CHECK_SIZE_NX150(ChangeCharacterStandingOnFlag, 0x38);

}  // namespace uking::behavior
