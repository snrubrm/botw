#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Thread/MessageBroker.h"

// The debug subsystem that prints the loading status (CSV DebugSubsys1; vtable 0x710250b7c0,
// singleton instance storage 0x261f9b8). uking::initBeforeStageGen and GameScene::startLoadingScreen
// drive it.
// TODO: incomplete (nowLoading, which builds the print request, and the members its request uses are
// not modelled).
class DebugSubsys1 : public ksys::Unk_71025d0530 {
    SEAD_RTTI_OVERRIDE(DebugSubsys1, ksys::Unk_71025d0530)
public:
    ~DebugSubsys1() override;

    // 0x71010bcc08: clears the request state.
    void initBeforeStageGen();
    // 0x71010bcc18 (declared only): prints "NowLoading <name>".
    void nowLoading();
    // 0x71010bcd4c: sets the "print the loading status" flag.
    void x(bool on);

private:
    u8 _8[0x18];   // 0x08
    bool _20;      // 0x20
    u8 _21[0xe7];  // 0x21
    // Reset by initBeforeStageGen.
    u64 _108;  // 0x108
    u64 _110;  // 0x110
    u64 _118;  // 0x118
    u64 _120;  // 0x120
    u32 _128;  // 0x128
};
