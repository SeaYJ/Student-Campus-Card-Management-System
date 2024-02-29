#ifndef TIME_OUTPUT_MODEL_H_
#define TIME_OUTPUT_MODEL_H_

#include <iostream>

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
	static std::string FormatTime(const tm* time_info, const std::int8_t ops)
	{
		std::string buffer = "";                                                // 返回值缓冲区
		char part_buffer[16];                                                   // 可选时间字段缓冲区

		bool include_year = false;                                              // 是否包含“年”的字段
		bool include_month = false;                                             // 是否包含“月”的字段
		bool include_day = false;                                               // 是否包含“日”的字段
		bool include_hour = false;                                              // 是否包含“时”的字段
		bool include_minute = false;                                            // 是否包含“分”的字段
		bool include_second = false;                                            // 是否包含“秒”的字段
		bool include_weekday = false;                                           // 是否包含“周”的字段

		if (ops & TimeOutputModel::Year)                                        // 添加“年”字段
		{
			include_year = true;                                                // 修改标识符，表示该字段被包含在日期字串内

			strftime(
				part_buffer,
				sizeof(part_buffer),
				"%Y",
				time_info
			);                                                                  // 获取年
			buffer.append(part_buffer);                                         // 添加年字段
		}

		if (ops & TimeOutputModel::Month)                                       // 添加“月”字段
		{
			include_month = true;                                               // 修改标识符，表示该字段被包含在日期字串内

			bool include_date_separator = include_year;                          // 计算是否需要添加“日期内分隔符”

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_date_separator ? "/%m" : "%m"),
				time_info
			);                                                                  // 获取月
			buffer.append(part_buffer);                                         // 添加月字段
		}

		if (ops & TimeOutputModel::Day)                                         // 添加“日”字段
		{
			include_day = true;                                                 // 修改标识符，表示该字段被包含在日期字串内

			bool include_date_separator =
				include_year ||
				include_month;                                                  // 计算是否需要添加“日期内分隔符”

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_date_separator ? "/%d" : "%d"),
				time_info
			);                                                                  // 获取日
			buffer.append(part_buffer);                                         // 添加日字段
		}

		if (ops & TimeOutputModel::Hour)                                        // 添加“时”字段
		{
			include_hour = true;                                                // 修改标识符，表示该字段被包含在日期字串内

			bool include_group_separator =
				include_year ||
				include_month ||
				include_day;                                                    // 计算是否需要添加“组间分隔符”
			// 所谓“组间分隔符”即为Date、Time、Weekday三者间的分隔符

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_group_separator ? " %H" : "%H"),
				time_info
			);                                                                  // 获取时
			buffer.append(part_buffer);                                         // 添加时字段
		}

		if (ops & TimeOutputModel::Minute)                                      // 添加“分”字段
		{
			include_minute = true;                                              // 修改标识符，表示该字段被包含在日期字串内

			bool include_time_separator =
				include_hour;                                                   // 计算是否需要添加“时间内分隔符”
			bool include_group_separator =
				include_year ||
				include_month ||
				include_day;                                                    // 计算是否需要添加“组间分隔符”

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_time_separator ? ":%M" : (include_group_separator ? " %M" : "%M")),
				time_info
			);                                                                  // 获取分
			buffer.append(part_buffer);                                         // 添加分字段
		}

		if (ops & TimeOutputModel::Second)                                      // 添加“秒”字段
		{
			include_second = true;                                              // 修改标识符，表示该字段被包含在日期字串内

			bool include_time_separator =
				include_hour ||
				include_minute;                                                 // 计算是否需要添加“时间内分隔符”
			bool include_group_separator =
				include_year ||
				include_month ||
				include_day;                                                    // 计算是否需要添加“组间分隔符”

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_time_separator ? ":%S" : (include_group_separator ? " %S" : "%S")),
				time_info
			);                                                                  // 获取秒
			buffer.append(part_buffer);                                         // 添加秒字段
		}

		if (ops & TimeOutputModel::Weekday)                                     // 添加“周”字段
		{
			include_weekday = true;                                             // 修改标识符，表示该字段被包含在日期字串内

			bool include_group_separator =
				include_year ||
				include_month ||
				include_day ||
				include_hour ||
				include_minute ||
				include_second;                                                 // 计算是否需要添加“组间分隔符”

			strftime(
				part_buffer,
				sizeof(part_buffer),
				(include_group_separator ? " %A" : "%A"),
				time_info
			);                                                                  // 获取周
			buffer.append(part_buffer);                                         // 添加周字段
		}

		return buffer;                                                          // 返回日期字符串
	}
};

#endif // !TIME_OUTPUT_MODEL_H_
