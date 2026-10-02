#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

class HitIceBlockBreak : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HitIceBlockBreak, ksys::act::ai::Behavior)
public:
    explicit HitIceBlockBreak(const InitArg& arg);
    ~HitIceBlockBreak() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mRigidBodyName_s{};
    /* 0x38 */ ksys::phys::RigidBody* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(HitIceBlockBreak, 0x40);

}  // namespace uking::behavior
