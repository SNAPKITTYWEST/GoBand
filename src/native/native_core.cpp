#include "native_core.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <fstream>

namespace winzip::native {

ProcessResult RunProcess(const std::wstring& executable,
                         const std::wstring& arguments) {
    ProcessResult result{};

    std::wstring command = L"\"" + executable + L"\" " + arguments;
    std::vector<wchar_t> mutable_command(command.begin(), command.end());
    mutable_command.push_back(L'\0');

    STARTUPINFOW si{};
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi{};

    if (!CreateProcessW(
            nullptr,
            mutable_command.data(),
            nullptr,
            nullptr,
            FALSE,
            CREATE_NO_WINDOW,
            nullptr,
            nullptr,
            &si,
            &pi)) {
        return result;
    }

    result.process_id = pi.dwProcessId;

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exit_code = 0;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    result.exit_code = static_cast<std::int32_t>(exit_code);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return result;
}

bool ReadFileBytes(const std::wstring& path,
                   std::vector<std::uint8_t>& output) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return false;

    file.seekg(0, std::ios::end);
    const auto size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size < 0)
        return false;

    output.resize(static_cast<std::size_t>(size));
    file.read(reinterpret_cast<char*>(output.data()), size);

    return file.good() || file.eof();
}

bool InspectPE(const std::wstring& path, PEInfo& output) {
    std::vector<std::uint8_t> bytes;
    if (!ReadFileBytes(path, bytes))
        return false;

    if (bytes.size() < sizeof(IMAGE_DOS_HEADER))
        return false;

    auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());

    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return false;

    if (dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(DWORD) +
        sizeof(IMAGE_FILE_HEADER) > bytes.size())
        return false;

    auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);

    if (nt->Signature != IMAGE_NT_SIGNATURE)
        return false;

    output.machine = nt->FileHeader.Machine;
    output.optional_magic = nt->OptionalHeader.Magic;
    output.entry_point_rva = nt->OptionalHeader.AddressOfEntryPoint;

    auto* section =
        IMAGE_FIRST_SECTION(nt);

    for (unsigned i = 0;
         i < nt->FileHeader.NumberOfSections;
         ++i, ++section) {
        SectionInfo info{};

        char name[9]{};
        std::memcpy(name, section->Name, 8);
        info.name = name;
        info.virtual_address = section->VirtualAddress;
        info.virtual_size = section->Misc.VirtualSize;
        info.raw_address = section->PointerToRawData;
        info.raw_size = section->SizeOfRawData;
        info.characteristics = section->Characteristics;

        output.sections.push_back(info);
    }

    return true;
}

}
