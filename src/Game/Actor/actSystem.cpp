#include "Game/Actor/actSystem.h"
#include <basis/seadNew.h>

namespace uking::act {

System::System(const CreateArg& arg) : Actor(arg) {
    _1c0 = 6;
}

System::~System() = default;

ksys::act::BaseProc* System::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) System(arg);
}

bool System::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

bool System::shouldUnload(s32* a1) {
    return false;
}

}  // namespace uking::act
