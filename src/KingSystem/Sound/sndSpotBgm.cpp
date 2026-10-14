#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMusicDefinition.h"

Unk_SpotBgmHandle::Unk_SpotBgmHandle(ksys::snd::Unk_710260f248Type type) : Unk_710260f248(type) {}

// `{ ; }` keeps the vtable store (as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
Unk_SpotBgmHandle::~Unk_SpotBgmHandle() { ; }

void Unk_SpotBgmHandle::m10(sead::Heap* heap, const sead::SafeString& name,
                            const sead::PtrArray<const xlink2::PropertyDefinition>* properties) {
    Unk_710260f248::m10(heap, name, properties);
    if (auto* definition = ksys::snd::sub_7100FFD73C()) {
        const auto& category = definition->getMusicCategoryByName(name);
        mCategory.format(category.cstr());
        mPriority = definition->getPriorityValueByCategoryName(category);
    }
}

void Unk_SpotBgmHandle::sub_710101D970() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D5EC(this);
}

void Unk_SpotBgmHandle::sub_710101D9A4() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D718(this);
}

void Unk_SpotBgmHandle::m11() {
    _138.calc();
    Unk_710260f248::m11();
    if (mEntries.size() == 0)
        _17a = false;
}

void Unk_SpotBgmInstance::sub_71010242C8() {
    if (!(_368 & 4))
        return;
    const f32 value = (_368 & 0x8000) ? 1.0f : 0.0f;
    _368 &= ~0xcu;
    _260 = value;
}

void Unk_SpotBgmInstance::sub_71010242F0() {
    _308 = 1;
    _368 |= 0x200;
    _310.setValueImmediate(0.0f);
}

// NON_MATCHING: placeholder destructor; the original (0x7101021558) also destroys members or bases
// this class does not declare yet.
Unk_71025008d0::~Unk_71025008d0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101021db8) also destroys members or bases
// this class does not declare yet.
Unk_7102500a00::~Unk_7102500a00() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101025acc) also destroys members or bases
// this class does not declare yet.
Unk_7102500e08::~Unk_7102500e08() = default;
