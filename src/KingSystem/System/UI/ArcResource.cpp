#include "KingSystem/System/UI/ArcResource.h"
#include "KingSystem/System/UI/ArcResourceMgr.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/gfx/gfx_ResTexture.h>
#include <nn/ui2d/ArcExtractor.h>
#include "KingSystem/Resource/resHandle.h"

namespace ksys::ui {

// 0x710109d814
ArcResource::ArcResource(ArcResourceMgr* mgr, const sead::SafeString& name, u8* data,
                         res::Handle* handle)
    : eui::ArcResourceMgr::ArcResource(mgr, name, data), mHandle(handle) {}

ArcResource::~ArcResource() {
    if (mTextureResource) {
        auto& texture = mTextureResource->ToData().textureContainerData;
        if (texture.pCurrentMemoryPool.Get() == texture.pTextureMemoryPool.Get())
            texture.pCurrentMemoryPool.Get()->Finalize(sead::GraphicsNvn::instance()->getNnDevice());
        texture.pCurrentMemoryPool.Set(nullptr);
        mTextureResource = nullptr;
    }
    eui::ArcResourceMgr::finalizeInitializedShaderResource(mData);
    nn::ui2d::ArcExtractor::Unrelocate(mData);
    delete mHandle;
    mData = nullptr;
}

}  // namespace ksys::ui
