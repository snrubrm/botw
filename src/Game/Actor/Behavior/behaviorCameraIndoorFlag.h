#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CameraIndoorFlag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CameraIndoorFlag, ksys::act::ai::Behavior)
public:
    explicit CameraIndoorFlag(const InitArg& arg);
    void enter() override;
    void leave() override;

};
KSYS_CHECK_SIZE_NX150(CameraIndoorFlag, 0x28);

}  // namespace uking::behavior
