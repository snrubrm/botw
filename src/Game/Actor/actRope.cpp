#include "Game/Actor/actRope.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::act {

void Rope::m149() {
    if (GameSceneSubsys5::sInstance == nullptr)
        return;
    GameSceneSubsys5::sInstance->sub_7100905C70();
}

}  // namespace uking::act
