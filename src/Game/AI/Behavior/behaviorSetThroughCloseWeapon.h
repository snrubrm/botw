#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// TODO: `_28` is an object with vtable 0x710243a160 (one virtual 0x710063f108 with eight arguments) that
// points to itself at +0x18; its type is not declared yet.
class SetThroughCloseWeapon : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetThroughCloseWeapon, ksys::act::ai::Behavior)
public:
    explicit SetThroughCloseWeapon(const InitArg& arg);
    ~SetThroughCloseWeapon() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x710063f0e0)
    void m9() override;  // not decompiled yet (0x710063f0f4)

    /* 0x28 */ u8 _28[0x28];
};
KSYS_CHECK_SIZE_NX150(SetThroughCloseWeapon, 0x50);

}  // namespace uking::behavior
