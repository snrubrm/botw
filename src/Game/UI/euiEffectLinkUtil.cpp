#include "Game/UI/euiEffectLinkUser.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100be81bc
Unk_7100be81bc::Unk_7100be81bc(LayoutEx* layout, sead::Heap* heap,
                               sead::Buffer<EffectLinkUser::Bone>* bones)
    : mDepth(0), mHeap(heap), mBones(bones) {
    mLayouts[0] = layout;
}

// 0x7100be8f04
u8 sub_7100BE8F04(LayoutEx* layout) {
    Screen* screen = layout->mScreen;
    return screen->mMgr->get_b42() + screen->mDrawTarget;
}

}  // namespace eui
