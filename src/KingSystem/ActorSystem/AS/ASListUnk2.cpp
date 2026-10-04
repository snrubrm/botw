#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

const sead::SafeString* ASList::Unk2::sub_7101161CD8() {
    if (!_18)
        return &sead::SafeString::cEmptyString;
    return &_0->mUnk8;
}

}  // namespace ksys::as
