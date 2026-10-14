#include "Game/Actor/AI/aiLumberjackTree.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyPolytope.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/actMapDynamicPassive.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::act {
// 0x71006e3ab0 (unnamed in the CSV; placeholder name, declaration only): a check on the accessor's actor
// with two words of the contact info.
bool sub_71006E3AB0(ksys::act::BaseProcAccessor* accessor, u32 a2, u32 a3);
}  // namespace uking::act

namespace uking::ai {

void Unk_7102403fe8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
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

bool Unk_7102404020::m0(void* a1, void*, void*, void*, void*, void*,
                        const ksys::act::Struct8Base* info, const ksys::act::PhysicsUserTag* tag) {
    if ((info->_18 & 8) != 0)
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    tag->acquireActor(&accessor);
    if (act::sub_71006E3AB0(&accessor, info->_18, info->_1c))
        return false;
    if ((info->_1c & 0x8000) != 0)
        return false;
    const f32 height = static_cast<const sead::Vector3f*>(a1)->y - _30;
    if (height < _28 || _2c < height)
        return true;
    return false;
}

// NON_MATCHING: store scheduling only (_248 and the _2d8 / _2dc stores land at different points).
LumberjackTree::LumberjackTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: scheduling only (the original loads mActor before the Effect instance).
LumberjackTree::~LumberjackTree() {
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
    ksys::eft::Effect::instance()->getActorTable9FE0().sub_7100DA2330(mActor);
    if (_2e8) {
        ksys::phys::Constraint::destroy(_2e8);
        _2e8 = nullptr;
    }
}

void LumberjackTree::sub_7100489A18(sead::Vector3f* out, const sead::Vector3f& from,
                                    const sead::Vector3f& to) {
    sead::Vector3f dir = to - from;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.equals(sead::Vector3f::zero, 0.01f)) {
        dir.x = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
        dir.y = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
        dir.z = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
        dir.normalize();
    }
    out->set(dir);
}

bool LumberjackTree::sub_710048A50C(ksys::phys::PolytopeShape* shape, bool upper, f32* min_y,
                                    f32* max_y) {
    const f32 volume = shape->getVolume();
    const int num = shape->getNumVertices();
    bool changed = false;
    for (int i = 0; i < num; ++i) {
        sead::Vector3f vertex = shape->getVertex(i);
        if (*min_y > vertex.y)
            *min_y = vertex.y;
        if (*max_y < vertex.y)
            *max_y = vertex.y;
        if ((upper && vertex.y < 1.1f) || (!upper && vertex.y > 1.1f)) {
            vertex.y = 1.1f;
            shape->setVertex(i, vertex);
            changed = true;
        }
    }
    if (!changed)
        return false;

    shape->updateHavokShape();
    const f32 height = *max_y - *min_y;
    f32 bottom = 1.1f;
    f32 top = *max_y;
    if (!upper) {
        bottom = *min_y;
        top = 1.1f;
    }
    shape->setVolume(volume * ((top - bottom) / height));
    return true;
}

// NON_MATCHING: the original uses the vertex count unmasked and signed (PolytopeRigidBody::getNumVertices returns
// int there; ours is declared u16), which also changes the loop register allocation
bool LumberjackTree::sub_710048A708(ksys::phys::PolytopeRigidBody* body, bool upper, f32* min_y,
                                    f32* max_y) {
    const f32 volume = body->getVolume();
    const int num = body->getNumVertices();
    bool changed = false;
    for (int i = 0; i < num; ++i) {
        sead::Vector3f vertex = body->getVertex(i);
        if (*min_y > vertex.y)
            *min_y = vertex.y;
        if (*max_y < vertex.y)
            *max_y = vertex.y;
        if (upper ? vertex.y < 1.1f : vertex.y > 1.1f) {
            vertex.y = 1.1f;
            body->setVertex(i, vertex);
            changed = true;
        }
    }
    if (!changed)
        return false;

    body->updateShape();
    const f32 height = *max_y - *min_y;
    f32 bottom = 1.1f;
    f32 top = *max_y;
    if (!upper) {
        bottom = *min_y;
        top = 1.1f;
    }
    body->setVolume(volume * ((top - bottom) / height));
    return true;
}

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
