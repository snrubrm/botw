#include "Game/UI/uiUnkTiny.h"

// The "{ ; }" destructors keep the original's vtable store (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; },
// commit 96101229; the original D1 is `str vptr; ret`).
namespace uking::ui {

// 0x7100932f6c
Unk_7102474b38::~Unk_7102474b38() = default;

// 0x71009332f0
Unk_7102474b78::Unk_7102474b78() = default;

// 0x7100933314
Unk_7102474b78::~Unk_7102474b78() = default;

// 0x71009336a4
Unk_7102474ba8::~Unk_7102474ba8() = default;

// 0x7100934b8c
Unk_7102474be8::~Unk_7102474be8() = default;

// 0x7100935f90
Unk_7102474c08::~Unk_7102474c08() = default;

// 0x7100936990
Unk_7102474c28::~Unk_7102474c28() = default;

// 0x7100936b10
Unk_7102474c48::~Unk_7102474c48() = default;

// 0x7100947b7c
Unk_7102475158::~Unk_7102475158() = default;

// 0x7100949ce0
Unk_7102475278::~Unk_7102475278() = default;

// 0x710094d8c4
Unk_7102475348::~Unk_7102475348() = default;

// 0x710095023c
Unk_7102475368::~Unk_7102475368() = default;

// 0x710096a890
Unk_7102475388::~Unk_7102475388() = default;

// 0x710095b124
Unk_71024753a8::~Unk_71024753a8() = default;

// 0x710095a3e4
Unk_7102476a80::~Unk_7102476a80() = default;

// 0x710096a89c
Unk_7102476b20::~Unk_7102476b20() = default;

// 0x7100968038
Unk_7102476b40::~Unk_7102476b40() = default;

// 0x7100968034
Unk_7102476b60::~Unk_7102476b60() = default;

// 0x71009858fc
Unk_7102476d68::~Unk_7102476d68() = default;

// 0x7100987fb4
Unk_7102477468::~Unk_7102477468() = default;

// 0x71009880a4
Unk_7102477488::~Unk_7102477488() = default;

// 0x7100988ee8
Unk_71024774c8::~Unk_71024774c8() = default;

// 0x7100989a78
Unk_7102477508::~Unk_7102477508() = default;

// 0x71009a4d24
Unk_7102479bb0::~Unk_7102479bb0() = default;

// 0x71009a7fa0
Unk_7102479f90::~Unk_7102479f90() = default;

// 0x71009a8be4
Unk_7102479fb0::~Unk_7102479fb0() = default;

// 0x71009b14f0
Unk_710247aa30::~Unk_710247aa30() = default;

// 0x71009b2054
Unk_710247adc8::~Unk_710247adc8() = default;

// 0x71009b2ee0
Unk_710247ae08::~Unk_710247ae08() = default;

// 0x71009b2ee8
Unk_710247ae28::~Unk_710247ae28() = default;

// 0x71009c5098
Unk_710247d8d8::~Unk_710247d8d8() = default;

// 0x71009c66e4
Unk_710247dc50::~Unk_710247dc50() = default;

// 0x71009c6870
Unk_710247dc70::~Unk_710247dc70() = default;

// 0x71009dff74
Unk_71024810d8::~Unk_71024810d8() = default;

// 0x71009e7e00
Unk_71024810f8::~Unk_71024810f8() = default;

// 0x71009dff7c
Unk_7102481118::~Unk_7102481118() = default;

// 0x71009ec6c8
Unk_7102481e50::~Unk_7102481e50() = default;

// 0x7100a6cb6c
Unk_710249c3b0::~Unk_710249c3b0() = default;

// 0x7100a6cbb8
Unk_710249c3d0::~Unk_710249c3d0() = default;

// 0x7100a6cc44
Unk_710249c3f0::~Unk_710249c3f0() = default;

// 0x7100a6d2c8
Unk_710249c410::~Unk_710249c410() = default;

// 0x71009ec6c8
Unk_7102516880::~Unk_7102516880() = default;

// 0x7100933140
Unk_7102474b58::Unk_7102474b58(void* owner) : _8(owner) {}

// 0x7100933184
Unk_7102474b58::~Unk_7102474b58() { ; }

// 0x7100959a84
Unk_7102476a40::~Unk_7102476a40() { ; }

// 0x7100959cfc
Unk_7102476a60::~Unk_7102476a60() { ; }

// 0x7100968020
Unk_7102476b00::~Unk_7102476b00() { ; }

// 0x7100988490
Unk_71024774a8::~Unk_71024774a8() { ; }

// 0x71009dfd4c
Unk_71024810b8::~Unk_71024810b8() { ; }

// NON_MATCHING: the original stores `_8` (the base class member) right after loading the vtable address, ours
// schedules it after the 64-bit constant of `_10`
// 0x7100a82fbc
Unk_710249d300::Unk_710249d300() = default;

// 0x7100a8331c
Unk_710249d300::~Unk_710249d300() { ; }

// 0x7100937f5c
Unk_7102474df8::~Unk_7102474df8() {
    _10.freeBuffer();
}

// 0x7100933938
Unk_7102474bc8::~Unk_7102474bc8() {
    _130.freeBuffer();
    _140.freeBuffer();
}

// 0x7100937d9c
Unk_7102474dd0::~Unk_7102474dd0() = default;

// 0x71010a7bcc
Unk_7102509148::Unk_7102509148() = default;

// 0x71010a7bf8
Unk_7102509148::~Unk_7102509148() = default;

}  // namespace uking::ui
