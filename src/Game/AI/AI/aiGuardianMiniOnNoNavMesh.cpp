#include "Game/AI/AI/aiGuardianMiniOnNoNavMesh.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
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

void GuardianMiniOnNoNavMesh::calc_() {
    if (!(_50.value <= sead::Mathf::epsilon()))
        _50.update();
    if (isCurrentChild("ナビメッシュなし") && getCurrentChild()->isChangeable() &&
        _50.value <= sead::Mathf::epsilon() && _40.hasProc()) {
        changeToOnIceMaker();
    } else {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("アイスメーカー上") && _40.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_40, &accessor);
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
                _40.reset();
            }
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
            return;
        }
    }
    if (isCurrentChild("アイスメーカー上"))
        sub_710041E15C();
}

}  // namespace uking::ai
