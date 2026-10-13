#include "KingSystem/Resource/resBfRes.h"
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResModel.h>
#include <nn/g3d/ResShape.h>
#include <gsys/gsysG3dResModelEx.h>
#include <gsys/gsysG3dResShapeEx.h>
#include <gsys/gsysModelShaderVariationKey.h>
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

// Native 25149C8 starts true; setUseTex2 writes it and BfRes::afterParse selects
// the texture suffix with it. Keep this texture choice within the BfRes family.
static bool sUseTex2 = true;

Unk_71024f9a90::~Unk_71024f9a90() = default;

Unk_71024f9ad8::~Unk_71024f9ad8() = default;

Unk_71025148b8::Unk_71025148b8() = default;

Unk_71025148b8::Unk_71025148b8(const sead::SafeString& name) : _10(name.cstr()) {}

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

Unk_71025149d0::~Unk_71025149d0() = default;

void Unk_71025149d0::m2(const void* arg) {
    mOwner->sub_71011FFD28(static_cast<const CallbackArg*>(arg)->mHandle->sub_7100FE83EC());
}

void BfRes::sub_71011FFD28(nn::gfx::ResTexture* texture) {
    if (!_50) {
        stubbedLogFunction();
        return;
    }
    if (sub_71011FFF3C()) {
        if (!(_40 & 4))
            _40 = (_40 & ~7) | 4;
    } else if (!(_40 & 2)) {
        _40 = (_40 & ~7) | 2;
    }
    sub_71011FF9B8();
    if (!(_40 & 2))
        _168.sub_7100FE85DC();
    auto lock = sead::makeScopedLock(_b8);
    for (auto* binding : _60) {
        if (binding)
            binding->sub_7100FDD9C0(texture);
    }
}

void Unk_71025149d0::m3(const void* arg) {
    auto* owner = mOwner;
    auto* texture = static_cast<const CallbackArg*>(arg)->mHandle->sub_7100FE83EC();
    if (!owner->_50) {
        stubbedLogFunction();
        return;
    }
    owner->_198.pushBack(texture);
    if (!owner->mListNode.isLinked())
        ResourceMgrTask::instance()->registerBfRes(owner);
}

void Unk_71025149d0::m4(const void* arg) {
    auto* owner = mOwner;
    auto* texture = static_cast<const CallbackArg*>(arg)->mHandle->sub_7100FE83EC();
    if (!owner->_50) {
        stubbedLogFunction();
        return;
    }
    owner->_40 = (owner->_40 & ~7) | 4;
    auto lock = sead::makeScopedLock(owner->_b8);
    for (auto* binding : owner->_60) {
        if (binding)
            binding->sub_7100FDD9C0(texture);
    }
}

}  // namespace ksys::res

namespace ksys::res {

Unk_7102514a08 sUnk_7102514a38;

void Unk_7102514a08::m3(const MaterialArg&) {}

// NON_MATCHING: string comparison register allocation and the common render-type
// selection tail differ from the original.
void Unk_7102514a08::m2(const ShaderAssignArg& arg) {
    const sead::SafeString model_name = arg.model->getResModel()->GetName();
    const sead::SafeString shape_name = arg.shape->getResShape()->GetName();
    u32 index;
    const char* render_type;
    if (model_name == "TeraTerrain") {
        if (shape_name == "NormalNear") {
            index = 0;
            render_type = "0";
        } else if (shape_name == "NormalMiddle") {
            index = 1;
            render_type = "0";
        } else if (shape_name == "NormalFar") {
            index = 2;
            render_type = "0";
        } else if (shape_name == "DegeneracyX") {
            index = 3;
            render_type = "2";
        } else if (shape_name == "DegeneracyY") {
            index = 4;
            render_type = "1";
        } else {
            return;
        }
    } else if (model_name == "TeraWater") {
        if (shape_name == "Normal") {
            index = 5;
            render_type = "0";
        } else if (shape_name == "DegeneracyX") {
            index = 6;
            render_type = "2";
        } else if (shape_name == "DegeneracyY") {
            index = 7;
            render_type = "1";
        } else {
            return;
        }
    } else if (model_name == "TeraRoute") {
        if (shape_name == "Dependence") {
            index = 8;
            render_type = "0";
        } else if (shape_name == "Independence") {
            index = 9;
            render_type = "1";
        } else {
            return;
        }
    } else {
        return;
    }
    sub_7100F3F84C(index);
    arg.variation_key->pushBack("tera_render_type", render_type);
}

}  // namespace ksys::res
