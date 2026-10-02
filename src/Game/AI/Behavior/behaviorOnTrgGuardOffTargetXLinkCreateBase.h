#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

// CSV name: OnTrgGuardOffTargetXLinkCreate (the base of that behavior).
class OnTrgGuardOffTargetXLinkCreateBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnTrgGuardOffTargetXLinkCreateBase, ksys::act::ai::Behavior)
public:
    explicit OnTrgGuardOffTargetXLinkCreateBase(const InitArg& arg);
    ~OnTrgGuardOffTargetXLinkCreateBase() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual void m14(Unk_71012419b4* handle) {}

    /* 0x28 */ sead::SafeString mKey_s{};
};

}  // namespace uking::behavior
