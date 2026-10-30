#include <gsys/gsysCameraAnimation.h>
#include <gsys/gsysModelProceduralShape.h>
#include <nn/g3d/ResFile.h>

namespace gsys {

CameraAnimation::CameraAnimation()
    : mCurrentScene(-1), mCurrentCamera(-1), mFrame(-2.0f), _2c{},
      mMatrix(sead::Matrix34f::ident) {}

CameraAnimation::~CameraAnimation() {
    for (u32 i = 0; i < mFile->mSceneAnimCount; ++i)
        mScenes[i].cameras.freeBuffer();
    mScenes.freeBuffer();
}

CameraAnimation* CameraAnimation::create(ModelResource* resource, const sead::SafeString&,
                                         sead::Heap* heap) {
    auto* animation = new (heap) CameraAnimation;
    animation->initialize_(resource, heap);
    return animation;
}

// 0x71014099f8: the two delegate members default-construct to their UnbindDummy tables.
ModelProceduralShape::ModelProceduralShape() = default;

// 0x7101409a28: the members have no destructor; the original body is empty.
ModelProceduralShape::~ModelProceduralShape() {}

void CameraAnimation::sub_71014092F8(CameraAnimation* animation) {
    delete animation;
}
}  // namespace gsys
