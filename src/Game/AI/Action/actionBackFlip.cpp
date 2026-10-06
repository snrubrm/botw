#include "Game/AI/Action/actionBackFlip.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

BackFlip::BackFlip(const InitArg& arg) : RotateTurnToTarget(arg) {}

BackFlip::~BackFlip() = default;

bool BackFlip::init_(sead::Heap* heap) {
    if (!RotateTurnToTarget::init_(heap))
        return false;
    return _a0.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void BackFlip::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
    _cc = false;
    _cd = false;
    if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_a0._0))
        checker->reset(15.0f);
}

void BackFlip::leave_() {
    RotateTurnToTarget::leave_();
    auto* actor = mActor;
    sub_7100738AA8(actor, 0.0f);
    sub_7100738428(actor, 0.1f);
}

void BackFlip::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mNearGrHeight_s, "NearGrHeight");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void BackFlip::calc_() {
    RotateTurnToTarget::calc_();
}

void BackFlip::m32() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(actor, 0x2f, &query, 0, 0)) {
        sead::Vector3f dir = actor->getMtx().getTranslation();
        dir -= *mTargetPos_d;
        const f32 speed = *mSpeed_s;
        const f32 length = dir.length();
        if (length > 0.0f)
            dir *= speed / length;
        ksys::act::sub_7100EE5980(actor, dir);
    } else {
        const f32 ratio = as_list->x(0x2f, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                     true) ?
                              *mPosRestRatio_s :
                              0.1f;
        sub_7100738428(actor, ratio);
    }
}

bool BackFlip::isFinished() const {
    if (!_cc)
        return false;
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    const sead::Vector3f down = -sead::Vector3f::ey;
    return somePositionCalc(&pos, pos, down, *mNearGrHeight_s);
}

}  // namespace uking::action
