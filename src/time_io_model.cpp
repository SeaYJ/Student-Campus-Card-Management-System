#include "time_io_model.h"

std::time_t TimeInputModel::InputFormatTime(
	const std::int32_t year,
	const std::int32_t month,
	const std::int32_t day,
	const std::int32_t hour,
	const std::int32_t minute,
	const std::int32_t second)
{
	// �����ݡ��·ݡ�Сʱ�����Ӻ������Ч��
	if (year < 1900 || year > 9999 ||
		month < 1 || month > 12 ||
		hour < 0 || hour > 23 ||
		minute < 0 || minute > 59 ||
		second < 0 || second > 59) {
		throw std::invalid_argument("Invalid year, month, hour, minute, or second.The \"year\" must be between 1900 and 9999; the \"month\" must be between 1 and 12; the \"hour\" must be between 0 and 23; the \"minute\" must be between 0 and 59; and the \"second\" must be between 0 and 59.");
	}

	// ��������Ƿ���Ч
	if (day < 1 || day > GetMaxDaysInMonth(year, month)) {
		throw std::invalid_argument("Invalid day for the given month and year.");
	}

	std::tm timeinfo = { 0 };
	timeinfo.tm_year = year - 1900; // ���Ϊ2000�꣨��1900�꿪ʼ���㣩
	timeinfo.tm_mon = month - 1;    // �·�Ϊ0����0��ʼ������
	timeinfo.tm_mday = day;         // ����
	timeinfo.tm_hour = hour;        // Сʱ
	timeinfo.tm_min = minute;       // ����
	timeinfo.tm_sec = second;       // ��

	std::time_t time = std::mktime(&timeinfo);
	if (time == -1) {
		throw std::invalid_argument("The date and time combination is not valid.");
	}

	return time;
}

int TimeInputModel::GetMaxDaysInMonth(int year, int month) {
	// �ж��Ƿ�Ϊ����
	bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

	// �����·ݷ�������
	switch (month) {
	case 4: case 6: case 9: case 11:
		return 30;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		return isLeapYear ? 29 : 28;
	default:
		// ����·ݵ���Ч��
		throw std::invalid_argument("Invalid month.");
	}
}

std::string TimeOutputModel::OutputFormatTime(const tm* time_info, const std::int8_t ops)

{
	std::string buffer = "";                                                // ����ֵ������
	char part_buffer[16];                                                   // ��ѡʱ���ֶλ�����

	bool include_year = false;                                              // �Ƿ�������ꡱ���ֶ�
	bool include_month = false;                                             // �Ƿ�������¡����ֶ�
	bool include_day = false;                                               // �Ƿ�������ա����ֶ�
	bool include_hour = false;                                              // �Ƿ������ʱ�����ֶ�
	bool include_minute = false;                                            // �Ƿ�������֡����ֶ�
	bool include_second = false;                                            // �Ƿ�������롱���ֶ�
	bool include_weekday = false;                                           // �Ƿ�������ܡ����ֶ�

	if (ops & TimeOutputModel::Year)                                        // ��ӡ��ꡱ�ֶ�
	{
		include_year = true;                                                // �޸ı�ʶ������ʾ���ֶα������������ִ���

		strftime(
			part_buffer,
			sizeof(part_buffer),
			"%Y",
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ������ֶ�
	}

	if (ops & TimeOutputModel::Month)                                       // ��ӡ��¡��ֶ�
	{
		include_month = true;                                               // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_date_separator = include_year;                          // �����Ƿ���Ҫ��ӡ������ڷָ�����

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_date_separator ? "/%m" : "%m"),
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ������ֶ�
	}

	if (ops & TimeOutputModel::Day)                                         // ��ӡ��ա��ֶ�
	{
		include_day = true;                                                 // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_date_separator =
			include_year ||
			include_month;                                                  // �����Ƿ���Ҫ��ӡ������ڷָ�����

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_date_separator ? "/%d" : "%d"),
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ������ֶ�
	}

	if (ops & TimeOutputModel::Hour)                                        // ��ӡ�ʱ���ֶ�
	{
		include_hour = true;                                                // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;                                                    // �����Ƿ���Ҫ��ӡ����ָ�����
		// ��ν�����ָ�������ΪDate��Time��Weekday���߼�ķָ���

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_group_separator ? " %H" : "%H"),
			time_info
		);                                                                  // ��ȡʱ
		buffer.append(part_buffer);                                         // ���ʱ�ֶ�
	}

	if (ops & TimeOutputModel::Minute)                                      // ��ӡ��֡��ֶ�
	{
		include_minute = true;                                              // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_time_separator =
			include_hour;                                                   // �����Ƿ���Ҫ��ӡ�ʱ���ڷָ�����
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;                                                    // �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_time_separator ? ":%M" : (include_group_separator ? " %M" : "%M")),
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ��ӷ��ֶ�
	}

	if (ops & TimeOutputModel::Second)                                      // ��ӡ��롱�ֶ�
	{
		include_second = true;                                              // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_time_separator =
			include_hour ||
			include_minute;                                                 // �����Ƿ���Ҫ��ӡ�ʱ���ڷָ�����
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;                                                    // �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_time_separator ? ":%S" : (include_group_separator ? " %S" : "%S")),
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ������ֶ�
	}

	if (ops & TimeOutputModel::Weekday)                                     // ��ӡ��ܡ��ֶ�
	{
		include_weekday = true;                                             // �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day ||
			include_hour ||
			include_minute ||
			include_second;                                                 // �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer,
			sizeof(part_buffer),
			(include_group_separator ? " %A" : "%A"),
			time_info
		);                                                                  // ��ȡ��
		buffer.append(part_buffer);                                         // ������ֶ�
	}

	return buffer;                                                          // ���������ַ���
}
