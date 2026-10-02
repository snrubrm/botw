#include "Game/AI/aiUnk_7100726FF4.h"
#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

Unk_71024241a8* sub_7100726FF4(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    return sead::DynamicCast<Unk_71024241a8>(*static_cast<Unk_71025afb58**>(unit));
}

}  // namespace uking::ai
