#include "KingSystem/Terrain/teraResourceNode.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

Unk_710110d278* Unk_7101108460::getB() const {
    return mB;
}

Unk_710110cfd0* Unk_7101108460::getA() {
    return mA;
}

const Unk_710110cfd0* Unk_7101108460::getA() const {
    return mA;
}

u16 Unk_7101108460::sub_7101108614() const {
    return mB->_8->id;
}

bool Unk_7101108460::sub_7101108624() const {
    return mB->_a0 > sead::Mathf::epsilon();
}

u32 sub_7101108AE8(sead::Vector2f* out_pos, s32* out_index, const sead::Vector2f& pos,
                   const Unk_7101108AE8Flags& flags, const Unk_71010FEDBC& areas, u32 max_level) {
    if ((flags._0 & 3) != 3)
        return 0;

    const u32 count = flags._2 < max_level ? flags._2 : max_level;
    out_pos->x = 0.0f;
    out_pos->y = 0.0f;
    *out_index = 0;
    *out_index = areas.sub_71010FEDBC(pos, count, 0.0f);
    while (*out_index != -1) {
        Unk_71010FEDBC::Result result;
        while (!areas.sub_71010FE920(&result, pos, *out_index) || !result._16) {
            if (*out_index == 0)
                return 0;
            --*out_index;
        }

        out_pos->x = result.pos.x;
        out_pos->y = result.pos.y;
        if (result.pos.x >= -1.0f && result.pos.x < 2.0f && result.pos.y >= -1.0f &&
            result.pos.y < 2.0f) {
            return result._10 == 0 ? 2 : 1;
        }

        if (*out_index == 0)
            return 0;
        *out_index = areas.sub_71010FEDBC(pos, *out_index - 1, 0.0f);
    }
    return 0;
}

}  // namespace ksys::tera
