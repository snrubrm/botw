#include "Game/Actor/AI/aiLumberjackTree.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include <random/seadGlobalRandom.h>
#include <common/aglTextureDataInitializerRAW.h>
#include <common/aglGPUMemBlock.h>
#include <g3d/aglTextureUtilG3D.h>
#include <gsys/gsysModel.h>
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

namespace uking::ai {

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

bool Unk_71024e1b58::sub_7100E18F4C() {
    if (_18.isAllocatedOrFailed())
        return true;
    if (_28.isAllocatedOrFailed())
        return true;
    return false;
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

void Unk_71024e1b58::sub_7100E18110(u8 kind, ksys::act::Actor* actor, sead::Heap* heap) {
    if (!heap)
        return;

    _12 = kind;
    mActor = actor;
    _40 = 0;
    _48 = 0;
    mTextureData.initialize_(agl::TextureType::cTextureType_2D, agl::TextureFormat::cTextureFormat_R8_uNorm,
                             24, 4, 1, 1, static_cast<agl::TextureAttribute>(1),
                             agl::MultiSampleType{}, true);

    const u32 size = mTextureData.getImageByteSize();
    const u32 alignment = mTextureData.getImageAlignment();
    auto* memory = new (heap, 8) agl::GPUMemBlock<u8>;
    memory->allocBuffer_(size, heap, alignment, agl::MemoryAttribute::Default);
    mMaskMemAddr = agl::GPUMemAddrBase(*memory, 0);
    if (mMaskMemAddr.isValid())
        mTextureData.setImagePtr(mMaskMemAddr, 0);

    sub_7100E18274();

    mResTexture = agl::g3d::TextureUtilG3D::convertToResTexture(&mResTextureData, mTextureData, nullptr);
    // The agl declaration returns ResTextureData*; the model API takes the SDK accessor for the
    // same object.
    mActor->getModel()->replaceTexture(
        static_cast<nn::gfx::ResTexture*>(static_cast<void*>(mResTexture)),
        sead::SafeString("ForReplace_Lumberjack"));
}

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

}  // namespace uking::ai
