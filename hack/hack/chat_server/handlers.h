#pragma once

#include "packet_define_req.h"
#include "packet_define_ack.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HandlerReqLogin(hack::SendHelperFp sendhelper, const hack::Packet* packet) {

	hack::Log("HandlerReqLogin packet_id_: {}, size_: {}", packet->header_.packet_id_, packet->header_.size_);

	auto size = sizeof(hack::Header);

	hack::Log("HandlerReqLogin size: {}", size);

	const char* bodyBuf = reinterpret_cast<const char*>(packet) + sizeof(hack::Header);

	const PdReqLogin* pdReqLogin = reinterpret_cast<const PdReqLogin*>(bodyBuf);

	hack::Log("HandlerReqLogin id: {}, pw: {}", pdReqLogin->id_, pdReqLogin->pw_);


	//header
	hack::Packet ackPacket;

	//body
	PdAckLogin pdAckLogin;
	pdAckLogin.result_ = 1;

	ackPacket.header_.size_ = sizeof(ackPacket) + sizeof(pdAckLogin);
	ackPacket.header_.packet_id_ = 22;

	char sendBuf[256] = { 0, };

	//copy header
	memcpy(sendBuf, reinterpret_cast<char*>(&ackPacket), sizeof(ackPacket));

	//copy body
	memcpy(sendBuf + sizeof(ackPacket), reinterpret_cast<char*>(&pdAckLogin), sizeof(pdAckLogin));

	sendhelper(5, sendBuf, ackPacket.header_.size_);

}