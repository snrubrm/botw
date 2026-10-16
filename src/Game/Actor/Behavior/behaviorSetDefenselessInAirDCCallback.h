#pragma once

#include "Game/Actor/Behavior/behaviorSetDefenselessDCCallback.h"

namespace uking::behavior {

class SetDefenselessInAirDCCallback : public SetDefenselessDCCallback {
    SEAD_RTTI_OVERRIDE(SetDefenselessInAirDCCallback, SetDefenselessDCCallback)
public:
    explicit SetDefenselessInAirDCCallback(const InitArg& arg);
    ~SetDefenselessInAirDCCallback() override;
    void calc() override;

};
KSYS_CHECK_SIZE_NX150(SetDefenselessInAirDCCallback, 0x58);

}  // namespace uking::behavior
