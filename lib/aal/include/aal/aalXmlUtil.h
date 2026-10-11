#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
class XmlDocument;
class XmlElement;
}

namespace aal {
class XmlUtil {
public:
    static sead::XmlElement* addChild(sead::XmlElement* element, const sead::SafeString& name,
                                     sead::Heap* heap);
    static sead::XmlElement* addString(sead::XmlElement* element, const sead::SafeString& name,
                                      const sead::SafeString& value, sead::Heap* heap);
    static void addF32(sead::XmlElement* element, const sead::SafeString& name, f32 value,
                       sead::Heap* heap);
    static void addBool(sead::XmlElement* element, const sead::SafeString& name, bool value,
                        sead::Heap* heap);
    static sead::XmlDocument* createTextDocument(void* data, u32 size, sead::Heap* heap);
    static sead::SafeString getElementContentString(sead::XmlElement* element,
                                                  const sead::SafeString& path);
};
}  // namespace aal
