#pragma once

#include "Game/AI/Action/actionSetGetFlagBase.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlag : public SetGetFlagBase {
    SEAD_RTTI_OVERRIDE(SetGetFlag, SetGetFlagBase)
public:
    explicit SetGetFlag(const InitArg& arg);
    ~SetGetFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    sead::FixedSafeString<128> _20;
};
KSYS_CHECK_SIZE_NX150(SetGetFlag, 0xb8);

}  // namespace uking::action
