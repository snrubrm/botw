#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

bool ASList::Unk1::sub_71011650B8(int row, int bit) const {
    if (!_30)
        return true;
    return _38[row].words[bit >> 5] & (1u << (bit & 0x1f));
}

void ASList::Unk1::sub_7101164F3C(sead::Vector3f* a1, sead::Vector3f* a2,
                                  const gsys::BoneAccessKey* key) {
    if (!key->isValid())
        return;
    if (_30) {
        if (!sub_71011650B8(key->model_unit_index, key->bone_index))
            return;
        if (_4d)
            return;
    }
    for (auto& entry : _20)
        entry.sub_7101162DE4(a1, a2, key);
}

}  // namespace ksys::as
