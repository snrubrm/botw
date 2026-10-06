#include "Game/AI/AI/aiRailMoveObjectOneWay.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

RailMoveObjectOneWay::RailMoveObjectOneWay(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RailMoveObjectOneWay::~RailMoveObjectOneWay() {
    ;
}

bool RailMoveObjectOneWay::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: our build inlines sub_710053479C/sub_71005348DC (calc_, their other caller, is not
// decompiled yet); the code is otherwise identical
void RailMoveObjectOneWay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _58 = sub_7100EEF264(actor, 0);
    if (_58)
        _60 = _58->getNumPoints();
    _64 = 0;
    _6d = false;
    _6e = false;

    if (!_58) {
        sub_71005348DC();
        return;
    }

    if (actor->checkBasicSig()) {
        if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_On_s))
            changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
        _68 = _64 + 1.0f;
        _6c = true;
        _6d = true;
        sub_710053479C();
        return;
    }

    if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_Off_s))
        changeAS(mASKeyName_Off_s.cstr(), false, 0, 0);
    _6c = false;
    sub_71005348DC();
}

void RailMoveObjectOneWay::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveObjectOneWay::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
}

void RailMoveObjectOneWay::m9() {
    _58 = sub_7100EEF264(mActor, 0);
    if (_58)
        _60 = _58->getNumPoints();
}

void RailMoveObjectOneWay::sub_710053479C() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f start = sead::Vector3f::zero;
    sead::Vector3f end = sead::Vector3f::zero;
    if (_58) {
        start = _58->calcTranslate(_64);
        end = _58->calcTranslate(_68);
    }
    pack.addVec3(start, "DynStartPos", -1);
    pack.addVec3(end, "DynTargetPos", -1);
    changeChild("移動", &pack);
}

void RailMoveObjectOneWay::sub_71005348DC() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 stop_time;
    if (_58) {
        _58->calcTranslate(&pos, _64);
        stop_time = sub_7100EEF078(_58, _64);
    } else {
        stop_time = 0;
    }
    pack.addFloat(stop_time, "DynStopTime", -1);
    pack.addVec3(pos, "DynStopPos", -1);
    changeChild("停止", &pack);
}

// NON_MATCHING: the original loads mActor before the first compare (same code otherwise)
// 0x7100534f90
void RailMoveObjectOneWay::sub_7100534F90() {
    const s32 last = _60 - 1;
    const s32 index = _64;
    if ((last == index && sead::Mathf::abs(_64 - last) <= 0) ||
        (index == 0 && sead::Mathf::abs(_64) <= 0 && _6c == 2)) {
        if (auto* as_list = mActor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_Off_s))
            changeAS(mASKeyName_Off_s.cstr(), false, 0, 0);
        _6c = 0;
        _6e = true;
    }
}

}  // namespace uking::ai
