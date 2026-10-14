#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetFlag, ksys::act::ai::Action)
public:
    explicit SetFlag(const InitArg& arg);
    ~SetFlag() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    // m32 returns the flag name, m33 prepares it.
    virtual const sead::SafeString& m32() = 0;
    virtual void m33() = 0;
};

}  // namespace uking::action
