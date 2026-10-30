#pragma once

#include <hostio/seadHostIONode.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace nn::g3d {
class ResFile;
class ResSceneAnim;
class ResCameraAnim;
}

namespace gsys {
class ModelResource;

// The original vtable has Node::getNodeClassType before the own destructors.
// Size from the create factory (0x71014090b4 allocates 0xa0 bytes with alignment 8).
// The constructor zeroes the 0x44 bytes at +0x2c, stores two -1
// values at +0x20 and -2.0f at +0x28, and copies Matrix34f::ident to +0x70 (three 16-byte stores
// at +0x70 / +0x80 / +0x90, the same sequence evt::CameraSystem::sub_7100DA44EC writes on its
// camera-animation resource). initialize_ (0x7101409154) fills a 0x18-byte-element buffer whose
// count / buffer live at +0x08 / +0x10 and stores the resource file at +0x18.
class CameraAnimation : public sead::hostio::Node {
public:
    CameraAnimation();
    // NON_MATCHING: the compiler reloads the scene count inside the free loop and uses a
    // different loop index width.
    virtual ~CameraAnimation();
    // NON_MATCHING: member initialization emits the matrix copy after clearing the result bytes,
    // while the original does those operations in the opposite order.
    static CameraAnimation* create(ModelResource* resource, const sead::SafeString& name,
                                   sead::Heap* heap);
    static void sub_71014092F8(CameraAnimation* animation);

private:
    struct Scene {
        nn::g3d::ResSceneAnim* resource;
        sead::Buffer<nn::g3d::ResCameraAnim*> cameras;
    };
    static_assert(sizeof(Scene) == 0x18);

    void initialize_(ModelResource* resource, sead::Heap* heap);

    /* 0x08 */ sead::Buffer<Scene> mScenes;
    /* 0x18 */ nn::g3d::ResFile* mFile;
    /* 0x20 */ s32 mCurrentScene;
    /* 0x24 */ s32 mCurrentCamera;
    /* 0x28 */ f32 mFrame;
    u8 _2c[0x44];

public:
    sead::Matrix34f mMatrix;
};
static_assert(sizeof(CameraAnimation) == 0xa0);

}  // namespace gsys
