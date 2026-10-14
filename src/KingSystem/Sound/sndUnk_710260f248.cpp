#include <aal/aalSoundSource.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndBgmMgr.h"

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

void Unk_710260f248::m3(const Unk_710260f248M3Arg& arg) {
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

}  // namespace ksys::snd
