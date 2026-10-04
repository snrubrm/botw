#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Thread/MessageTransceiverRxOnly.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Controller;
class ControllerWrapperBase;
class Heap;
}  // namespace sead

namespace uking {

// Name from the CSV (MaskController::createInstance 0x71008bc0d8, init, calc, getController,
// getControllerSafe). A sead singleton (size 0x2c8, instance pointer at 0x71025d1538) that is also a
// message handler (vtable 0x710246cf18: D1, D0, handleMessage). It owns the game's controllers
// (created in init: indices 0, 1, 2, 3, 6, 7 of an 8-entry buffer; 1 is read for the left stick,
// 3 for the right stick), a sead::MaskControllerWrapper-derived wrapper at +0x40 (vtable
// 0x710246c070, registered with controller 2), a MessageTransceiverRxOnly at +0x258 and two
// 0x10-byte objects at +0x2a8 / +0x2b8. Only what the callers use is declared so far.
class MaskController : public ksys::MessageTransceiverRxOnly::IHandler {
    SEAD_SINGLETON_DISPOSER(MaskController)
    MaskController();
    ~MaskController() override;

public:
    // Controller index. getController takes it by value and round-trips it through the stack (the
    // SEAD_ENUM volatile operator int); no names are known.
    SEAD_ENUM(ControllerIdx, _0, _1, _2, _3, _4, _5, _6, _7)

    void init(sead::Heap* heap);
    void calc();
    int handleMessage(const ksys::Message& message) override;

    // Returns nullptr when there is no instance.
    static sead::Controller* getControllerSafe(ControllerIdx idx);
    sead::Controller* getController(ControllerIdx idx);
    // 0x71008bca40: the controller wrapper at +0x40 (a sead::MaskControllerWrapper subclass, not
    // declared yet; WaitForKeyInput / KeyInputCheck test its trigger mask). Declared only.
    sead::ControllerWrapperBase* sub_71008BCA40();

private:
    u8 _28[8];
    sead::Buffer<sead::Controller*> mControllers;
    u8 _40[0x2c8 - 0x40];
};
KSYS_CHECK_SIZE_NX150(MaskController, 0x2c8);

// 0x71008bbdc8 (declaration only; called by Motorcycle::m76 when its rider is the player).
void sub_71008BBDC8();

}  // namespace uking
