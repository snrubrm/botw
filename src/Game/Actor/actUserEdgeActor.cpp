#include "Game/Actor/actUserEdgeActor.h"
#include <basis/seadNew.h>

namespace uking::act {

UserEdgeActor::UserEdgeActor(const CreateArg& arg) : Actor(arg) {}

UserEdgeActor::~UserEdgeActor() = default;

ksys::act::BaseProc* UserEdgeActor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) UserEdgeActor(arg);
}

}  // namespace uking::act
