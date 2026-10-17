#include "Game/gameUnkRttiClasses.h"
#include <cstring>
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Terrain/teraAreaNode.h"
#include <nn/font/font_Util.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAlignPane.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiUtils.h"
#include "Game/Actor/aiUnk_71025b27b8.h"
#include "Game/Actor/aiUnk_71025b2aa8.h"
#include "Game/Actor/aiUnk_71025b2d88.h"
#include "Game/Actor/aiUnk_710070F974.h"
#include <common/aglTextureSampler.h>
#include <common/aglVertexAttribute.h>
#include <common/aglIndexStream.h>
#include <common/aglDrawContext.h>
#include <driver/aglNVNsampler.h>
#include <driver/aglNVNtexture.h>
#include "Game/gameUnkRttiPlaceholders.h"

// Existing placeholder AI tree variable classes whose vtables had no key function so far (the original keeps one
// out-of-line empty destructor per class).
Unk_71025b2aa8::~Unk_71025b2aa8() = default;
Unk_71025b2d88::~Unk_71025b2d88() = default;
Unk_71025b27b8::~Unk_71025b27b8() = default;
Unk_71025c89e8::~Unk_71025c89e8() = default;

// (Unk_71023f3710's destructor is defaulted inline in the header: virtual but trivial,
// so its subclasses keep no D1 of their own. Its RTTI virtuals are defined here so the
// vtable keeps an out-of-line key function.)
bool Unk_71023f3710::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* Unk_71023f3710::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

Unk_710245a498::~Unk_710245a498() = default;

Unk_710245a4c8::~Unk_710245a4c8() = default;

Unk_710245a4f8::~Unk_710245a4f8() = default;

Unk_710245a578::~Unk_710245a578() = default;

Unk_710245bee0::~Unk_710245bee0() = default;

Unk_710245c6b8::~Unk_710245c6b8() = default;

Unk_710245c858::~Unk_710245c858() = default;

Unk_710246c330::~Unk_710246c330() = default;

Unk_710246c360::~Unk_710246c360() = default;

Unk_710246cec8::~Unk_710246cec8() = default;

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71024dcf80::~Unk_71024dcf80() {
    ;
}


Unk_710250dcd8::Unk_710250dcd8() = default;

Unk_710250dcd8::~Unk_710250dcd8() = default;

void Unk_710250dcd8::m11(agl::TextureSampler* sampler, const agl::GPUMemVoidAddr& addr,
                         s32 mip_offset, bool flag) {
    _8 |= 0x20000000;
    sub_710110DB28(sampler, addr, mip_offset, flag);
    _8 |= 8;
}

// NON_MATCHING: lib agl::TextureData's destructor is out of line (the original inlines ~NVNtexture_ at
// TextureData + 0x58), so ours calls ~TextureData and the stack slots of the image copy / texture are
// swapped. Everything else follows the original instruction for instruction.
// Placeholder name. Builds the image's TextureData from the image virtuals, constructs the sampler in
// `sampler` (the caller passes unconstructed storage) and applies the texture data to it.
void Unk_710250dcd8::sub_710110DB28(void* storage, const agl::GPUMemVoidAddr& addr, s32 mip_offset,
                                    s32 flag) {
    const s32 format = m6();
    const s32 filter = m7();
    const s32 size = m9();
    const s32 mip_count = m10();
    agl::TextureData texture;
    new (storage) agl::TextureSampler;
    _10 = storage;
    texture.initialize_(agl::TextureType::cTextureType_2D, static_cast<agl::TextureFormat>(format),
                        size, size, 1, mip_count,
                        static_cast<agl::TextureAttribute>(m4() == 1),
                        static_cast<agl::MultiSampleType>(0), true);
    const agl::GPUMemVoidAddr image(addr);
    texture.setImagePtr(image, 0);
    if (mip_offset) {
        agl::GPUMemAddrBase mip(addr, mip_offset);
        texture.setMipPtr(mip);
    }
    getSamplerMaybe()->applyTextureData(texture);
    getSamplerMaybe()->setWrap(7, 7, 7);
    getSamplerMaybe()->setFilter(u8(filter), u8(filter), 1);
}

void Unk_710250dcd8::m13(void* unused, const void* src, u32 size) {
    const agl::TextureData& texture = getTextureDataMaybe();
    std::memcpy(texture.getImagePtr().getAddress(), src, size);
    texture.getImagePtr().flushCPUCache(size);
}

u32 Unk_710250dcd8::m14(void* dst) {
    const agl::TextureData& texture = getTextureDataMaybe();
    const u32 size = texture.getImageByteSize();
    if (dst)
        std::memcpy(dst, texture.getImagePtr().getAddress(), size);
    return size;
}

void Unk_710250dcd8::sub_710110DD20(bool on) {
    _8 = on ? _8 | 4 : _8 & ~4;
}

void Unk_710250dcd8::sub_710110DD3C() {
    _8 &= ~8;
    static_cast<Unk1*>(_10)->~Unk1();
    _10 = nullptr;
}

