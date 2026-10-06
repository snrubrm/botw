#pragma once

#include <basis/seadTypes.h>
#include "aal/aalDeviceType.h"

namespace sead {
class DrawContext;
class Heap;
class TextWriter;
}  // namespace sead

namespace aal {

/// Measures the final output of a device. TODO: incomplete.
class FinalOutputMeasure {
public:
    struct InitializeArg {
        f32 _0;
    };

    explicit FinalOutputMeasure(DeviceType device);
    virtual ~FinalOutputMeasure();

    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void finalize();
    void calc();
    void drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const;

private:
    u8 _8[0x218 - 8];
};
static_assert(sizeof(FinalOutputMeasure) == 0x218, "aal::FinalOutputMeasure size mismatch");

}  // namespace aal
