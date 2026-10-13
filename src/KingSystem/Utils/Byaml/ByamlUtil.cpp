#include "KingSystem/Utils/Byaml/Byaml.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace al {

bool tryGetByamlS32(s32* value, const ByamlIter& iter, const char* key) {
    return iter.tryGetIntByKey(value, key);
}

bool tryGetByamlU32(u32* value, const ByamlIter& iter, const char* key) {
    s32 v{};
    bool ret = iter.tryGetIntByKey(&v, key);
    if (ret)
        *value = v;
    return ret;
}

bool tryGetByamlF32(f32* value, const ByamlIter& iter, const char* key) {
    f32 v{};
    bool ret = iter.tryGetFloatByKey(&v, key);
    if (!ret)
        return false;
    *value = v;
    return true;
}

bool tryGetByamlV3f(sead::Vector3f* value, const ByamlIter& iter, const char* key) {
    f32 x, y, z;
    ByamlIter vec_iter;
    if (!iter.tryGetIterByKey(&vec_iter, key))
        return false;

    x = 0;
    bool ok = vec_iter.tryGetFloatByKey(&x, "X");
    y = 0;
    ok |= vec_iter.tryGetFloatByKey(&y, "Y");
    z = 0;
    ok |= vec_iter.tryGetFloatByKey(&z, "Z");

    *value = {x, y, z};
    return ok;
}

}  // namespace al

Unk_71024bd4f0::~Unk_71024bd4f0() = default;

Unk_71024bf6f8::~Unk_71024bf6f8() = default;

Unk_71024bfe10::~Unk_71024bfe10() = default;

Unk_71024c0140::~Unk_71024c0140() = default;

Unk_71024c0220::~Unk_71024c0220() = default;
