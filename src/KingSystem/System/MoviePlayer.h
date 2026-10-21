#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <gfx/seadGraphicsContext.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Name from the CSV (MoviePlayer::createInstance 0x71010b9934, init, __auto0 .. __auto2). A singleton (instance pointer
// at 0x710261f140). Only the members used so far are declared (layout incomplete; lane2 s47).
// Vtable 0x710250b5e8 (hostio::Node only); the singleton disposer sits at 0x8. Size 0x3e0.
class MoviePlayer : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(MoviePlayer)
    MoviePlayer() = default;
    ~MoviePlayer() = default;

public:

    // 0x71010b9a08 (CSV name): empty; InitializeApp calls it with the createInstance heap.
    void init(sead::Heap* heap);

    // Native cleanup clears +0x31/+0x32; start sets +0x31 and StageMgrRun tests it.
    void sub_71010B9C04();
    // 0x71010b9c84 (declared only; placeholder name): forwards to the movie object's update when there is one
    // (false otherwise); EventFlowMovie::m14 returns it
    bool sub_71010B9C84();

    u64 _28 = 0;
    bool _30 = false;
    bool _31 = false;
    bool _32 = false;
    /* 0x38 */ agl::TextureData mTextureData;
    /* 0x160 */ agl::RenderBuffer mRenderBuffer;
    /* 0x1c8 */ agl::RenderTargetColor mRenderTargetColor;
    /* 0x340 */ sead::GraphicsContext mGraphicsContext;
    u64 _3b8 = 0;
    u64 _3c0 = 0;
    u32 _3c8 = 0;
    u64 _3d0 = 0;
    /* 0x3d8 */ s32 mFrameCount = 0;
    /* 0x3dc */ bool _3dc = false;  // set while a movie event is being played (S7Movie::x)
};
KSYS_CHECK_SIZE_NX150(MoviePlayer, 0x3e0);

}  // namespace ksys
