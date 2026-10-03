#include "Game/AI/AI/aiCliffCheckSelect.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CliffCheckSelect::CliffCheckSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CliffCheckSelect::~CliffCheckSelect() = default;

void CliffCheckSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710035116C())
        changeChild("崖である", params);
    else
        changeChild("崖でない", params);
}

bool CliffCheckSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool CliffCheckSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool CliffCheckSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void CliffCheckSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckAngle_s, "CheckAngle");
    getStaticParam(&mIsSelectFirstTime_s, "IsSelectFirstTime");
}

void CliffCheckSelect::calc_() {
    auto* child = getCurrentChild();
    const bool done = child->isFinished() || child->isFailed();
    if (done) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (!getCurrentChild()->isChangeable() || *mIsSelectFirstTime_s)
        return;

    if (isCurrentChild("崖である")) {
        if (!sub_710035116C())
            changeChild("崖でない");
    } else if (isCurrentChild("崖でない")) {
        if (sub_710035116C())
            changeChild("崖である");
    }
}

bool CliffCheckSelect::sub_710035116C() {
    if (!mActor)
        return false;

    sead::Vector3f dir;
    m34(&dir);
    sead::Vector3f rot = sead::Vector3f::ey;
    rot *= *mCheckAngle_s;
    sead::Matrix34f mtx;
    mtx.makeR(rot);
    dir.rotate(mtx);
    return sub_710072FEC4(mActor, dir, *mCheckDist_s, nullptr, false, nullptr);
}

// NON_MATCHING: regalloc (x8/x9 swapped)
void CliffCheckSelect::m34(sead::Vector3f* out) {
    if (!mActor)
        *out = sead::Vector3f::ez;
    mActor->getMtx().getBase(*out, 2);
}

}  // namespace uking::ai
