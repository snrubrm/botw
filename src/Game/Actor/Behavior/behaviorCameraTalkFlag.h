#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CameraTalkFlag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CameraTalkFlag, ksys::act::ai::Behavior)
public:
    explicit CameraTalkFlag(const InitArg& arg);
    void enter() override;
    void leave() override;

};
KSYS_CHECK_SIZE_NX150(CameraTalkFlag, 0x28);

}  // namespace uking::behavior
