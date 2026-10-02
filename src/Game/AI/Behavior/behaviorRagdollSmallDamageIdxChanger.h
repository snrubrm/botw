#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class RagdollSmallDamageIdxChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(RagdollSmallDamageIdxChanger, ksys::act::ai::Behavior)
public:
    explicit RagdollSmallDamageIdxChanger(const InitArg& arg);
    ~RagdollSmallDamageIdxChanger() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mIsChinkCheck_s{};
    /* 0x30 */ sead::SafeString mKeyName_s{};
    /* 0x40 */ u32 _40 = 0xffffffffffffffff;
    /* 0x44 */ bool _44 = false;
};
KSYS_CHECK_SIZE_NX150(RagdollSmallDamageIdxChanger, 0x48);

}  // namespace uking::behavior
