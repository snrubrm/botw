#include "Game/Actor/actCookResult.h"
#include <basis/seadNew.h>

namespace uking::act {

CookResult::CookResult(const CreateArg& arg) : Item(arg) {
    _bb0.actor_name.copy(mName);
}

ksys::act::BaseProc* CookResult::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) CookResult(arg);
}

}  // namespace uking::act
