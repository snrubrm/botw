#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkDisplaySerializeIStream;
class hkDisplaySerializeOStream;
class hkDebugDisplayHandler;
class hkProcessHandler;

// Secondary base of hkpWorldViewerBase at +0x10 (vtable 0x7102544490 + 0x70, slots 14..22).
class hkProcess {
public:
    virtual ~hkProcess() {}
    virtual int getProcessTag() = 0;
    // 0x7101676468: returns -1.
    virtual int sub_7101676468();
    virtual void getConsumableCommands(hkUint8*& commands, int& numCommands);
    virtual void consumeCommand(hkUint8 command);
    // 0x7101676480: m_outStream && m_outStream->isOk().
    virtual bool isOk();
    virtual void step(hkReal frameTimeInMs);
    // 0x71016764a8: empty.
    virtual void sub_71016764A8();

protected:
    hkBool m_selectable;
    hkDisplaySerializeIStream* m_inStream;
    hkDisplaySerializeOStream* m_outStream;
    hkDebugDisplayHandler* m_displayHandler;
    hkProcessHandler* m_processHandler;
};
static_assert(sizeof(hkProcess) == 0x30);
