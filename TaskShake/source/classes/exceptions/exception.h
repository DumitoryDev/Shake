#pragma once
#include"..//..//..//task_snake//stdafx.h"


namespace game_error
{
	/*
	 *	классы для исключений игры
	 *
	 *
	 */
	class m_exception final : public std::exception
	{

	public:

		m_exception(const m_exception&) = default;
		m_exception(m_exception&&) = default;
		m_exception& operator = (const m_exception&) = default;
		m_exception& operator = (m_exception&&) = default;
		
	
		explicit m_exception(const char * message):std::exception(message)
		{
			
		}
		

	};


	class m_win_api_exception
	{

	public:
		m_win_api_exception(const m_win_api_exception&) = default;
		m_win_api_exception(m_win_api_exception&&) = default;
		m_win_api_exception& operator = (const m_win_api_exception&) = default;
		m_win_api_exception& operator = (m_win_api_exception&&) = default;
		using ulong = unsigned long;

		explicit m_win_api_exception(const std::wstring& ws_message) : m_win_api_exception(ws_message, {}) { }

		explicit m_win_api_exception(const ulong ul_code) : m_win_api_exception({}, ul_code) { }

		explicit m_win_api_exception(std::wstring ws_message,
			const ulong ul_code) : m_ws_message_(std::move(ws_message)), m_ul_code_(ul_code) { }
		


		std::wstring GetMessage(void) const
		{

			if (!this->m_ul_code_)
				return this->m_ws_message_;

			LPVOID lp_msg_buf{};

			if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				{},
				this->m_ul_code_,
				MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lp_msg_buf),
				{},
				{}))
				return this->m_ws_message_;

			std::wostringstream wos{};
			wos << this->m_ws_message_ << std::endl;
			wos << L"Error code " << this->m_ul_code_ << std::endl;
			wos << reinterpret_cast<LPCWSTR>(lp_msg_buf);

			::LocalFree(lp_msg_buf);

			return wos.str();

		}

	private:
		std::wstring m_ws_message_{};
		ulong m_ul_code_{};


	};




}