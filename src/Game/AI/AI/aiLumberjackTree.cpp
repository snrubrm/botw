#include "Game/AI/AI/aiLumberjackTree.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

LumberjackTree::LumberjackTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LumberjackTree::~LumberjackTree() = default;

void LumberjackTree::sub_710048A190() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    xlinkSearchAndEmit(actor, "Leaf", 2, nullptr);
    if (auto* xlink = actor->getXLink())
        xlink->sub_7101231500();
    sead::Vector3f position;
    actor->getMtx().getTranslation(position);
    if (!actor->x_18(&position) && body)
        body->getCenterOfMassInWorld(&position);
    sub_7100734270(actor, mForceSetDropPos_a, position);
    callDeleteAndCreateDropAndEmit(actor, 0);
}

bool LumberjackTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LumberjackTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LumberjackTree::hasPreDeleteCb() {
    return true;
}

void LumberjackTree::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LumberjackTree::loadParams_() {
    getStaticParam(&mFallInterval_s, "FallInterval");
    getStaticParam(&mFellImpRate_s, "FellImpRate");
    getStaticParam(&mFellRotRate_s, "FellRotRate");
    getStaticParam(&mCutOffsetLower_s, "CutOffsetLower");
    getStaticParam(&mCutOffsetUpper_s, "CutOffsetUpper");
    getStaticParam(&mAlphaLower_s, "AlphaLower");
    getStaticParam(&mAlphaSpeed_s, "AlphaSpeed");
    getMapUnitParam(&mCutRate_m, "CutRate");
    getMapUnitParam(&mAngleY_m, "AngleY");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getAITreeVariable(&mLumberjackType_a, "LumberjackType");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
    getAITreeVariable(&mMoveDirection_a, "MoveDirection");
}

}  // namespace uking::ai
