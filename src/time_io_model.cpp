#include "time_io_model.h"

std::time_t TimeInputModel::InputFormatTime(
	const std::int32_t year,
	const std::int32_t month,
	const std::int32_t day,
	const std::int32_t hour,
	const std::int32_t minute,
	const std::int32_t second)
{
	// 检查年份、月份、小时、分钟和秒的有效性
	if (year < 1900 || year > 9999 ||
		month < 1 || month > 12 ||
		hour < 0 || hour > 23 ||
		minute < 0 || minute > 59 ||
		second < 0 || second > 59) {
		throw std::invalid_argument("Invalid year, month, hour, minute, or second.The \"year\" must be between 1900 and 9999; the \"month\" must be between 1 and 12; the \"hour\" must be between 0 and 23; the \"minute\" must be between 0 and 59; and the \"second\" must be between 0 and 59.");
	}

	// 检查天数是否有效
	if (day < 1 || day > GetMaxDaysInMonth(year, month)) {
		throw std::invalid_argument("Invalid day for the given month and year.");
	}

	std::tm timeinfo = { 0 };
	timeinfo.tm_year = year - 1900; // 年份为2000年（从1900年开始计算）
	timeinfo.tm_mon = month - 1;    // 月份为0（从0开始计数）
	timeinfo.tm_mday = day;         // 日期
	timeinfo.tm_hour = hour;        // 小时
	timeinfo.tm_min = minute;       // 分钟
	timeinfo.tm_sec = second;       // 秒

	std::time_t time = std::mktime(&timeinfo);
	if (time == -1) {
		throw std::invalid_argument("The date and time combination is not valid.");
	}

	return time;
}

int TimeInputModel::GetMaxDaysInMonth(int year, int month) {
	// 判断是否为闰年
	bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

	// 根据月份返回天数
	switch (month) {
	case 4: case 6: case 9: case 11:
		return 30;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		return isLeapYear ? 29 : 28;
	default:
		// 检查月份的有效性
		throw std::invalid_argument("Invalid month.");
	}
}

std::string TimeOutputModel::OutputFormatTime(const tm* time_info, const std::int8_t ops)

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
