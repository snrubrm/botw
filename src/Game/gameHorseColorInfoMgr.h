#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <gsys/gsysModel.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"

// The material colors and texture names copied by 0x710094c8cc, after initialization at
// 0x7100a5090c. ScreenShopHorse consumes the four colors and both 64-character names.
struct HorseColorInfo {
    HorseColorInfo();
    sead::Color4f mColors[4];
    sead::FixedSafeString<64> mTextureName;
    sead::FixedSafeString<64> mTextureName2;
};
static_assert(sizeof(HorseColorInfo) == 0xf0);

// Name from the CSV (HorseColorInfoMgr::createInstance 0x710094c374). The singleton is created
// through SEAD_SINGLETON_DISPOSER (sInstance 0x71025d6708, SingletonDisposer_::sStaticDisposer
// 0x71025d6700): createInstance allocates 0x218 bytes, builds the disposer at +0x08 and then the
// instance (primary vtable 0x71024752b8, three res::ResDerived, the load-resources delegate at
// +0x138 and the ksys::ManagedTask at +0x158).
class HorseColorInfoMgr {
    SEAD_SINGLETON_DISPOSER(HorseColorInfoMgr)

public:
    HorseColorInfoMgr();
    virtual ~HorseColorInfoMgr();

    // 0x710094c638 (placeholder name): clears the flag byte `_28`.
    void sub_710094C638();
    // 0x710094c4b8: the managed task's body, loads the three res::ResDerived resources.
    bool loadResources(void* arg);
    // 0x710094c810: the destructor's cleanup: cancels the load task, frees the models and the heap
    // and unloads the three resources.
    void sub_710094C810();
    // 0x710094d018: declaration-only model creation request.
    void sub_710094D018();
    // 0x710094d0f8 (declared only; called after the horse layout is unloaded)
    void sub_710094D0F8();

    // 0x710094cdcc: selects the material animations from the three input values.
    void sub_710094CDCC(const s32* kind, const s32* variant, const s32* frame);
    // 0x710094c8cc: copies colors and texture names from the horse models.
    void sub_710094C8CC(HorseColorInfo* info);
    // 0x710094c640 / 0x710094d114 (placeholder names): the resource load step and the model creation.
    void sub_710094C640();
    void createModels();

public:
    /* 0x28 */ u8 _28;  // bit 1: the horse layout is already available
    /* 0x29 */ u8 _29;
    u8 _2a[2];
    /* 0x2c */ s32 _2c;  // 2: the layout resource is loaded on request
    /* 0x30 */ sead::ExpHeap* mHeap;
    /* 0x38 */ gsys::Model* mModel;
    /* 0x40 */ gsys::Model* mTextureModel;
    /* 0x48 */ ksys::res::ResDerived mModelRes;
    /* 0x98 */ ksys::res::ResDerived mTextureRes;
    /* 0xe8 */ ksys::res::ResDerived mAnimRes;
    /* 0x138 */ ksys::TaskDelegateT<HorseColorInfoMgr> mLoadDelegate;
    /* 0x158 */ ksys::ManagedTask mLoadTask;
};
KSYS_CHECK_SIZE_NX150(HorseColorInfoMgr, 0x218);
