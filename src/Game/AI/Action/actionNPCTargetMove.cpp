#include "Game/AI/Action/actionNPCTargetMove.h"
#include <cfloat>
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

NPCTargetMove::NPCTargetMove(const InitArg& arg) : RandomMoveAction(arg) {}

NPCTargetMove::~NPCTargetMove() = default;

// NON_MATCHING: the original compares the actor name with the literal in an inline loop without the
// assureTermination calls / pointer-equality fast path of SafeString::isEqual (a different, unknown comparison).
// NON_MATCHING: same compares and calls; the original materialises the four AS name addresses in separate blocks
// after the compares (here the first two are hoisted above the loops)
void NPCTargetMove::sub_7100204E40() {
    sead::SafeString key(mActor->getASList()->sub_710115ECF4(59, 1));
    const char* name;
    if (key == "Sit")
        name = "Rest";
    else if (key == "SitOnObject")
        name = "Act_SitChair_Wait";
    else if (key == "Crouch")
        name = "Act_Squat";
    else
        name = "Wait";
    playAS(name, true, 0, 0, -1.0f);
}

bool NPCTargetMove::init_(sead::Heap* heap) {
    _90 = sead::DynamicCast<uking::act::NPC>(mActor);
    _98.change(0x4,
               mActor->getParam()->getRes().mGParamList->getNpc()->mIsWalkUnderShelterFromRain.ref());
    if (mActor->getName() == "Npc_TripMaster")
        _98.set(0x18);
    return true;
}

void NPCTargetMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NPCTargetMove::leave_() {
    RandomMoveAction::leave_();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (_90 && (_90->_fe8 & 0x8000000)) {
        auto* controller = mActor->getCharacterController();
        auto* physics = mActor->getPhysics();
        if (controller && physics) {
            const s32 idx = physics->sub_7100FBE7F0("Standing");
            if (idx >= 0)
                controller->sub_7100F5F270(idx);
        }
    }
}

void NPCTargetMove::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mStopTime_s, "StopTime");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mRunGoalDistance_s, "RunGoalDistance");
    getStaticParam(&mDistOnFailure_s, "DistOnFailure");
    getStaticParam(&mIsPathOptimization_s, "IsPathOptimization");
    getStaticParam(&mIsShelterFromRain_s, "IsShelterFromRain");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NPCTargetMove::calc_() {
    RandomMoveAction::calc_();
}

void NPCTargetMove::sub_7100206280() {
    if (!*mIsShelterFromRain_s || _98.isOff(4) ||
        !wm::callIsRainingOrSnowingOrThunderStorm(false) || !_90 || _98.isOff(1) ||
        uking::act::NPC::isZora(mActor))
        return;

    if (mActor->_6a0->_a.isOff(8)) {
        _e4.reset(90.0f);
        m34();
    } else {
        _e4.update();
        if (_e4.value <= FLT_EPSILON)
            playAS("Walk", true, 0, 0, -1.0f);
    }
}

// NON_MATCHING: boolean negation and the common return are materialized differently.
bool NPCTargetMove::sub_71002065FC() {
    if (mActor->getASList()->sub_710115D2D4().length() < FLT_EPSILON || _98.isOff(1) ||
        mActor->getASList()->x_1(0, 0) == "Move_End")
        return false;

    return !mActor->getASList()->x(26, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

void NPCTargetMove::m34() {
    playAS(mASKeyName_s.cstr(), true, 0, 0, -1.0f);
}

sead::SafeString NPCTargetMove::m35() {
    return mASKeyName_s;
}

s32 NPCTargetMove::m32(RandomMovePoints* points) {
    points->add(*mTargetPos_d);
    return *mUpdateTargetPosInterval_s;
}

}  // namespace uking::action
