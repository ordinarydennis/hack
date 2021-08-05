#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestHandler(hack::SendHelperFp sendhelper, const hack::Packet& p)
{
	char buf[123] = { "aasdfq1112234" };

	hack::SendBuffSize buffSize = static_cast<hack::SendBuffSize>(strlen(buf));

	sendhelper(p.fd_, buf, buffSize);
}