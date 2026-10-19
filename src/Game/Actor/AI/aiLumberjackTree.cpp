#include "Game/Actor/AI/aiLumberjackTree.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include <random/seadGlobalRandom.h>
#include <common/aglTextureDataInitializerRAW.h>
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
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

// NON_MATCHING: the frame is 0x10 larger (a second SafeString temporary is not shared) and the
// register allocation differs.
void Unk_71024e1b58::sub_7100E18B90(const char* name1, const char* name2) {
    if (_18.isAllocatedOrFailed() || _28.isAllocatedOrFailed() || (_10 & 4) != 0)
        return;

    if (name1 && *name1 != sead::SafeString::cNullChar) {
        ksys::act::InstParamPack pack;
        pack->addMatrix(mActor->getMtx());
        pack->addScale(mActor->getScale());
        const char* unique = mActor->getUniqueName();
        if (unique)
            pack->addModelUser(unique);
        ksys::act::ActorCreator::instance()->requestCreateActor(
            name1, ksys::map::PlacementMgr::instance()->mDynamicHeap, &_18, &pack, nullptr, 2);
    }

    if (name2 && *name2 != sead::SafeString::cNullChar) {
        if (_28.isAllocatedOrFailed())
            _28.deleteProc();
        ksys::act::InstParamPack pack;
        pack->addMatrix(mActor->getMtx());
        pack->addScale(mActor->getScale());
        const char* unique = mActor->getUniqueName();
        if (unique)
            pack->addModelUser(unique);
        ksys::act::ActorCreator::instance()->requestCreateActor(
            name2, ksys::map::PlacementMgr::instance()->mDynamicHeap, &_28, &pack, nullptr, 2);
    }
}

void Unk_71024e1b58::sub_7100E18578() {
    if ((_10 & 0x100) != 0)
        return;

    _50 = 1.0f;
    _40 = 0;
    _48 = 0;
    mContactPointInfo = nullptr;

    if (u32(_12 - 1) < 4) {
        _10 |= 4;
        sub_7100E18274();
        if (auto* model = mActor->getModel())
            Unk_710260af28::instance()->sub_7100F1EA00(model, model->getScale().y);
        return;
    }

    if (_12 != 0)
        return;

    for (u32 i = 0; i < 24; ++i)
        mAlphas[i] = 1.0f;

    auto* set = mActor->getPhysics()->findBodyByName("Tgt");
    if (!set || set->getRigidBodies().size() == 0)
        return;
    auto* body = set->getRigidBodies()[0];
    if (!body)
        return;

    body->addToWorld();
    auto* info = body->getContactPointInfo();
    mContactPointInfo = info;
    if (!info)
        return;

    info->subscribeLayer(ksys::phys::ContactLayer::SensorAttackPlayer);
    info->subscribeLayer(ksys::phys::ContactLayer::SensorAttackEnemy);
}

void Unk_71024e1b58::sub_7100E18A38(const char* name1, const char* name2, bool arg) {
    const u16 flags = _10;
    _10 = flags | 0x400;
    if ((flags & 4) != 0)
        return;
    _10 = arg ? (flags | 0x408) : ((flags | 0x400) & ~u16(8));
    _50 = 0;

    if (_18.isAllocatedOrFailed() || _28.isAllocatedOrFailed()) {
        const bool ready = (_18.isProcReady() || _18.hasProcCreationFailed()) &&
                           (_28.isProcReady() || _28.hasProcCreationFailed());
        if (!ready)
            sub_7100E18B90(name1, name2);
    } else {
        sub_7100E18B90(name1, name2);
    }

    _10 |= 0x30;

    ksys::phys::RigidBody* body = nullptr;
    if (auto* set = mActor->getPhysics()->findBodyByName("Tgt")) {
        if (set->getRigidBodies().size() != 0)
            body = set->getRigidBodies()[0];
    }
    body->removeFromWorld();

    _10 |= 4;
    sub_7100E18274();

    if (auto* model = mActor->getModel())
        Unk_710260af28::instance()->sub_7100F1EA00(model, model->getScale().y);
}

