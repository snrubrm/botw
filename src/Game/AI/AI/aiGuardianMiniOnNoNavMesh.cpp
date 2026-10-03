#include "Game/AI/AI/aiGuardianMiniOnNoNavMesh.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniOnNoNavMesh::GuardianMiniOnNoNavMesh(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniOnNoNavMesh::~GuardianMiniOnNoNavMesh() = default;

void GuardianMiniOnNoNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    _40.reset();
    _5c = 0;
    if (sub_710041DBE0())
        _50.reset(*mChangeToIceTimer_s);
    changeChild("ナビメッシュなし", params);
}

void GuardianMiniOnNoNavMesh::leave_() {
    _40.reset();
}

void GuardianMiniOnNoNavMesh::loadParams_() {
    getStaticParam(&mChangeToIceTimer_s, "ChangeToIceTimer");
}

void GuardianMiniOnNoNavMesh::changeToOnIceMaker() {
    _5c |= 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("アイスメーカー上", &pack);
}

}  // namespace uking::ai
