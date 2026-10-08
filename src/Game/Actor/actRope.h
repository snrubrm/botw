#pragma once

#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::act {

// Only the nominal type is recovered; owned members and construction remain undeclared.
class Rope : public ksys::act::RopeBase {
    SEAD_RTTI_OVERRIDE(Rope, ksys::act::RopeBase)
public:
    ~Rope() override;

    // RopeBase slot 149.
    void m149() override;
};

}  // namespace uking::act
