#include "Game/Actor/actSoundSystemActor.h"
#include <basis/seadNew.h>

namespace uking::act {

SoundSystemActor::SoundSystemActor(const CreateArg& arg) : Actor(arg) {
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
    _1c0 = 15;
}

SoundSystemActor::~SoundSystemActor() = default;

ksys::act::BaseProc* SoundSystemActor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) SoundSystemActor(arg);
}

}  // namespace uking::act