Unk_710251b678::~Unk_710251b678() = default;

Unk_7102457a80::~Unk_7102457a80() = default;

Unk_7102457ac0::~Unk_7102457ac0() = default;

Unk_7102499a68::~Unk_7102499a68() = default;

eui::AlignPane* Unk_7102499a68::findAlignPane(const sead::SafeString& name) {
    return nn::font::DynamicCast<eui::AlignPane>(_8->FindPaneByName(name.cstr(), true));
}

void Unk_7102499a68::m4(nn::ui2d::Pane* pane) {
    _8 = pane;
    if (_8)
        _8->SetVisible(false);
    if (_8)
        _8->SetPosition(nn::util::Float3{0.0f, 2000.0f, 0.0f});
}

void Unk_7102499968::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_PostOne_00", true));
    _10 = findAlignPane("N_AlignEdge_00");
}

void Unk_7102499968::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_71024999a8::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_NameOne_00", true));
}

void Unk_71024999a8::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_71024999e8::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18[0] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_00", true));
    _18[1] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_01", true));
    _18[2] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_02", true));
    _10 = findAlignPane("N_Align_00");
}

void Unk_71024999e8::m5(const sead::SafeString& label, s32 idx) {
    if (u32(idx) <= 2 && _18[idx])
        setMessage(_18[idx], label);
}

namespace {
sead::SafeString sStaffRollDLCMessageFile = "LayoutMsg/StaffRollDLC_00";
}  // namespace

// NON_MATCHING: the original reaches the static message file name through a merged-globals base (TU sinit)
// (0x7100a578bc)
void Unk_7102499a68::setMessage(eui::TextBoxEx* box, const sead::SafeString& label) {
    if (!box)
        return;
    eui::MessageString message;
    if (uking::ui::getMessage(sStaffRollDLCMessageFile, label, &message) == 0 && message.getLength() > 0 &&
        sead::WSafeString(message.getString()) != sead::WSafeString(u"EmptyMessage")) {
        box->SetVisible(true);
        box->setMessageString(message, nullptr);
    } else {
        box->SetVisible(false);
        box->setMessageString(eui::MessageString(sead::WSafeString(u"")), nullptr);
    }
    if (_10)
        _10->mNeedsAlignment = true;
}

Unk_7102499968::~Unk_7102499968() = default;

Unk_71024999a8::~Unk_71024999a8() = default;

Unk_71024999e8::~Unk_71024999e8() = default;

Unk_710249a1a0::~Unk_710249a1a0() = default;

eui::AlignPane* Unk_710249a1a0::findAlignPane(const sead::SafeString& name) {
    return nn::font::DynamicCast<eui::AlignPane>(_8->FindPaneByName(name.cstr(), true));
}

void Unk_710249a1a0::m4(nn::ui2d::Pane* pane) {
    _8 = pane;
    if (_8)
        _8->SetVisible(false);
    if (_8)
        _8->SetPosition(nn::util::Float3{0.0f, 2000.0f, 0.0f});
}

void Unk_710249a0a0::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_PostOne_00", true));
    _10 = findAlignPane("N_AlignEdge_00");
}

void Unk_710249a0a0::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_710249a0e0::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_NameOne_00", true));
}

void Unk_710249a0e0::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_710249a120::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18[0] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_00", true));
    _18[1] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_01", true));
    _18[2] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_02", true));
    _10 = findAlignPane("N_Align_00");
}

void Unk_710249a120::m5(const sead::SafeString& label, s32 idx) {
    if (u32(idx) <= 2 && _18[idx])
        setMessage(_18[idx], label);
}

namespace {
sead::SafeString sStaffRollMessageFile = "LayoutMsg/StaffRoll_00";
}  // namespace

// NON_MATCHING: the original reaches the static message file name through a merged-globals base (TU sinit)
// (0x7100a5cffc)
void Unk_710249a1a0::setMessage(eui::TextBoxEx* box, const sead::SafeString& label) {
    if (!box)
        return;
    eui::MessageString message;
    if (uking::ui::getMessage(sStaffRollMessageFile, label, &message) == 0 && message.getLength() > 0 &&
        sead::WSafeString(message.getString()) != sead::WSafeString(u"EmptyMessage")) {
        box->SetVisible(true);
        box->setMessageString(message, nullptr);
    } else {
        box->SetVisible(false);
        box->setMessageString(eui::MessageString(sead::WSafeString(u"")), nullptr);
    }
    if (_10)
        _10->mNeedsAlignment = true;
}

Unk_710249a0a0::~Unk_710249a0a0() = default;

Unk_710249a0e0::~Unk_710249a0e0() = default;

Unk_710249a120::~Unk_710249a120() = default;

// NON_MATCHING: the constructor groups its zero stores in a different order.
Unk_710251d230::Unk_710251d230() = default;
Unk_710251d230::~Unk_710251d230() = default;

