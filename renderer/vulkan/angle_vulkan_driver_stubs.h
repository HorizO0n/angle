
ifndef VK_DRIVER_VERSION_STUBS_H_
#define VK_DRIVER_VERSION_STUBS_H_

#include <cstdint>

namespace angle {

// Stub for drivers Vulkan
unsigned int ParseArmVulkanDriverVersion(unsigned int version);
unsigned int ParseQualcommVulkanDriverVersion(unsigned int version);
unsigned int ParseNvidiaVulkanDriverVersion(unsigned int version);
unsigned int ParseSamsungVulkanDriverVersion(unsigned int version);
unsigned int ParseAMDVulkanDriverVersion(unsigned int version);

} // namespace angle

#endif // VK_DRIVER_VERSION_STUBS_H_
