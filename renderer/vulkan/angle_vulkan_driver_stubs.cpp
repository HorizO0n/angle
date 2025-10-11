// vk_driver_version_stubs.cpp
// Stubs temporários para funções ausentes de análise de versão de driver Vulkan.
// Evita erros de símbolo indefinido na hora do link.
// Substituir por implementações reais quando disponíveis.

#include <cstdint>

namespace angle {

const char *ParseArmVulkanDriverVersion(unsigned int)
{
    return "ARM Vulkan driver (stub)";
}

const char *ParseQualcommVulkanDriverVersion(unsigned int)
{
    return "Qualcomm Vulkan driver (stub)";
}

const char *ParseNvidiaVulkanDriverVersion(unsigned int)
{
    return "NVIDIA Vulkan driver (stub)";
}

const char *ParseSamsungVulkanDriverVersion(unsigned int)
{
    return "Samsung Vulkan driver (stub)";
}

const char *ParseAMDVulkanDriverVersion(unsigned int)
{
    return "AMD Vulkan driver (stub)";
}

}  // namespace angle
