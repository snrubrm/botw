#include "Game/AI/AI/aiCliffDistanceSelectThreeAction.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CliffDistanceSelectThreeAction::CliffDistanceSelectThreeAction(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CliffDistanceSelectThreeAction::~CliffDistanceSelectThreeAction() = default;

bool CliffDistanceSelectThreeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: operand order of the three normalize multiplies (x * inv in the original)
void CliffDistanceSelectThreeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 2);
    dir.normalize();

    sead::Vector3f pos;
    if (!sub_710072FEC4(mActor, dir, *mCheckDist_s, &pos, true, nullptr)) {
        changeChild("崖でない", params);
        return;
    }

    if ((pos - mActor->getMtx().getTranslation()).length() <= *mNearCliffDist_s)
        changeChild("崖近距離", params);
    else
        changeChild("崖である", params);
}

void CliffDistanceSelectThreeAction::calc_() {}

bool CliffDistanceSelectThreeAction::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool CliffDistanceSelectThreeAction::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void CliffDistanceSelectThreeAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CliffDistanceSelectThreeAction::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mNearCliffDist_s, "NearCliffDist");
}

}  // namespace uking::ai
