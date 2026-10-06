#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEndian.h>

namespace aal {

/// The header that all the binary aal resources start with: a signature, the byte order mark and the version.
struct ResourceHeader {
    char signature[4];
    u16 byte_order_mark;
    u16 version;

    /// The signature is compared as a little endian u32 (the original reads it byte by byte).
    u32 readSignature() const {
        auto* bytes = reinterpret_cast<const u8*>(signature);
        return bytes[0] | bytes[1] << 8 | bytes[2] << 16 | static_cast<u32>(bytes[3]) << 24;
    }

    /// Whether the signature is `expected` and the resource has the byte order of the host.
    bool isValid(u32 expected) const {
        return readSignature() == expected &&
               sead::Endian::markToEndian(byte_order_mark) == sead::Endian::getHostEndian();
    }
};

}  // namespace aal
