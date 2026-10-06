#include "Game/AI/Action/actionSwimMoveASHoldEvent.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadStringUtil.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SwimMoveASHoldEvent::SwimMoveASHoldEvent(const InitArg& arg) : SwimMoveBase(arg) {}

SwimMoveASHoldEvent::~SwimMoveASHoldEvent() = default;

void SwimMoveASHoldEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimMoveBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _100 = -10.0f;
}

void SwimMoveASHoldEvent::loadParams_() {
    SwimMoveBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: same logic; the original keeps the parameter e and the parsed value in stack slots above the
// query (frame layout / register allocation of the cNullChar pointer differ).
void SwimMoveASHoldEvent::m32(f32 a, f32 b, f32 c, f32 d, f32 e) {
    ksys::as::ASList::Unk4 query;
    f32 target;
    if (!sub_71005DD5B0(mActor, 47, &query, 0, 0)) {
        _98 *= *mPosReduceRatio_s;
    } else {
        f32 value = c;
        if (!query.name.isEmpty())
            sead::StringUtil::tryParseF32(&value, query.name);
        if (b * 2.5f < a) {
            target = value * 0.5f;
            _98.chase(target, value * 0.05f);
        } else if (d <= e) {
            _98.lerp(value, sead::Mathf::min(2.0f / query._10, 1.0f));
        } else {
            target = 0.0f;
            _98.chase(target, value * 0.33f);
        }
    }
    _98.setToMin(e);
    _98.updateStats();
}

}  // namespace uking::action
