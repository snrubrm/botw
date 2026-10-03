#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionSetGetFlagBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlagByActorName : public SetGetFlagBase {
    SEAD_RTTI_OVERRIDE(SetGetFlagByActorName, SetGetFlagBase)
public:
    explicit SetGetFlagByActorName(const InitArg& arg);
    ~SetGetFlagByActorName() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    const sead::SafeString& m32() override;
    void m33() override;
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    sead::FixedSafeString<128> _30;
};
KSYS_CHECK_SIZE_NX150(SetGetFlagByActorName, 0xc8);

}  // namespace uking::action
