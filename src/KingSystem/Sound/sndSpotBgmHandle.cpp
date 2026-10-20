#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicDefinition.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace {
// The static initialiser 0x710101e10c sets these (0x71026101c0).
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

Unk_SpotBgmHandle::Unk_SpotBgmHandle(ksys::snd::Unk_710260f248Type type) : Unk_710260f248(type) {}

// `{ ; }` keeps the vtable store (as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
Unk_SpotBgmHandle::~Unk_SpotBgmHandle() { ; }

void Unk_SpotBgmHandle::init(sead::Heap* heap, const sead::SafeString& name,
                            const sead::PtrArray<xlink2::PropertyDefinition>* properties) {
    Unk_710260f248::init(heap, name, properties);
    if (auto* definition = ksys::snd::sub_7100FFD73C()) {
        const auto& category = definition->getMusicCategoryByName(name);
        mCategory.format(category.cstr());
        mPriority = definition->getPriorityValueByCategoryName(category);
    }
}

void Unk_SpotBgmHandle::sub_710101D9D8() {
    if (_124 == 0 && _179)
        _124 = 1;
}

void Unk_SpotBgmHandle::sub_710101D9F4(f32 fade_sec) {
    if (_124 == 0)
        return;
    sub_7101020C08(fade_sec);
    sub_710101DA34();
}

void Unk_SpotBgmHandle::sub_710101DA34() {
    if (_124 != 0 && _179)
        _124 = 0;
}

void Unk_SpotBgmHandle::sub_710101D970() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D5EC(this);
}

void Unk_SpotBgmHandle::sub_710101D9A4() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D718(this);
}

void Unk_SpotBgmHandle::calc() {
    _138.calc();
    Unk_710260f248::calc();
    if (mEntries.size() == 0)
        _17a = false;
}