void Unk_710251d230::sub_71012EB478(u32 base_vertex, u32 first_index) {
    mBaseVertex = base_vertex;
    _20 = m8();
    mFirstIndex = first_index;
    mIndexCount = m9();
    mFlags |= 0x40000000;
}

void Unk_710251d230::m4(agl::DrawContext* context) {
    mAttribute->activate(context);
}

void Unk_710251d230::m5(agl::DrawContext* context, u32 instances) {
    m6(context, 0, mIndexCount, instances, 0);
}

// NON_MATCHING: draw-range and native buffer-address loads are scheduled differently.
void Unk_710251d230::m6(agl::DrawContext* context, u32 index_offset, u32 count,
                       u32 instances, u32 vertex_offset) {
    if (count == 0)
        return;
    auto* stream = mIndexStream;
    NVNcommandBuffer* command_buffer = context->getCommandBuffer()->ToData()->pNvnCommandBuffer;
    const auto primitive = stream->getPrimitiveType();
    const auto index_address = stream->getBufferAddress() +
                               stream->getElementSize() * (mFirstIndex + index_offset);
    const u32 base_vertex = mBaseVertex + vertex_offset;
    if (instances >= 2) {
        nvnCommandBufferDrawElementsInstanced(command_buffer, primitive,
            NVNindexType(stream->getFormat()), count, index_address,
            base_vertex, mBaseInstance, instances);
    } else if (base_vertex != 0) {
        nvnCommandBufferDrawElementsBaseVertex(command_buffer, primitive,
            NVNindexType(stream->getFormat()), count, index_address, base_vertex);
    } else {
        nvnCommandBufferDrawElements(command_buffer, primitive,
            NVNindexType(stream->getFormat()), count, index_address);
    }
}

namespace ksys::tera {

// 0x71012eb6e8 / 0x71012eb70c follow Unk_710251d230 in the original.
void Unk_71012eb6e8::set(System* system, const Unk_7101106F44* entry, u16 key) {
    mSystem = system;
    mId = entry->mId;
    mIndex = entry->mIndex;
    mKey = key;
    mSystemId = system->_1334;
}

// NON_MATCHING: the original compares the two id bytes with one ldrh and branches on the final compare.
bool Unk_71012eb6e8::isValid(System* const* systems, const Unk_7101106F44* entry, u16 key) const {
    if (mKey != key)
        return false;
    System* system = systems[mSystemId.slot & 7];
    if (mSystem != system || mSystemId.slot != system->_1334.slot ||
        mSystemId.generation != system->_1334.generation)
        return false;
    if (system->_fa8[mIndex] == entry)
        return true;
    if (system->sub_7101115080(mId) == entry)
        return true;
    return false;
}

// NON_MATCHING: the mode and flag stores are merged into one in ours.
Unk_71012EBDBC::Unk_71012EBDBC() = default;

Unk_71012EBDBC::~Unk_71012EBDBC() {
    if (mFlags.isOnBit(0)) {
        Terrain::instance()->_428->tryClose(&mHandle);
        mFlags.resetBit(0);
    }
}

// NON_MATCHING: scheduling of the path store and the mode clamp.
bool Unk_71012EBDBC::open(const char* path, u32 mode) {
    mMode = mode;
    mPath = path;
    if (!Terrain::instance()->_428->tryOpen(&mHandle, path,
                                             sead::FileDevice::FileOpenFlag(mode < 2 ? mode : 2), 0))
        return false;
    mFlags.setBit(0);
    return true;
}

// NON_MATCHING: the zero store of `written` is scheduled before the device load in ours.
void Unk_71012EBDBC::write(const u8* data, u32 size, u32 a3, u32 a4) {
    u32 written = 0;
    Terrain::instance()->_428->tryWrite(&written, &mHandle, data, size);
}

}  // namespace ksys::tera

// NON_MATCHING: placeholder destructor; the original (0x7100155198) also destroys members or bases
// this class does not declare yet.
Unk_710238b148::~Unk_710238b148() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a57d80) also destroys members or bases
// this class does not declare yet.
Unk_71024993a0::~Unk_71024993a0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5ac3c) also destroys members or bases
// this class does not declare yet.
Unk_71024993e0::~Unk_71024993e0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5aa08) also destroys members or bases
// this class does not declare yet.
Unk_7102499a28::~Unk_7102499a28() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5d4c0) also destroys members or bases
// this class does not declare yet.
Unk_7102499ad8::~Unk_7102499ad8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5fef0) also destroys members or bases
// this class does not declare yet.
Unk_7102499b18::~Unk_7102499b18() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5fcbc) also destroys members or bases
// this class does not declare yet.
Unk_710249a160::~Unk_710249a160() = default;

// NON_MATCHING: placeholder destructor; the original (0x710112ed24) also destroys members or bases
// this class does not declare yet.
Unk_710250e490::~Unk_710250e490() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101148888) also destroys members or bases
// this class does not declare yet.
Unk_710250f758::~Unk_710250f758() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101148e08) also destroys members or bases
// this class does not declare yet.
Unk_710250f7d8::~Unk_710250f7d8() = default;
