#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

class OnChangeXLinkCreate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnChangeXLinkCreate, ksys::act::ai::Behavior)
public:
    explicit OnChangeXLinkCreate(const InitArg& arg);
    ~OnChangeXLinkCreate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m11() override;
    virtual void m14();

    /* 0x28 */ const bool* mDoOnChangeAI_s{};
    /* 0x30 */ sead::SafeString mKey_s{};
};
KSYS_CHECK_SIZE_NX150(OnChangeXLinkCreate, 0x40);

}  // namespace uking::behavior
