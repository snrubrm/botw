#include "KingSystem/Effect/eftEffectUnkHelpers.h"

namespace ksys::eft {

u32 Unk_71025125c8::getVertexCountMaybe() const {
    return _10;
}

u32 Unk_71025125c8::getIndexCount() const {
    return _14;
}

void* Unk_71025125c8::get18() const {
    return _18;
}

void* Unk_71025125c8::get20() const {
    return _20;
}

void Unk_71025125c8::getVertexAddress(nn::gfx::GpuAddress* out) const {
    *out = _30;
}

const nn::gfx::GpuAddress& Unk_71025125c8::getIndexAddress() const {
    return _40;
}

bool Unk_71025125c8::m6() const {
    return true;
}

bool Unk_71025125c8::m7() const {
    return false;
}

s32 Unk_71025125c8::m8() const {
    return 0x1905;
}

nn::gfx::IndexFormat Unk_71025125c8::getIndexFormat() const {
    return nn::gfx::IndexFormat_Uint32;
}

void* Unk_71025125c8::get50(u32 idx) const {
    return _50[idx];
}

void Unk_71025125c8::draw(CommandBuffer* buffer, s32 num_instances) {
    buffer->DrawIndexed(nn::gfx::PrimitiveTopology_TriangleList, getIndexFormat(), getIndexAddress(),
                        getIndexCount(), 0, num_instances, 0);
}

void Unk_71025125c8::draw(CommandBuffer* buffer, s32 num_instances, s32 base_instance) {
    buffer->DrawIndexed(nn::gfx::PrimitiveTopology_TriangleList, getIndexFormat(), getIndexAddress(),
                        getIndexCount(), 0, num_instances, base_instance);
}

void Unk_7102512640::reset() {
    _8 = 0.0f;
    _c = 20.0f;
    _10 = 30.0f;
}

void Unk_7102512658::reset() {
    _8 = 0.0f;
    _c = 20.0f;
    _10 = 30.0f;
    _14 = false;
    _18 = 0.0f;
    _1c = 40.0f;
    _20 = 80.0f;
    _24 = 0.35f;
    _28 = 0.0f;
}

Unk_7102512670::~Unk_7102512670() = default;

void Unk_7102512670::lock() {
    mMutex.lock();
}

void Unk_7102512670::unlock() {
    mMutex.unlock();
}

}  // namespace ksys::eft
