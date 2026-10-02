#include "Game/AI/AI/aiInsectFairyRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

InsectFairyRoot::InsectFairyRoot(const InitArg& arg) : InsectRoot(arg) {}

InsectFairyRoot::~InsectFairyRoot() = default;

bool InsectFairyRoot::init_(sead::Heap* heap) {
    return InsectRoot::init_(heap);
}

void InsectFairyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    InsectRoot::enter_(params);
}

void InsectFairyRoot::leave_() {
    InsectRoot::leave_();
}

void InsectFairyRoot::loadParams_() {
    InsectRoot::loadParams_();
}

void InsectFairyRoot::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("解凍後")) {
        m38();
        return;
    }
    InsectRoot::calc_();
}

bool InsectFairyRoot::m34() {
    if (isCurrentChild("解凍後"))
        return false;
    return InsectRoot::m34();
}

void InsectFairyRoot::m44() {
    m45();
    _f5 = false;
}

void InsectFairyRoot::m45() {
    sead::Vector3f pos;
    mActor->getHomePos(&pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("解凍後", &params);
}

}  // namespace uking::ai
