#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::behavior {

// vtable 0x71024355e8 (functions in this behavior's translation unit): disables contacts with the
// rigid bodies of contact layer `_8`.
class Unk_71024355e8 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;

    u32 _8 = 0;
    u32 _c;
    u32 _10 = 0;
};

class DisableContactLayer : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableContactLayer, ksys::act::ai::Behavior)
public:
    explicit DisableContactLayer(const InitArg& arg);
    ~DisableContactLayer() override;
    void m7() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710061f198)
    void m8() override;  // not decompiled yet (0x710061f290)
    void m9() override;  // not decompiled yet (0x710061f324)

    /* 0x28 */ const bool* mIgnoreContactPoint_s{};
    /* 0x30 */ sead::SafeString mLayerNameToDisable_s{};
    /* 0x40 */ Unk_71024355e8 _40;
};
KSYS_CHECK_SIZE_NX150(DisableContactLayer, 0x58);

}  // namespace uking::behavior
