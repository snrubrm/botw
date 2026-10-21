#include <gsys/gsysGBuffer.h>

namespace gsys {

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
