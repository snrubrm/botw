#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {
class SeadController;
}

namespace uking::ui {

// Placeholder singleton (lane2 s47; instance pointer 0x710261eae8, createInstance 0x710109e224, size 0x38, vtable
// 0x7102506d38 with only D1 / D0 (0x710109e2c4 / 0x710109e2c8), disposer vtable 0x7102506d18). It drives the box
// cursor of the first screen (see the two methods) and holds some flag words.
class Unk_7102506d38 {
    SEAD_SINGLETON_DISPOSER(Unk_7102506d38)
    Unk_7102506d38() = default;

public:
    virtual ~Unk_7102506d38();

    // 0x710109e2cc (placeholder name): enables the box cursor of the first target (and disables the second)
    void sub_710109E2CC();
    // 0x710109e350 (placeholder name): `enable` for the first target; records the change in the flag word
    void sub_710109E350(bool enable);

    void sub_710109E3F8(ksys::SeadController* controller);
    void sub_710109E5C0(ksys::SeadController* controller);

    /* 0x28 */ bool _28 = true;
    /* 0x2c */ u32 _2c = 0;
    /* 0x30 */ u32 _30 = 0;
    u32 _34 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102506d38, 0x38);

}  // namespace uking::ui
