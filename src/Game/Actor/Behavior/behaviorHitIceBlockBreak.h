#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys { struct MesTransceiverId; }

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

class HitIceBlockBreak : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HitIceBlockBreak, ksys::act::ai::Behavior)
public:
    explicit HitIceBlockBreak(const InitArg& arg);
    ~HitIceBlockBreak() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void sub_7100627F7C(ksys::phys::RigidBody* body);
    bool sub_7100628084(ksys::MesTransceiverId* id, ksys::phys::RigidBody* body);

    /* 0x28 */ sead::SafeString mRigidBodyName_s{};
    /* 0x38 */ ksys::phys::RigidBody* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(HitIceBlockBreak, 0x40);

}  // namespace uking::behavior
