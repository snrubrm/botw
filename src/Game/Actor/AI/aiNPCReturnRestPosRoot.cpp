#include "Game/Actor/AI/aiNPCReturnRestPosRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/aiUnk_71024f1658.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

NPCReturnRestPosRoot::NPCReturnRestPosRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReturnRestPosRoot::~NPCReturnRestPosRoot() = default;

bool NPCReturnRestPosRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: inline parameter argument and string descriptor scheduling.
void NPCReturnRestPosRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (npc->_840) {
            npc->_fe8 &= ~0x100;
            npc->_9d8.copy(npc->_840->sub_7100EEEE88(mActor));
        }
    }
    if (auto* schedule = mActor->getSchedule()) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x37, schedule->_248, 0);
        mActor->getASList()->goLimpFromHeadShotMaybe(0x38, schedule->_248, 0);
    }
    const bool raining = wm::callIsRainingOrSnowingOrThunderStorm(false);
    ksys::act::ai::InlineParamPack pack;
    const char* as_name = raining ? "Run_Rain" : "Walk";
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addString(as_name, "DynASKeyName", -1);
    changeChild("Move", &pack);
}

void NPCReturnRestPosRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("Move")) {
        sead::Vector3f dir;
        sead::Matrix34f home;
        mActor->getHomeMtx(&home);
        home.getBase(dir, 2);

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, sead::Vector3f::ez, dir, sead::Vector3f::ey);
        const sead::Vector3f rot{0.0f, angle * axis.y, 0.0f};

        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        pack.addVec3(rot, "TargetRot", -1);
        changeChild("Turn", &pack);
    } else if (isCurrentChild("Turn")) {
        setFinished();
    }
}

void NPCReturnRestPosRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReturnRestPosRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
