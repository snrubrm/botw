#include "Game/AI/AI/aiOutOfScreen.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OutOfScreen::OutOfScreen(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OutOfScreen::~OutOfScreen() = default;

bool OutOfScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OutOfScreen::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F4054();
    mActor->getLodState()->mFlags10.set(0x40);
}

void OutOfScreen::sub_71004F4054() {
    sead::Vector3f pos;
    sub_71004F4270(&pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void OutOfScreen::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OutOfScreen::loadParams_() {
    getStaticParam(&mUpdateInterval_s, "UpdateInterval");
    getStaticParam(&mTagetDistance_s, "TagetDistance");
    getStaticParam(&mDeleteDistance_s, "DeleteDistance");
}

}  // namespace uking::ai
