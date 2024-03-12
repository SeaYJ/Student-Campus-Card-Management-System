#ifndef TIME_IO_MODEL_H_
#define TIME_IO_MODEL_H_

#include <iostream>
#include <stdexcept>
#include <ctime>

class TimeInputModel {
public:
	/// <summary>
	/// 获取特定时间的 std::time_t 值。
	/// </summary>
	/// <param name="year">年 [1900, 9999]</param>
	/// <param name="month">月 [1, 12]</param>
	/// <param name="day">日 [1, 31]</param>
	/// <param name="hour">时 [0, 23]</param>
	/// <param name="minute">分 [0, 59]</param>
	/// <param name="second">秒 [0, 59]</param>
	/// <returns>对应时间的 time_t 值</returns>
	static std::time_t InputFormatTime(
		const std::int32_t year = 1900,
		const std::int32_t month = 1,
		const std::int32_t day = 1,
		const std::int32_t hour = 0,
		const std::int32_t minute = 0,
		const std::int32_t second = 0
	);
private:
	static int GetMaxDaysInMonth(int year, int month);
};

class TimeOutputModel
{
public:
	static const std::int8_t
		Year = 0b00000001,				// 0x01
		Month = 0b00000010,				// 0x02
		Day = 0b00000100,				// 0x04
		Hour = 0b00001000,				// 0x08
		Minute = 0b00010000,			// 0x10
		Second = 0b00100000,			// 0x20
		Weekday = 0b01000000,			// 0x40
		Date = Year | Month | Day,		// 0x07
		Time = Hour | Minute | Second,	// 0x38
		All = Date | Time | Weekday;	// 0x7F

	/// <summary>
	/// 格式化日期字符串
	/// </summary>
	/// <param name="time_info">包含日期信息的 tm 结构体</param>
	/// <param name="ops">可选字段的可选参数组合</param>
	/// <returns>包含特定可选字段的日期字符串</returns>
	static std::string OutputFormatTime(const tm* time_info, const std::int8_t ops);
};

#endif // !TIME_IO_MODEL_H_
