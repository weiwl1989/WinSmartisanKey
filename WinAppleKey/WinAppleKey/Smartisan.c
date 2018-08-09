#include "driver.h"

static BOOLEAN FakeFnActive = 0;

void ProcessSmartisanBuffer(BYTE* buf, ULONG size)
{
	DebugPrintBuffer("ProcessSmartisanBuffer(): <= ", buf, size);
	BYTE* pModifier = &buf[0];
	BYTE* pKey1 = &buf[1];
	BYTE* pSpecialKey = &buf[2];

	// F1 02 21 02
	// F2 02 23 00
	// F3 02 24 00
	// F4 02 25 00
	// F5 02 26 00
	// F6 02 27 00
	// F7 02 28 00
	// F8 02 29 00
	// F9 02 23 02
	// F10 02 2A 00
	// F11 02 70 00
	// F12 02 6F 00
	// F13 02 2B 00
	// F14 02 B6 00
	// F15 02 CD 00
	// F16 02 B5 00
	// F17 02 E2 00
	// F18 02 EA 00
	// F19 02 E9 00
	// F20 02 2C 00
	//if (*pKey1 == 0x23)
	//{
	//	*pKey1 = 0x21;
	//	*pSpecialKey = 0x02;
	//}
	switch (*pKey1)
	{
		case 0x23: {
			//F2 打开资源管理器
			if (*pSpecialKey == 0x00)
			{
				*pKey1 = 0x94;
				*pSpecialKey = 0x01;
			}
			////F9
			//else if (*pSpecialKey == 0x02)
			//{
			//	*pKey1 = 0x37;
			//	*pSpecialKey = 0x02;
			//}
			break;
		}
		//F3 打开邮箱
		case 0x24:
			*pKey1 = 0x8A;
			*pSpecialKey = 0x01;
			break;
		//F4 打开计算器
		case 0x25:
		{
			*pKey1 = 0x92;
			*pSpecialKey = 0x01;
			break;
		}
		//F5 刷新
		case 0x26:
			*pKey1 = 0x27;
			*pSpecialKey = 0x02;
			break;
		//F6 前进
		case 0x27:
			*pKey1 = 0x25;
			*pSpecialKey = 0x02;
			break;
		//F7 后退
		case 0x28:
			*pKey1 = 0x24;
			*pSpecialKey = 0x02;
			break;
		//F8 在浏览器中停止加载
		case 0x29:
			*pKey1 = 0x26;
			*pSpecialKey = 0x02;
			break;
		//F10 打开浏览器书签
		case 0x2A:
			*pKey1 = 0x2A;
			*pSpecialKey = 0x02;
			break;
		////F11 亮度+1
		//case 0x70:
		//	*pKey1 = 0x25;
		//	*pSpecialKey = 0x02;
		//	break;
		////F12 亮度-1
		//case 0x6F:
		//	*pKey1 = 0x26;
		//	*pSpecialKey = 0x02;
		//	break;
		//F13 打开音乐播放器
		case 0x2B:
			*pKey1 = 0x83;
			*pSpecialKey = 0x01;
			break;
		////F14 上一曲
		//case 0xB6:
		//	*pKey1 = 0x2F;
		//	*pSpecialKey = 0x02;
		//	break;
		////F15 暂停
		//case 0xCD:
		//	*pKey1 = 0x30;
		//	*pSpecialKey = 0x02;
		//	break;
		////F16  下一曲
		//case 0xB5:
		//	*pKey1 = 0x31;
		//	*pSpecialKey = 0x02;
		//	break;
		////F17 静音
		//case 0xE2:
		//	*pKey1 = 0x32;
		//	*pSpecialKey = 0x02;
		//	break;
		////F18 音量-
		//case 0xEA:
		//	*pKey1 = 0x33;
		//	*pSpecialKey = 0x02;
		//	break;
		////F19 音量+
		//case 0xE9:
		//	*pKey1 = 0x34;
		//	*pSpecialKey = 0x02;
		//	break;
		//F20 打开音量控制
		case 0x2C:
			*pKey1 = 0xE0;
			*pSpecialKey = 0x00;
			break;
		default:
		break;
	}

	DebugPrintBuffer("ProcessSmartisanBuffer(): => ", buf, size);
}