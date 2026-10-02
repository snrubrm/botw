#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetIsAffectWeak : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetIsAffectWeak, ksys::act::ai::Behavior)
public:
    explicit SetIsAffectWeak(const InitArg& arg);
    ~SetIsAffectWeak() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mIsAffect_s{};
    /* 0x30 */ bool _30 = true;
};
KSYS_CHECK_SIZE_NX150(SetIsAffectWeak, 0x38);

}  // namespace uking::behavior
