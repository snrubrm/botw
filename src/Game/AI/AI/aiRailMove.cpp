#include "Game/AI/AI/aiRailMove.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

RailMove::RailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMove::~RailMove() = default;

bool RailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710032BCAC(0.0f);
    m38();
}

void RailMove::sub_710032BCAC(f32 progress) {
    _40.sub_7100EEBAE0(m36(), progress);
    _40.sub_7100EEBE9C(1);
}

void RailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMove::loadParams_() {
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
}

void RailMove::sub_710032C088() {
    m37();
    sub_710032C56C();
}

void RailMove::sub_710032C56C() {
    if (sub_710032C5AC())
        sub_710032C0D4();
    else
        sub_710032C2B0();
}

bool RailMove::sub_710032C5AC() const {
    return _40._8.rail && _40._8.rail->isBezier();
}

void RailMove::sub_710032C5BC(sead::Vector3f* pos) const {
    *pos = _40._8.sub_7100EEB370();
}

void RailMove::m34() {}

ksys::map::Rail* RailMove::m36() {
    return sub_7100EEF264(mActor, 0);
}

void RailMove::m37() {
    if (!_40.sub_7100EEBB74())
        return;

    if (!_40.sub_7100EEBE88() && _40.m3() && m40())
        _40.sub_7100EEBE9C(-_40._58);

    if (sub_710032C5AC())
        _40.x(m35() * ksys::VFR::instance()->getDeltaFrame());
    else
        _40.x(-1.0f);
}

f32 RailMove::sub_710032C97C() const {
    return _40._30.progress;
}

bool RailMove::sub_710032C984(f32* progress, sead::Vector3f* pos,
                              const sead::Vector3f& target) const {
    auto* rail = _40._8.rail;
    if (!rail)
        return false;

    const f32 p = sub_7100EEF7AC(rail, target, false, 0.2f, -0.0f);
    if (progress)
        *progress = p;
    if (pos)
        rail->calcTranslate(pos, p);
    return true;
}

void RailMove::m38() {
    if (_40.sub_7100EEBB74())
        sub_710032C088();
    else
        sub_710032CA64();
}

void RailMove::m39() {
    const f32 wait_frame = sub_7100EEF078(_40._8.rail, sub_710032C97C());
    if (*mIsIgnoreNoWaitStopPoint_s && wait_frame <= 0.0f)
        sub_710032C088();
    else
        sub_710032C5F8();
}

bool RailMove::m40() {
    return true;
}

}  // namespace uking::ai
