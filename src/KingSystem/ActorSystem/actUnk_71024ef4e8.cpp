#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"

namespace ksys::act {

void Unk_71024ef4e8::sub_7100EB2448() {
    if (mAttachInfo)
        mAttachInfo->sub_7100EB0D30();
}

void Unk_71024ef4e8::sub_7100EB57F0(const sead::Matrix34f& mtx) {
    mMtx = mtx;
    _110.reset(0x880000);
    _110.set(0x80000);
    _188 = mtx;
    _1b8 = 1.0f;
    _1bc = 1.0f;
}

}  // namespace ksys::act
