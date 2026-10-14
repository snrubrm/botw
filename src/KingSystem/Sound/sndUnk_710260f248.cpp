#include <aal/aalSoundSource.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2SystemSLink.h>
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_710260f248::Unk_710260f248(Unk_710260f248Type type) : mType(type) {
    mEntries.initOffset(0x40);
}

Unk_710260f248::~Unk_710260f248() {
    if (mType != Unk_710260f248Type::_3 && (_68._18 & 3) == 0)
        sub_7100FFD71C()->sub_7100FF8B94(this);
    if (auto* mgr = sub_7100FFF124())
        mgr->sub_71012BE234(this);
    if (mUserInstance) {
        mUserInstance->destroy();
        mUserInstance = nullptr;
    }
    mEntries.clear();
}

void Unk_710260f248::hm3(const Unk_710260f248M3Arg& arg) {
    auto* supplier = sub_7100FFD71C()->sub_7100FF8A24();
    if (!supplier)
        return;
    auto* handle = arg.handle;
    if (!handle)
        return;
    auto* source = handle->getSoundSource();
    if (!source)
        return;
    source->setSpeakerBalanceSupplier(supplier);
    supplier->sub_7100FF8C74(*handle);
}

void Unk_710260f248::calc() {
    _a8.calc();
    bool playing = false;
    for (auto& entry : mEntries.robustRange()) {
        if (entry.sub_7100FF6C1C(this)) {
            playing = true;
        } else {
            entry.sub_7100FF6A44();
            mEntries.erase(&entry);
        }
    }
    if (!mUserInstance)
        return;
    if (playing || xlink2::SystemSLink::instance()->isServerConnecting()) {
        auto* user_instance = mUserInstance;
        user_instance->preCalc();
        user_instance->postCalc();
    }
}

Unk_710260f248Entry* Unk_710260f248::sub_71010209FC(const sead::SafeString& name) {
    auto* user_instance = mUserInstance;
    if (!user_instance)
        return nullptr;
    xlink2::Locator locator;
    if (!user_instance->searchAsset(&locator, name.cstr()))
        return nullptr;
    return sub_7101020A88(locator);
}

Unk_710260f248Entry* Unk_710260f248::sub_7101020A88(const xlink2::Locator& locator) {
    if (!locator.getAssetCallTable() || !(_68._18 & 1))
        return nullptr;
    xlink2::HandleSLink handle;
    mUserInstance->emit(locator, &handle);
    if (!handle.isActive())
        return nullptr;
    auto* mgr = SoundMgr::instance()->_30;
    if (!mgr)
        return nullptr;
    auto* entry = mgr->sub_7100FF89A0();
    if (!entry)
        return nullptr;
    entry->sub_7100FF6A18(this, handle);
    mEntries.pushBack(entry);
    return entry;
}

void Unk_710260f248::sub_7101020988(sead::Heap* heap) {
    if (mType != Unk_710260f248Type::_2)
        return;
    SoundMgr::instance()->_60->sub_7101058734(mName, &_68, heap, false);
    if ((_68._18 & 1) && mUserInstance)
        mUserInstance->setAssetInfoReader(&_68);
}

void Unk_710260f248::sub_7101020BB0(f32 fade_sec) {
    if (fade_sec == 0.0f)
        return;
    _a8.setValueImmediate(0.0);
    _a8.moveTo(1.0, fade_sec);
}

void Unk_710260f248::sub_7101020C08(f32 fade_sec) {
    for (auto& entry : mEntries) {
        if (entry.sub_7100FF6DF4(this))
            entry.sub_7100FF6A64(fade_sec);
    }
}

// NON_MATCHING: the last bit test becomes ubfx here; the original branches to the shared `return true`.
bool Unk_710260f248::sub_7101020CEC() {
    if (mType == Unk_710260f248Type::_3 || (_68._18 & 3) != 0)
        return true;
    if (!_68.sub_7101057258(mName, sub_7100FFD71C()->_80))
        return false;
    if (_68._18 & 1) {
        if (mUserInstance)
            mUserInstance->setAssetInfoReader(&_68);
        return true;
    }
    if (_68._18 & 2)
        return true;
    return false;
}

}  // namespace ksys::snd
