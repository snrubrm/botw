#include "Game/Actor/Behavior/behaviorSoundStateLoad.h"
#include "Game/Actor/actCamera.h"

namespace uking::behavior {

SoundStateLoad::SoundStateLoad(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void SoundStateLoad::m8() {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::Camera>(mActor))
            camera->sub_7100795C38(0);
    }
}

}  // namespace uking::behavior
