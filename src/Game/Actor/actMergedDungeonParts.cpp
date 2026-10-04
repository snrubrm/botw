#include "Game/Actor/actMergedDungeonParts.h"
#include <basis/seadNew.h>

namespace uking::act {

MergedDungeonParts::MergedDungeonParts(const CreateArg& arg)
    : MapConstActiveOrMergedDungeonParts(arg) {
    for (int i = 0; i < 17; ++i)
        _850[i] = sead::Matrix34f::ident;
    for (int i = 0; i < 17; ++i)
        _b80[i] = -1;
}

ksys::act::BaseProc* MergedDungeonParts::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MergedDungeonParts(arg);
}

}  // namespace uking::act