// NON_MATCHING: the checkerboard value becomes one ubfiz instead of and + lsl, and the eor operands
// are swapped (4 bytes shorter).
void Unk_71024e1b58::sub_7100E18274() {
    agl::TextureData& texture = mTextureData;
    if (texture.getImageByteSize() != 0) {
        for (u32 i = 0; i < texture.getImageByteSize(); ++i) {
            s32 value;
            if ((_10 & 8) != 0) {
                u32 width = texture.getWidth();
                if (width < 2)
                    width = 1;
                const u32 row = i / width;
                const u32 col = i % width;
                value = s32((col ^ row) % 2) * 2 - 1;
            } else if ((_10 & 4) != 0) {
                u32 width = texture.getWidth();
                if (width < 2)
                    width = 1;
                const u32 row = i / width;
                const u32 col = i % width;
                const u32 min_height = texture.getMinHeight_();
                f32 v = 0.0f;
                if (((row ^ col) & 1) == 0) {
                    const u32 height = s32(min_height) > s32(texture.getHeight())
                                           ? min_height
                                           : texture.getHeight();
                    const f32 t = (f32(row) - 1.0f) / (f32(height) - 1.0f);
                    v = sead::Mathf::clamp(t, 0.0f, 1.0f);
                }
                const u32 index = col < 24 ? col : 0;
                const f32 alpha = mAlphas[index] < 1.0f ? 0.0f : 1.0f;
                const f32 a = v * alpha;
                if (a <= 0.0f) {
                    value = 0;
                } else {
                    const s32 x = s32(a * 255.0f);
                    value = x != 0 ? x : 1;
                }
            } else {
                value = 0;
            }
            static_cast<u8*>(mMaskMemAddr.getAddress())[i] = u8(value);
        }
    }

    for (u32 i = 0; i < sead::Mathu::max(texture.getWidth(), 1u); ++i) {
        f32 value;
        if ((_10 & 8) == 0) {
            const s32 index = i < 24 ? s32(i) : 0;
            value = mAlphas[index];
            if ((_10 & 4) != 0) {
                if (value >= 1.0f && i % 3 == 0)
                    value = 0.75f;
                if (value <= 0.5f)
                    value = sead::GlobalRandom::instance()->getF32() * 0.5f;
            }
        } else {
            const f32 r = sead::GlobalRandom::instance()->getF32();
            value = r < 0.2f ? 0.75f : 1.0f;
            const s32 index = i < 24 ? s32(i) : 0;
            value *= mAlphas[index];
        }
        static_cast<u8*>(mMaskMemAddr.getAddress())[i] = u8(s32(value * 255.0f));
    }

    const s32 min_height = s32(texture.getMinHeight_());
    agl::TextureDataInitializerRAW::initialize(
        &texture, mMaskMemAddr, texture.getImageByteSize(), texture.getFormat(),
        s32(sead::Mathu::max(texture.getWidth(), 1u)),
        min_height > s32(texture.getHeight()) ? min_height : s32(texture.getHeight()), nullptr);
    mMaskMemAddr.flushCPUCache(texture.getImageByteSize());
}

void Unk_7102403fe8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* damage_mgr = sub_710072BA90(_28->getActor());
    sead::Vector3f position = sead::Vector3f::zero;
    s32 type = -1;
    bool flag = false;
    if (damage_mgr) {
        damage_mgr->getAttackDirType(&type);
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

void LumberjackTree::changeToFelling() {
    ksys::act::disableAttClient(mActor, "LockOn");
    if (_2e0) {
        if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
            if (mgr->_8)
                mgr->_8->sub_710102C9E8(_2e0);
        }
    }
    _2e0 = nullptr;
    ksys::eft::Effect::instance()->getActorTable9FE0().sub_7100DA2330(mActor);
    sub_71007A4440(mActor, &_70);
    if (auto* damage_mgr_base = mActor->getDamageMgr()) {
        if (auto* damage_mgr = sead::DynamicCast<act::DamageManager>(damage_mgr_base))
            damage_mgr->removeDamageCallback(&_40);
    }
    changeChild("伐採");
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
    sub_71007A4440(mActor, &_70);
    if (auto* damage_mgr_base = mActor->getDamageMgr()) {
        if (auto* damage_mgr = sead::DynamicCast<act::DamageManager>(damage_mgr_base))
            damage_mgr->removeDamageCallback(&_40);
    }
    if (_2e0) {
        if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
            if (mgr->_8)
                mgr->_8->sub_710102C9E8(_2e0);
        }
    }
    _2e0 = nullptr;
    if (_2e8)
        _2e8->sub_7100F6A074();
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

// NON_MATCHING: return value kept in a callee-saved register shared with the inlined listener (regalloc /
// block layout).
bool LumberjackTree::handleMessage_(const ksys::Message* message) {
    if (_110._30)
        return false;
    auto* actor = mActor;
    if (!ksys::act::hasTag(actor, 0x2b533845))
        return false;

    if (message->getType() == 0x8000019) {
        _24b = false;
        return true;
    }

    if (_a8.m2(*message)) {
        if (_38 && _38->sub_7100E18EC4()) {
            _f8.sub_710070DE10(message->getSource(), true);
            _a8.x();
        }
    } else if (!_110.m2(*message)) {
        return false;
    }

    _24b = true;
    // inline-only in the original: the body of LodState::sub_710125122C (as in PhysicsUserTag)
    if (auto* lod = actor->getLodState()) {
        lod->mFlags8.reset(0x40);
        lod->_60 = 0;
    }
    return true;
}

}  // namespace uking::ai

bool Unk_7102404060::m2(const ksys::Message& message) {
    if (message.getType() != 0x8000018)
        return false;

    auto* payload = static_cast<Unk_7102404060_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// 0x7100e18ec4 (its own TU in the original, far from LumberjackTree; kept with its only known user)
// True once both handles have finished creating their procs (ready or failed).
// NON_MATCHING: the original computes &_18 after the first test; ours hoists it (ldr pre-index)
bool uking::ai::Unk_71024e1b58::sub_7100E18EC4() {
    if (_18.isAllocatedOrFailed() || _28.isAllocatedOrFailed()) {
        if (_18.isProcReady() || _18.hasProcCreationFailed()) {
            if (_28.isProcReady())
                return true;
            if (_28.hasProcCreationFailed())
                return true;
        }
    }
    return false;
}
