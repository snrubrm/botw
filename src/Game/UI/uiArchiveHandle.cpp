#include "Game/UI/uiArchiveHandle.h"

namespace nn::ui2d {

// 0x71009c3308
ArchiveHandle::ArchiveHandle() = default;

// 0x71009c3358
ArchiveHandle::~ArchiveHandle() = default;

void ArchiveHandle::sub_71009C3570(s32 state) { mBreak.sub_71009B1578(state); }
void ArchiveHandle::sub_71009C3578(s32 state, f32 frame) { mBreak.sub_71009B163C(state, frame); }
void ArchiveHandle::sub_71009C36B8(f32 frame) { mTexture.sub_7100988F30(frame); }
void ArchiveHandle::sub_71009C36C0() { mTexture.sub_7100988FE8(); }
void ArchiveHandle::sub_71009C36C8(s32 category, s32 value, s32 number) {
    mNumber.sub_7100989AF0(category, value, number);
}
Material* ArchiveHandle::sub_71009C3780() const { return mBreak.sub_71009B1738(); }
f32 ArchiveHandle::sub_71009C37A8() const { return mBreak.sub_71009B1784(); }

}  // namespace nn::ui2d
