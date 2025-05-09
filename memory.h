#include "memflow_win32.h"
#include <cstring>
#include <stdio.h>
#include <mutex>
#include <string>
#include <iostream>
#include <cstdint>
#include <optional>
#include <tuple>
#include <functional>
#include "offsets.h"
#include <algorithm>

#define INRANGE(x,a,b)		(x >= a && x <= b) 
#define getBits( x )		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte( x )		(getBits(x[0]) << 4 | getBits(x[1]))

typedef uint8_t* PBYTE;
typedef uint8_t BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef WORD *PWORD;

static CloneablePhysicalMemoryObj *conn = 0;
static Kernel *kernel = 0;

inline bool isMatch(const PBYTE addr, const PBYTE pat, const PBYTE msk)
{
	size_t n = 0;
	while (addr[n] == pat[n] || msk[n] == (BYTE)'?')
	{
		if (!msk[++n])
		{
			return true;
		}
	}
	return false;
}

size_t findPattern(const PBYTE rangeStart, size_t len, const char* pattern);

typedef struct Process
{
	Win32Process* hProcess = 0;
	uint64_t baseaddr = 0;
}Process;

enum class process_status : BYTE
{
	NOT_FOUND,
	FOUND_NO_ACCESS,
	FOUND_READY
};

class Memory
{
private:
	Process proc;
	VirtualMemoryObj* mem;
	process_status status = process_status::NOT_FOUND;
	std::mutex m;
public:
	~Memory() { if (mem) virt_free(mem); if (proc.hProcess) process_free(proc.hProcess); }

	uint64_t get_proc_baseaddr();

	process_status get_proc_status();

	void check_proc();

	void open_proc(const char* name);

	void close_proc();

	// 定义一个模板函数Read，用于从指定地址读取指定类型的值，并将其赋给out参数
	template<typename T>
	bool ReadData(uint64_t address, T& out); 

	// 读取单浮点(32位整数)
	template<typename T>
	bool ReadFloat(uint64_t address, T& out);
	
	template<typename T>
	bool Read(uint64_t address, T& out);

	template<typename T>
	bool ReadArray(uint64_t address, T out[], size_t len);

	template<typename T>
	bool Write(uint64_t address, const T& value);

	template<typename T>
	bool WriteArray(uint64_t address, const T value[], size_t len);

	uint64_t ScanPointer(uint64_t ptr_address, const uint32_t offsets[], int level);

	uint64_t GetModuleAddress(const char* proc_name, const char* module_name); //get client/engine .dll from csgo
};

template<typename T>
inline bool Memory::Read(uint64_t address, T& out)
{
	std::lock_guard<std::mutex> l(m);
	return mem && virt_read_raw_into(mem, address, (uint8_t*)&out, sizeof(T)) == 0;
}

// 定义一个模板函数Read，用于从指定地址读取指定类型的值，并将其赋给out参数
template<typename T>
inline bool Memory::ReadData(uint64_t address, T& out)
{
	// 如果有虚拟内存对象，就调用virt_read_raw_into函数从地址读取数据，并返回是否成功
	return mem && (out = virt_read_u64(mem, address)) == 0; // correct 
}

// 定义一个模板函数Read，用于从指定地址读取浮点的值，并将其赋给out参数
template<typename T>
inline bool Memory::ReadFloat(uint64_t address, T& out)
{
	// 如果有虚拟内存对象，就调用virt_read_raw_into函数从地址读取数据，并返回是否成功
	return mem && (out = virt_read_u32(mem, address)) == 0; // correct 
}

template<typename T>
inline bool Memory::ReadArray(uint64_t address, T out[], size_t len)
{
	std::lock_guard<std::mutex> l(m);
	return mem && virt_read_raw_into(mem, address, (uint8_t*)out, sizeof(T) * len) == 0;
}

template<typename T>
inline bool Memory::Write(uint64_t address, const T& value)
{
	std::lock_guard<std::mutex> l(m);
	return mem && virt_write_raw(mem, address, (uint8_t*)&value, sizeof(T)) == 0;
}

template<typename T>
inline bool Memory::WriteArray(uint64_t address, const T value[], size_t len)
{
	std::lock_guard<std::mutex> l(m);
	return mem && virt_write_raw(mem, address, (uint8_t*)value, sizeof(T) * len) == 0;
}
