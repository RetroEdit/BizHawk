#include <iostream>
#include <cstdint>
#include <iomanip>
#include <string>

using namespace std;

namespace GBHawk
{
	class LR35902;
	class Timer;
	class PPU;
	class GBAudio;
	class SerialPort;
	class Mapper;
	
	class MemoryManager
	{
	public:
				
		MemoryManager()
		{

		};

		uint8_t ReadMemory(uint32_t addr);
		uint8_t PeekMemory(uint32_t addr);
		void WriteMemory(uint32_t addr, uint8_t value);
		uint8_t Read_Registers(uint32_t addr);
		void Write_Registers(uint32_t addr, uint8_t value);

		#pragma region Declarations

		PPU* ppu_pntr = nullptr;
		GBAudio* psg_pntr = nullptr;
		LR35902* cpu_pntr = nullptr;
		Timer* timer_pntr = nullptr;
		SerialPort* serialport_pntr = nullptr;
		Mapper* mapper_pntr = nullptr;
		uint8_t* ROM = nullptr;
		uint8_t* Cart_RAM = nullptr;
		uint8_t* bios_rom = nullptr;

		// initialized by core loading, not savestated
		uint32_t ROM_Length;
		uint32_t ROM_Mapper;
		uint32_t Cart_RAM_Length;

		// State
		bool lagged;
		bool is_GBC;
		bool GBC_compat;
		bool speed_switch, double_speed;
		bool in_vblank;
		bool in_vblank_old;
		bool vblank_rise;
		bool GB_bios_register;
		bool HDMA_transfer;
		bool Use_MT;
		bool has_bat;
		
		uint8_t REG_FFFF, REG_FF0F, REG_FF0F_OLD;
		uint8_t _scanlineCallbackLine;
		uint8_t input_register;
		uint32_t RAM_Bank;
		uint32_t VRAM_Bank;

		uint8_t IR_reg, IR_mask, IR_signal, IR_receive, IR_self;
		uint32_t IR_write;
		uint32_t addr_access;
		uint32_t Acc_X_state;
		uint32_t Acc_Y_state;

		// several undocumented GBC Registers
		uint8_t undoc_6C, undoc_72, undoc_73, undoc_74, undoc_75, undoc_76, undoc_77;
		uint8_t controller_state;

		uint8_t ZP_RAM[0x80] = {};
		uint8_t RAM[0x8000] = {};
		uint8_t VRAM[0x4000] = {};
		uint8_t OAM[0xA0] = {};
		uint8_t header[0x50] = {};
		uint32_t vidbuffer[160 * 144] = {};
		uint32_t frame_buffer[160 * 144] = {};
		uint32_t color_palette[4] = { 0xFFFFFFFF , 0xFFAAAAAA, 0xFF555555, 0xFF000000 };

		const uint8_t GBA_override[13] = { 0xFF, 0x00, 0xCD, 0x03, 0x35, 0xAA, 0x31, 0x90, 0x94, 0x00, 0x00, 0x00, 0x00 };

		#pragma endregion

		#pragma region Functions

		// NOTE: only called when checks pass that the files are correct
		void Load_BIOS(uint8_t* bios, bool GBC_console, bool GBC_as_GBA)
		{
			if (GBC_console)
			{
				bios_rom = new uint8_t[2304];
				memcpy(bios_rom, bios, 2304);
				is_GBC = true;

				// set up IR variables if it's GBC
				IR_mask = 0; IR_reg = 0x3E; IR_receive = 2; IR_self = 2; IR_signal = 2;

				if (GBC_as_GBA) 
				{
					for (int i = 0; i < 13; i++)
					{
						bios_rom[i + 0xF3] = (uint8_t)((GBA_override[i] + bios_rom[i + 0xF3]) & 0xFF);
					}
					IR_mask = 2;
				}
			}
			else
			{
				bios_rom = new uint8_t[256];
				memcpy(bios_rom, bios, 256);
			}
		}

		void Load_ROM(uint8_t* ext_rom_1, uint32_t ext_rom_size_1)
		{
			ROM = new uint8_t[ext_rom_size_1];

			memcpy(ROM, ext_rom_1, ext_rom_size_1);

			ROM_Length = ext_rom_size_1;

			std::memcpy(header, ext_rom_1 + 0x100, 0x50);
		}

		// Switch Speed (GBC only)
		uint32_t SpeedFunc(uint32_t temp)
		{
			if (is_GBC)
			{
				if (speed_switch)
				{
					speed_switch = false;
					uint32_t ret = double_speed ? 70224 * 2 : 70224 * 2; // actual time needs checking
					double_speed = !double_speed;
					return ret;
				}

				// if we are not switching speed, return 0
				return 0;
			}

			// if we are in GB mode, return 0 indicating not switching speed
			return 0;
		}

		void Register_Reset()
		{
			input_register = 0xCF; // not reading any input

			REG_FFFF = 0;
			REG_FF0F = 0xE0;
			REG_FF0F_OLD = 0xE0;

			//undocumented registers
			undoc_6C = 0xFE;
			undoc_72 = 0;
			undoc_73 = 0;
			undoc_74 = 0;
			undoc_75 = 0x8F;
			undoc_76 = 0;
			undoc_77 = 0;
		}

		#pragma endregion

		#pragma region State Save / Load

		uint8_t* SaveState(uint8_t* saver)
		{
			*saver = (uint8_t)(lagged ? 1 : 0); saver++;

			std::memcpy(saver, &RAM, 0x10000); saver += 0x10000;
			//std::memcpy(saver, &cart_ram, 0x8000); saver += 0x8000;

			return saver;
		}

		uint8_t* LoadState(uint8_t* loader)
		{
			lagged = *loader == 1; loader++;

			std::memcpy(&RAM, loader, 0x10000); loader += 0x10000;
			//std::memcpy(&cart_ram, loader, 0x8000); loader += 0x8000;

			return loader;
		}

		#pragma endregion
	};
}