#include "Game/AI/AI/aiDisplaySelect.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

DisplaySelect::DisplaySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DisplaySelect::~DisplaySelect() = default;

bool DisplaySelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DisplaySelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DisplaySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DisplaySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100361960(params);
}

// 0x7100361960 (placeholder name): picks "画面内" / "画面外" depending on whether the actor is on screen.
void DisplaySelect::sub_7100361960(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    bool visible;
    if (*mRadius_s <= 0.0f)
        visible = ksys::sub_7100D8C4F8(pos);
    else
        visible = visibilityCheckMaybe(pos, *mRadius_s);
    if (visible) {
        if (!isCurrentChild("画面内"))
            changeChild("画面内", params);
    } else {
        if (!isCurrentChild("画面外"))
            changeChild("画面外", params);
    }
}

void DisplaySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DisplaySelect::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

void DisplaySelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable() && *mIsCheckEveryFrame_s)
        sub_7100361960(nullptr);
}

}  // namespace uking::ai
