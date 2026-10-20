#include "Game/Actor/actEnvSeEmitPoint.h"
#include <basis/seadNew.h>
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::act {

// NON_MATCHING: the original builds the position after getStatsPointer and clears the result after it
// (scheduling).
// Reads the forest density at the actor once and passes it to the xlink property 0 (0 in AocField).
void EnvSeEmitPoint::calcMaybe() {
    if (_84c)
        return;

    if (ksys::StageInfo::getCurrentMapType() == "AocField") {
        _848 = 0;
        _84c = true;
        if (mXLink)
            mXLink->sub_7101231468(0, 0.0f, false);
        return;
    }

    auto* stats = StatisticsMgr::instance();
    if (!stats)
        return;
    f32 density = 0;
    const sead::Vector3f pos = getMtx().getTranslation();
    if (!stats->sub_7100E33B10(&density, 1, stats->getStatsPointer("forest_density"), &pos))
        return;
    _84c = true;
    _848 = density;
    if (mXLink)
        mXLink->sub_7101231468(0, density, false);
}

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

EnvSeEmitPoint::~EnvSeEmitPoint() = default;

ksys::act::BaseProc* EnvSeEmitPoint::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) EnvSeEmitPoint(arg);
}

}  // namespace uking::act
