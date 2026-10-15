#include "Game/Actor/AI/aiRailMoveObjectOneWay.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
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

// NON_MATCHING: our build inlines sub_7100534F90 (the original calls it) and selects the _6c update with csinc;
// the original reads _6c sign-extended (ldrsb)
void RailMoveObjectOneWay::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        _64 = _68;
        sub_71005348DC();
        return;
    }
    if (!child->isChangeable())
        return;

    if (_6d == actor->checkBasicSig()) {
        if (!isCurrentChild("停止") || _6c == 0 || _6e)
            return;
        const s32 index = _64;
        if (sead::Mathf::abs(_64 - index) <= 0.0f) {
            _64 = _68;
            if (_6c == 1)
                _68 = _64 + 1.0f;
            else if (_6c == 2)
                _68 = _64 - 1.0f;
        }
        _64 = sead::Mathf::clamp(_64, 0.0f, _60 - 1.0f);
        _68 = sead::Mathf::clamp(_68, 0.0f, _60 - 1.0f);
        sub_7100534F90();
        if (_6e)
            return;
        sub_710053479C();
        return;
    }

    _6d = actor->checkBasicSig();
    _6e = false;
    switch (_6c) {
    case 0:
        if (actor->checkBasicSig())
            _6c = 1;
        else
            _6c = 2;
        if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_On_s))
            changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
        break;
    case 1:
        _6c = 2;
        break;
    case 2:
        _6c = 1;
        break;
    }

    if (isCurrentChild("移動")) {
        sub_7100534D4C();
    } else if (isCurrentChild("停止")) {
        const s32 index = _64;
        if (sead::Mathf::abs(_64 - index) <= 0.0f) {
            _64 = _68;
            if (_6c == 1)
                _68 = _64 + 1.0f;
            else if (_6c == 2)
                _68 = _64 - 1.0f;
        }
        _64 = sead::Mathf::clamp(_64, 0.0f, _60 - 1.0f);
        _68 = sead::Mathf::clamp(_68, 0.0f, _60 - 1.0f);
    } else {
        return;
    }
    sub_710053479C();
}

// NON_MATCHING: the original captures mActor before the rail calls.
void RailMoveObjectOneWay::sub_7100534D4C() {
    if (!_58)
        return;
    f32 start = 0.0f;
    f32 previous = 0.0f;
    if (_6c == 1) {
        start = sead::Mathf::ceil(_64);
        previous = start - 1.0f;
    } else if (_6c == 2) {
        start = sead::Mathf::floor(_64);
        previous = start + 1.0f;
    }
    previous = sead::Mathf::clamp(previous, 0.0f, _60 - 1.0f);
    const sead::Vector3f start_pos = _58->calcTranslate(start);
    const sead::Vector3f target_pos = _58->calcTranslate(_68);
    const f32 length = (target_pos - start_pos).length();
    const f32 distance = (mActor->getMtx().getTranslation() - start_pos).length();
    const f32 ratio = sead::Mathf::clamp(distance / length, 0.0f, 1.0f);
    if (_6c == 1) {
        _64 = start - ratio;
        _68 = previous + 1.0f;
    } else if (_6c == 2) {
        _64 = start + ratio;
        _68 = previous - 1.0f;
    }
    _64 = sead::Mathf::clamp(_64, 0.0f, _60 - 1.0f);
    _68 = sead::Mathf::clamp(_68, 0.0f, _60 - 1.0f);
}

void RailMoveObjectOneWay::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveObjectOneWay::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
}

void RailMoveObjectOneWay::applyParams() {
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
