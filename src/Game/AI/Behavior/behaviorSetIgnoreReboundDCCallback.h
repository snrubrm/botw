#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetIgnoreReboundDCCallback : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetIgnoreReboundDCCallback, ksys::act::ai::Behavior)
public:
    explicit SetIgnoreReboundDCCallback(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    ~SetIgnoreReboundDCCallback() override;  // not decompiled yet

    /* 0x28 */ const bool* mEnableRebound_s{};
    /* 0x30 */ const bool* mEnableReboundStrong_s{};
    /* 0x38 */ const bool* mEnableReboundSuper_s{};
    /* 0x40 */ Unk_7102451b68 _40;
};
KSYS_CHECK_SIZE_NX150(SetIgnoreReboundDCCallback, 0x68);

}  // namespace uking::behavior
