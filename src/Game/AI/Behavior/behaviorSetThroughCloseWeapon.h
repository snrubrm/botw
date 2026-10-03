#pragma once

#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace uking::behavior {

class SetThroughCloseWeapon : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetThroughCloseWeapon, ksys::act::ai::Behavior)
public:
    explicit SetThroughCloseWeapon(const InitArg& arg);
    ~SetThroughCloseWeapon() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;
    void m9() override;

    // vtable 0x710243a160 (virtual 0x710063f108): the registered attack sensor listener lets close weapons through.
    class Listener : public ksys::act::AttackSensor2Listener {
    public:
        bool m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                const ksys::act::Struct8Base* info) override;
    };

    /* 0x28 */ Listener _28;
};
KSYS_CHECK_SIZE_NX150(SetThroughCloseWeapon, 0x50);

}  // namespace uking::behavior
