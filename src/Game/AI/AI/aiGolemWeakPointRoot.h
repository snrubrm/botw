#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/AI/aiWeakPointRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorConstDataAccess;
}

// 0x7100d15f1c (CSV name, global): a random drop of `table_name` from the drop table of the actor
// `accessor` points to.
const sead::SafeString& golemWeakPointGetOneDrop(const ksys::act::ActorConstDataAccess& accessor,
                                                 const sead::SafeString& table_name);

namespace uking::ai {

// Placeholder name (vtable 0x71023f5bb0; one virtual, 0x7100403c0c: an attack sensor listener that
// GolemWeakPointRoot registers with its actor in enter_ and removes in leave_).
class Unk_71023f5bb0 : public ksys::act::AttackSensor2Listener {
public:
    bool m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
            const ksys::act::Struct8Base* info) override;
};

class GolemWeakPointRoot : public WeakPointRoot {
    SEAD_RTTI_OVERRIDE(GolemWeakPointRoot, WeakPointRoot)
public:
    explicit GolemWeakPointRoot(const InitArg& arg);
    ~GolemWeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m36();
    virtual void m37();
    virtual void m38(s32 idx, const sead::Matrix34f& mtx);

protected:
    // The three spawned drop actors ("Milestone" table).
    ksys::act::BaseProcLink _180[3];
    Unk_71023f57c8 _1b0;
    // Position of the actor (inline copy of the 3 floats returned by sub_7100739578).
    f32 _1e8;
    f32 _1ec;
    f32 _1f0;
    s32 _1f4 = 0;
    Unk_71023f5bb0 _1f8;
};

}  // namespace uking::ai
