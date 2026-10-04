#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

class AnimalAttack : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AnimalAttack, ksys::act::ai::Behavior)
public:
    explicit AnimalAttack(const InitArg& arg);
    ~AnimalAttack() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    // Original out-of-line update helper; declaration only.
    void sub_7100616E20();

    /* 0x28 */ const bool* mIsUseASEventAtCollision_s{};
    /* 0x30 */ sead::SafeString mAtkRigidName_s{};
    /* 0x40 */ bool _40 = false;
    /* 0x48 */ ksys::phys::RigidBody* _48 = nullptr;
};
KSYS_CHECK_SIZE_NX150(AnimalAttack, 0x50);

}  // namespace uking::behavior
