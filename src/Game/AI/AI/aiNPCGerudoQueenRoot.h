#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::ai {

class NPCGerudoQueenRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCGerudoQueenRoot, NPCRoot)
public:
    explicit NPCGerudoQueenRoot(const InitArg& arg);
    ~NPCGerudoQueenRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x238
    const bool* mIsOnHelmet_m{};
    // Array of 3 bone handles allocated in init_ (the destructor removes them from the actor and deletes the array).
    ksys::act::BoneHandle* _240 = nullptr;
    bool _248 = false;
};
KSYS_CHECK_SIZE_NX150(NPCGerudoQueenRoot, 0x250);

}  // namespace uking::ai
