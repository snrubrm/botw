#pragma once

#include <prim/seadSafeString.h>

namespace ksys::as {
class ASList;
}
#include "Game/Actor/actUnk_7102366570.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SyncBodyASAndAnimalUnitAS : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SyncBodyASAndAnimalUnitAS, ksys::act::ai::Behavior)
public:
    explicit SyncBodyASAndAnimalUnitAS(const InitArg& arg);
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void loadParams() override;
    void enter() override;  // not decompiled yet (0x7100645c60)
    void leave() override;  // not decompiled yet (0x7100645d08)
    ~SyncBodyASAndAnimalUnitAS() override;  // not decompiled yet

    // 2026-10-07: vtable0x710243b090 inherits the root callback RTTI and owns its D1/D0.
    // The parameters live in the callback: sub_71006459BC / sub_7100645E24 read them from `this`.
    class Callback : public Unk_7102366570 {
    public:
        ~Callback() override;
        void call(ksys::act::Actor* actor) override;
        // 0x71006459bc: syncs the actor's AS slot `mTargetBone_s` with the rider's AS bank.
        void sub_71006459BC(ksys::act::Actor* actor);
        // 0x7100645e24 (declared only): uses mPreFix_s and `name`.
        void sub_7100645E24(ksys::as::ASList* list, const sead::SafeString& name, int target_bone,
                            int seq_bank);

        /* 0x20 */ const int* mSeqBank_s{};
        /* 0x28 */ const int* mTargetBone_s{};
        /* 0x30 */ sead::SafeString mPreFix_s{};
        /* 0x40 */ s32 mBank = -1;
    };
    /* 0x28 */ Callback _28;
};
KSYS_CHECK_SIZE_NX150(SyncBodyASAndAnimalUnitAS, 0x70);

}  // namespace uking::behavior
