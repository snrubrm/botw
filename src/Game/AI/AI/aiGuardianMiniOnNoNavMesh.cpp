#include "Game/AI/AI/aiGuardianMiniOnNoNavMesh.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniOnNoNavMesh::GuardianMiniOnNoNavMesh(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniOnNoNavMesh::~GuardianMiniOnNoNavMesh() = default;

void GuardianMiniOnNoNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniOnNoNavMesh::leave_() {
    _40.reset();
}

void GuardianMiniOnNoNavMesh::loadParams_() {
    getStaticParam(&mChangeToIceTimer_s, "ChangeToIceTimer");
}

void GuardianMiniOnNoNavMesh::sub_710041E07C() {
    _5c |= 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("アイスメーカー上", &pack);
}

}  // namespace uking::ai
