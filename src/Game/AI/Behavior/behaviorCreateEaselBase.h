#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::behavior {

class CreateEaselBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CreateEaselBase, ksys::act::ai::Behavior)
public:
    explicit CreateEaselBase(const InitArg& arg);
    ~CreateEaselBase() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual const char* m14();  // not decompiled yet (0x710061dd24)
    virtual bool m15() { return true; }
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710061d7ec)
    void m7() override;  // not decompiled yet (0x710061d894)

    /* 0x28 */ const bool* mIsNoSystemDelete_s{};
    /* 0x30 */ sead::SafeString mActorName_s{};
    /* 0x40 */ const sead::Vector3f* mOffset_s{};
    /* 0x48 */ ksys::act::BaseProcHandle _48;
};

}  // namespace uking::behavior
