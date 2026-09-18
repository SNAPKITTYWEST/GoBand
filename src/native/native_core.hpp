#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace winzip::native {

struct ProcessResult {
    std::uint32_t process_id{};
    std::int32_t exit_code{};
    std::string stdout_text;
    std::string stderr_text;
};

struct SectionInfo {
    std::string name;
    std::uint32_t virtual_address{};
    std::uint32_t virtual_size{};
    std::uint32_t raw_address{};
    std::uint32_t raw_size{};
    std::uint32_t characteristics{};
};

struct PEInfo {
    std::uint16_t machine{};
    std::uint16_t optional_magic{};
    std::uint32_t entry_point_rva{};
    std::vector<SectionInfo> sections;
};

ProcessResult RunProcess(const std::wstring& executable,
                         const std::wstring& arguments);

bool ReadFileBytes(const std::wstring& path,
                   std::vector<std::uint8_t>& output);

bool InspectPE(const std::wstring& path, PEInfo& output);

}
