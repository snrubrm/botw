#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlagBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetGetFlagBase, ksys::act::ai::Action)
public:
    explicit SetGetFlagBase(const InitArg& arg);
    ~SetGetFlagBase() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    // m32 returns the flag name, m33 prepares it.
    virtual const sead::SafeString& m32() = 0;
    virtual void m33() = 0;
};

}  // namespace uking::action
