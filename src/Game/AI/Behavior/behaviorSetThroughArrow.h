#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

// TODO: `_58` is an object with vtable 0x710243a0c8 (one virtual 0x710063eef4 with eight arguments) that
// points to itself at +0x18; its type is not declared yet.
class SetThroughArrow : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetThroughArrow, SetDamageCallback)
public:
    explicit SetThroughArrow(const InitArg& arg);
    ~SetThroughArrow() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;
    void m8() override;  // not decompiled yet (0x710063ec04)
    void m9() override;  // not decompiled yet (0x710063ed80)

    /* 0x30 */ Unk_71024518c8 _30;
    /* 0x58 */ u8 _58[0x28];
};
KSYS_CHECK_SIZE_NX150(SetThroughArrow, 0x80);

}  // namespace uking::behavior
