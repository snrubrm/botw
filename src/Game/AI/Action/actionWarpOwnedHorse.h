#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class WarpOwnedHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpOwnedHorse, ksys::act::ai::Action)
public:
    explicit WarpOwnedHorse(const InitArg& arg);
    ~WarpOwnedHorse() override;

    void loadParams_() override;

protected:
    sead::Matrix34f _1c = sead::Matrix34f::ident;
    ksys::act::BaseProcLink _50;
};
KSYS_CHECK_SIZE_NX150(WarpOwnedHorse, 0x60);

}  // namespace uking::action
