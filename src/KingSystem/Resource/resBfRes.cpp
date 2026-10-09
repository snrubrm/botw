#include "KingSystem/Resource/resBfRes.h"
#include <nn/g3d/ResFile.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

// Native 25149C8 starts true; setUseTex2 writes it and BfRes::afterParse selects
// the texture suffix with it. Keep this texture choice within the BfRes family.
static bool sUseTex2 = true;

void setUseTex2(bool use) {
    if (sUseTex2 == use)
        return;
    sUseTex2 = use;
    clearAllCaches();
    stubbedLogFunction();
}

nn::gfx::ResTexture* BfRes::sub_710120033C(u32 hash) {
    auto lock = sead::makeScopedLock(_f8);
    for (auto& entry : _150) {
        if (entry.hash == hash)
            return entry.handle.sub_7100FE83EC();
    }
    return nullptr;
}

// NON_MATCHING: the original stores _41 right after Resource::Resource() and _40 later (ours merges the two bytes into
// one halfword store) and schedules the 0x48 / 0x58 / 0x180 / 0x190 stores differently.
BfRes::BfRes() {
    _138.initOffset(8);
    _150.initOffset(8);
}

BfRes::~BfRes() = default;

s32 BfRes::getLoadDataAlignment() const {
    return 0x1000;
}

bool BfRes::needsParse() const {
    return true;
}

bool BfRes::m2_() {
    return _50 != nullptr;
}

// NON_MATCHING: the alignment warning branch has a different block order.
void BfRes::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {
    u32 alignment = sub_7100FDDB40(buffer)->GetAlignment();
    if ((alignment & 0xfff) && ((alignment + 0x1fff) & 0x1000))
        stubbedLogFunction();
}

void BfRes::onDestroy_() {
    sub_7100FDDB70(sub_7100FDDB40(mRawData));
}

void BfRes::sub_71011FFDF4(sead::TListNode<Unk_71024f9958*>* node) {
    auto lock = sead::makeScopedLock(_b8);
    _60.pushBack(node);
}

void BfRes::sub_71011FFE74(sead::TListNode<Unk_71024f9958*>* node) {
    auto lock = sead::makeScopedLock(_b8);
    _60.erase(node);
}

void BfRes::sub_71011FFECC() {
    auto lock = sead::makeScopedLock(_b8);
    for (auto* owner : _60) {
        if (owner)
            owner->sub_7100FDDA60(&_198);
    }
    _198.clear();
}

}  // namespace ksys::res
