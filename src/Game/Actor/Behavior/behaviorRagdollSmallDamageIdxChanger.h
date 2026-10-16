#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class RagdollSmallDamageIdxChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(RagdollSmallDamageIdxChanger, ksys::act::ai::Behavior)
public:
    explicit RagdollSmallDamageIdxChanger(const InitArg& arg);
    ~RagdollSmallDamageIdxChanger() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    // inline-only in the original; names are guesses (the same sequences are inlined in calc, enter and leave).
    void sub_applyKey_();
    void sub_restoreKey_();

    /* 0x28 */ const bool* mIsChinkCheck_s{};
    /* 0x30 */ sead::SafeString mKeyName_s{};
    /* 0x40 */ u32 _40 = 0xffffffffffffffff;
    /* 0x44 */ bool _44 = false;
};
KSYS_CHECK_SIZE_NX150(RagdollSmallDamageIdxChanger, 0x48);

}  // namespace uking::behavior
