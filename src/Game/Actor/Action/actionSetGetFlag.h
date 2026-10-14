#pragma once

#include "Game/Actor/Action/actionSetFlag.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlag : public SetFlag {
    SEAD_RTTI_OVERRIDE(SetGetFlag, SetFlag)
public:
    explicit SetGetFlag(const InitArg& arg);
    ~SetGetFlag() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    const sead::SafeString& m32() override;
    void m33() override;
    sead::FixedSafeString<128> _20;
};
KSYS_CHECK_SIZE_NX150(SetGetFlag, 0xb8);

}  // namespace uking::action
