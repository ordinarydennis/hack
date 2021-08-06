#pragma once

#include "packet_define_req.h"
#include "packet_define_ack.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HandlerReqLogin(const hack::Fd fd, const hack::Packet* packet, hack::SendHelperFp sendhelper) {

	hack::Log("HandlerReqLogin packet_id_: {}, size_: {}", packet->header_.packet_id_, packet->header_.size_);

	auto size = sizeof(hack::Header);

	hack::Log("HandlerReqLogin size: {}", size);

	const char* bodyBuf = reinterpret_cast<const char*>(packet) + sizeof(hack::Header);

	const PdReqLogin* pdReqLogin = reinterpret_cast<const PdReqLogin*>(bodyBuf);

	hack::Log("HandlerReqLogin id: {}, pw: {}", pdReqLogin->id_, pdReqLogin->pw_);


	//body
	PdAckLogin pdAckLogin;
	pdAckLogin.result_ = 1;

	//todo session을 인자로 넘기는게 낫나?
	sendhelper(fd, 22, reinterpret_cast<const char*>(&pdAckLogin), sizeof(pdAckLogin));

}