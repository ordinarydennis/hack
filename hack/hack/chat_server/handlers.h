#pragma once

#include "packet_define_req.h"
#include "packet_define_ack.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnConnectSession(const hack::Session* session, const hack::Packet* packet) {

	hack::Log("OnConnectSession fd {}" , session->FD());

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnCloseSession(const hack::Session* session, const hack::Packet* packet) {

	hack::Log("OnCloseSession fd {}", session->FD());

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HandlerReqLogin(const hack::Session* session, const hack::Packet* packet) {

	const char* bodyBuf = reinterpret_cast<const char*>(packet) + sizeof(hack::Header);

	const PdReqLogin* pdReqLogin = reinterpret_cast<const PdReqLogin*>(bodyBuf);

	hack::Log("HandlerReqLogin id: {}, pw: {}", pdReqLogin->id_, pdReqLogin->pw_);

	//body
	PdAckLogin pdAckLogin;
	pdAckLogin.result_ = 1;

	//body 직렬화 템플릿 함수 있으면 좋겠다.

	if (session) {

		session->SendPacket(22, reinterpret_cast<const char*>(&pdAckLogin), sizeof(pdAckLogin));
	
	}

}