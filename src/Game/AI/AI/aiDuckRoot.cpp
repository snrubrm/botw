#include "Game/AI/AI/aiDuckRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DuckRoot::DuckRoot(const InitArg& arg) : PreyRoot(arg) {}

DuckRoot::~DuckRoot() = default;

bool DuckRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void DuckRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
}

void DuckRoot::leave_() {
    PreyRoot::leave_();
}

void DuckRoot::loadParams_() {
    PreyRoot::loadParams_();
}

void DuckRoot::calc_() {
    if (_200 < -3.0f && m34())
        sub_7100504ED0();
    PreyRoot::calc_();
}

bool DuckRoot::m34() {
    return PreyRoot::m34();
}

bool DuckRoot::m35() {
    if (isCurrentChild("滝接触"))
        return false;
    return PreyRoot::m35();
}

bool DuckRoot::m37() {
    if (isCurrentChild("滝接触"))
        return false;
    return PreyRoot::m37();
}

// 0x71003740f8
void DuckRoot::m41() {
    if (isCurrentChild("滝接触"))
        return;
    if (!isCurrentChild("リアクション") && sub_7100504070()) {
        if (!mActor->isDeletedOrDeleting())
            sub_7100374194();
        return;
    }
    PreyRoot::m41();
}

// 0x7100374194
void DuckRoot::sub_7100374194() {
    sub_7100504BF0();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("滝接触", &pack);
}

}  // namespace uking::ai
