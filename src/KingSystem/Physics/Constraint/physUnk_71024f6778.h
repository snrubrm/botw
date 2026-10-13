#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f71854 allocates 0x60, installs its own two-slot
// destructor table 0x71024f6778, and constructs BoneAccessKeyEx at 0x18.
// Both destructors destroy that member; complete initialization and update establish the scalar state.
class Unk_71024f6778 {
public:
    struct Param {
        gsys::Model* model;
        const char* bone_name;
        f32 _10;
        f32 _14;
    };
    static Unk_71024f6778* sub_7100F71854(const Param& param, sead::Heap* heap);
    virtual ~Unk_71024f6778();
    // Complete F718B8 consumes Param; F71A18 independently reads the model and float settings.
    bool sub_7100F718B8(const Param& param);
    static void sub_7100F719B4(Unk_71024f6778* object);
    void sub_7100F71A10();
    void sub_7100F71A18(f32 offset, bool valid, const sead::Vector3f* direction, bool smooth,
                      bool immediate);

private:
    Unk_71024f6778() = default;
    gsys::Model* mModel = nullptr;
    s32 mBoneIndex = -1;
    u8 _14[4];
    gsys::BoneAccessKeyEx mKey;
    // Whole update 0x7100f71a18 reads, interpolates and stores this float.
    f32 _50 = 0.0f;
    f32 _54 = 1.0f;
    f32 _58 = 0.0f;
    f32 _5c = 0.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6778, 0x60);
static_assert(sizeof(Unk_71024f6778::Param) == 0x18);

}  // namespace ksys::phys
