#include "Game/Actor/actEnvSeEmitPoint.h"
#include <basis/seadNew.h>
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::act {

void EnvSeEmitPoint::sub_7101029620(bool enabled) {
    if (auto* link = getXLink()) {
        if (!enabled && _845)
            link->_cc.set(0x200);
        else
            link->_cc.reset(0x200);
    }
    _844 = enabled;
}

void EnvSeEmitPoint::sub_7101029658() {
    const sead::Vector3f position = getMtx().getTranslation();
    if (auto* listener = ksys::snd::SoundMgr::instance()->sub_71011FC2D0())
        _840 = listener->calcLocalDistance(position);
}

void EnvSeEmitPoint::sub_71010296B0() {}

EnvSeEmitPoint::EnvSeEmitPoint(const CreateArg& arg) : Actor(arg) {
    _1c0 = 15;
    bindCalc1ToJob1_2();
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
}

ksys::act::BaseProc* EnvSeEmitPoint::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) EnvSeEmitPoint(arg);
}

}  // namespace uking::act
