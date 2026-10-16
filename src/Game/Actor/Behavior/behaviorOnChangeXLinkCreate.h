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
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void onChangeChild() override;
    virtual void m14();

    /* 0x28 */ const bool* mDoOnChangeAI_s{};
    /* 0x30 */ sead::SafeString mKey_s{};
};
KSYS_CHECK_SIZE_NX150(OnChangeXLinkCreate, 0x40);

}  // namespace uking::behavior
