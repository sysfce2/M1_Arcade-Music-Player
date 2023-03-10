/*********************************************************/
/*    SEGA 16ch 8bit PCM                                 */
/*********************************************************/

#include "driver.h"
#include "vgmwrite.h"

struct segapcm
{
	UINT8  *ram;
	UINT16 low[16];
	const UINT8 *rom;
	UINT32 *step;
	int rate;
	int bankshift;
	int bankmask;
	unsigned short vgm_idx;		// VGM index
} spcm;

static void SEGAPCM_update(int num, INT16 **buffer, int length)
{
	int ch;
	memset(buffer[0], 0, length*2);
	memset(buffer[1], 0, length*2);

	for(ch=0; ch<16; ch++)
		if(!(spcm.ram[0x86+8*ch] & 1)) {
			UINT8 *base = spcm.ram+8*ch;
			UINT32 addr = (base[5] << 24) | (base[4] << 16) | spcm.low[ch];
			UINT16 loop = (base[0x85] << 8)|base[0x84];
			UINT8 end = base[6]+1;
			UINT8 delta = base[7];
			UINT32 step = spcm.step[delta];
			UINT8 voll = base[2];
			UINT8 volr = base[3];
			UINT8 flags = base[0x86];
			const UINT8 *rom = spcm.rom + ((flags & spcm.bankmask) << spcm.bankshift);
			int i;

			for(i=0; i<length; i++) {
				INT8 v;
				if((addr >> 24) == end) {
					if(!(flags & 2))
						addr = loop << 16;
					else {
						flags |= 1;
						break;
					}
				}
				v = rom[addr>>16] - 0x80;
				buffer[0][i] += (v*voll);
				buffer[1][i] += (v*volr);
				addr += step;
			}
			base[0x86] = flags;
			base[4] = addr >> 16;
			base[5] = addr >> 24;
			spcm.low[ch] = flags & 1 ? 0 : addr;
		}
}

int SEGAPCM_sh_start( const struct MachineSound *msound )
{
	struct SEGAPCMinterface *intf = msound->sound_interface;
	const char *name[2];
	int vol[2];
	int mask;
	int i;

	spcm.rate = intf->mode == SEGAPCM_SAMPLE15K ? 15625 : 15625*2;

	spcm.rom = (const UINT8 *)memory_region(intf->region);
	spcm.ram = malloc(0x800);
	spcm.step = malloc(sizeof(UINT32)*256);

	if(!spcm.ram || !spcm.step)
		return 1;

	for(i=0; i<256; i++)
		spcm.step[i] = i*spcm.rate*(double)(65536/256) / Machine->sample_rate;

	memset(spcm.ram, 0xff, 0x800);

	spcm.bankshift = (UINT8)(intf->bank);
	mask = intf->bank >> 16;
	if(!mask)
		mask = BANK_MASK7>>16;
	spcm.bankmask = mask;

	name[0] = "SEGAPCM L";
	name[1] = "SEGAPCM R";
	vol[0] = (MIXER_PAN_LEFT<<8)  | (intf->volume & 0xff);
	vol[1] = (MIXER_PAN_RIGHT<<8) | (intf->volume & 0xff);
	stream_init_multi(2, name, vol, Machine->sample_rate, 0, SEGAPCM_update );

	spcm.vgm_idx = vgm_open(VGMC_SEGAPCM, spcm.rate * 128);
	vgm_header_set(spcm.vgm_idx, 0x01, intf->bank);
	vgm_write_large_data(spcm.vgm_idx, 0x01, memory_region_length(intf->region), 0x00, 0x00, spcm.rom);
	
	return 0;
}

void SEGAPCM_sh_stop( void )
{
	free(spcm.ram);
	free(spcm.step);
}


WRITE_HANDLER( SegaPCM_w )
{
	spcm.ram[offset & 0x07ff] = data;
	vgm_write(spcm.vgm_idx, 0x00, offset & 0xFFFF, data);
}

READ_HANDLER( SegaPCM_r )
{
	return spcm.ram[offset & 0x07ff];
}
