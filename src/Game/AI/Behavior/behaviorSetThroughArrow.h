#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace uking::behavior {

class SetThroughArrow : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetThroughArrow, SetDamageCallback)
public:
    explicit SetThroughArrow(const InitArg& arg);
    ~SetThroughArrow() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;
    void m8() override;
    void m9() override;

    // vtable 0x710243a0c8 (virtual 0x710063eef4): the registered attack sensor listener lets arrows through.
    class Listener : public ksys::act::AttackSensor2Listener {
    public:
        bool m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                const ksys::act::Struct8Base* info, const ksys::act::PhysicsUserTag* tag) override;
    };

    /* 0x30 */ Unk_71024518c8 _30;
    /* 0x58 */ Listener _58;
};
KSYS_CHECK_SIZE_NX150(SetThroughArrow, 0x80);

}  // namespace uking::behavior
