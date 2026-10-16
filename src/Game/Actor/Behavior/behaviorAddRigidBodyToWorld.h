#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AddRigidBodyToWorld : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AddRigidBodyToWorld, ksys::act::ai::Behavior)
public:
    explicit AddRigidBodyToWorld(const InitArg& arg);
    ~AddRigidBodyToWorld() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const bool* mEnableNavMeshCut_s{};
    /* 0x30 */ sead::SafeString mRigidBodySetName_s{};
    /* 0x40 */ bool _40 = false;
};
KSYS_CHECK_SIZE_NX150(AddRigidBodyToWorld, 0x48);

}  // namespace uking::behavior
