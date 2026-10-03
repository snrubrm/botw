#include "Game/AI/AI/aiSeqCloseDistTwoAction.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::ai {

SeqCloseDistTwoAction::SeqCloseDistTwoAction(const InitArg& arg) : SeqTwoAction(arg) {}

SeqCloseDistTwoAction::~SeqCloseDistTwoAction() = default;

void SeqCloseDistTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
    _68 = false;
}

void SeqCloseDistTwoAction::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SeqCloseDistTwoAction::m35() const {
    if (_68)
        return getCurrentChild()->isChangeable();
    return false;
}

void SeqCloseDistTwoAction::calc_() {
    if (auto* actor = mActor) {
        const sead::Vector3f target = *mTargetPos_d;
        const f32 dist = sead::Mathf::sqrt(
            ksys::util::sqXZDistance(target, actor->getMtx().getTranslation()));
        if (dist <= *mCloseDist_s + sub_71007320F0(actor, *mWeaponIdx_s))
            _68 = true;
    }
    SeqTwoAction::calc_();
}

}  // namespace uking::ai
