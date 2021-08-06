#pragma once

#pragma pack(push, 1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PdReqLogin {

	static constexpr uint16_t MAX_USER_ID_BYTE_LENGTH = 16;
	static constexpr uint16_t MAX_USER_PW_BYTE_LENGTH = 16;

	char id_[MAX_USER_ID_BYTE_LENGTH] = { 0, };
	char pw_[MAX_USER_PW_BYTE_LENGTH] = { 0, };

};

#pragma pack(pop)