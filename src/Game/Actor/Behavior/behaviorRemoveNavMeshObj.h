#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class RemoveNavMeshObj : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(RemoveNavMeshObj, ksys::act::ai::Behavior)
public:
    explicit RemoveNavMeshObj(const InitArg& arg);
    ~RemoveNavMeshObj() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(RemoveNavMeshObj, 0x28);

}  // namespace uking::behavior
