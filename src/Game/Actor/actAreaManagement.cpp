#include "Game/Actor/actAreaManagement.h"
#include <basis/seadNew.h>

namespace uking::act {

AreaManagement::AreaManagement(const CreateArg& arg) : Actor(arg) {
    getJobHandler(ksys::act::JobType::PreCalc) = nullptr;
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
}

ksys::act::BaseProc* AreaManagement::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) AreaManagement(arg);
}

void AreaManagement::m73() {
    mActorFlags2Prev = mActorFlags2;
}

int AreaManagement::getCalcTiming() {
    return 2;
}

}  // namespace uking::act
