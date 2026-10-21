#include <gsys/gsysGBuffer.h>

namespace gsys {

// 0x7100c7158c
void GBuffer::setMaterialIdMask(MaterialIdMask mask, u8 value) {
    mMaterialIdMasks[int(mask)] = value;
}

// 0x7100c72f08
void GBuffer::forwardPreShadingStepForXlu(agl::DrawContext* draw_context, int) {
    expandMaterialID_(draw_context, Resolution(1), MaterialIdMask(2), agl::TextureCompSel(2));
}

// 0x7100c73cf4
void GBuffer::entryToDebugTexturePagePreShading(agl::DrawContext*, int,
                                                const agl::utl::DebugTexturePage*) {}

// 0x7100c73af4
void GBuffer::setFormat(BufferType type, agl::TextureFormat format) {
    mBufferRecords[int(type)].mFormat = format;
}

// 0x7100c7259c
void GBuffer::setClearColor(BufferType type, bool enable, const sead::Color4f& color) {
    BufferRecord& record = mBufferRecords[int(type)];
    record.mFlags = enable ? record.mFlags | 1 : record.mFlags & ~1;
    record.mClearColor = color;
}

// 0x7100c73b04
void GBuffer::enableMEM2(BufferType type, bool enable) {
    u8& flags = mBufferRecords[int(type)].mFlags;
    flags = enable ? flags | 2 : flags & ~2;
}

}
