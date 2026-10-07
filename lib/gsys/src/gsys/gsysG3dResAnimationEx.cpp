#include <gsys/gsysG3dResAnimationEx.h>
#include <codec/seadHashCRC32.h>

namespace gsys {

G3dResAnimationEx::G3dResAnimationEx() : nameHash(0) {}

void G3dResAnimationEx::updateNameHash(const sead::SafeString& string) {
    name = string.cstr();
    nameHash = sead::HashCRC32::calcStringHash(string.cstr());
}

}  // namespace gsys
