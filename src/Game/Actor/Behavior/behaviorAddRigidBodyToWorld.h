#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AddRigidBodyToWorld : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AddRigidBodyToWorld, ksys::act::ai::Behavior)
public:
    explicit AddRigidBodyToWorld(const InitArg& arg);
    ~AddRigidBodyToWorld() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mEnableNavMeshCut_s{};
    /* 0x30 */ sead::SafeString mRigidBodySetName_s{};
    /* 0x40 */ bool _40 = false;
};
KSYS_CHECK_SIZE_NX150(AddRigidBodyToWorld, 0x48);

}  // namespace uking::behavior
