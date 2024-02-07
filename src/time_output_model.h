#ifndef TIME_OUTPUT_MODEL_H_
#define TIME_OUTPUT_MODEL_H_

#include <iostream>

namespace TimeOutputModel
{
	static const std::int8_t
		Year = 0b00000001,	// 0x01
		Month = 0b00000010,	// 0x02
		Day = 0b00000100,	// 0x04
		Hour = 0b00001000,	// 0x08
		Minute = 0b00010000,	// 0x10
		Second = 0b00100000,	// 0x20
		Weekday = 0b01000000,	// 0x40
		Date = Year | Month | Day,		// 0x07
		Time = Hour | Minute | Second,	// 0x38
		All = Date | Time | Weekday;	// 0x7F
};


#endif // !TIME_OUTPUT_MODEL_H_
