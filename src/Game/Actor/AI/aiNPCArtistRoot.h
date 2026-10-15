#pragma once

#include "Game/Actor/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCArtistRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCArtistRoot, NPCRoot)
public:
    explicit NPCArtistRoot(const InitArg& arg);
    ~NPCArtistRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x238
    sead::SafeString mActorName_m{};
    ksys::act::BoneHandle _248;
    bool _2f0 = false;
    f32 _2f4 = 0;
    ksys::Timer _2f8;
    act::NPC* _308 = nullptr;
};
KSYS_CHECK_SIZE_NX150(NPCArtistRoot, 0x310);

}  // namespace uking::ai
