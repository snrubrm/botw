#include "Game/AI/AI/aiLumberjackTree.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/actMapDynamicPassive.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::ai {

void Unk_7102403fe8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* damage_mgr = sub_710072BA90(_28->getActor());
    sead::Vector3f position = sead::Vector3f::zero;
    s32 type = -1;
    bool flag = false;
    if (damage_mgr) {
        damage_mgr->m40(&type);
        damage_mgr->getPosition(&position);
        flag = damage_mgr->checkDamageFlags(4);
    }
    if (!sub_71007A4064(type) || (flag | (u32(*a5 - 29) < 3)))
        *a1 = 0;
}

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

void LumberjackTree::onPreDelete() {
    if (_240 != 2)
        return;
    auto* actor = sead::DynamicCast<act::MapDynamicPassive>(mActor);
    if (!actor)
        return;
    auto* object = actor->_b90;
    if (!object)
        return;
    ksys::map::PlacementMgr::instance()->sub_71011E9C28(object, true);
    ksys::map::PlacementMgr::instance()->enableObjStaticCompound(object);
    using Flag = ksys::map::Object::Flag0;
    object->resetFlags0(Flag::_D00400);
    if (!object->getFlags0().isAnyOn({Flag::ActorCreated, Flag::_80000000}) && !object->getProc())
        object->unlinkProc(true);
}

}  // namespace uking::ai
