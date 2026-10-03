#include "Game/Actor/actEnvSeEmitPoint.h"
#include <basis/seadNew.h>

namespace uking::act {

EnvSeEmitPoint::EnvSeEmitPoint(const CreateArg& arg) : Actor(arg) {
    _1c0 = 15;
    bindCalc1ToJob1_2();
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
}

ksys::act::BaseProc* EnvSeEmitPoint::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) EnvSeEmitPoint(arg);
}

}  // namespace uking::act
