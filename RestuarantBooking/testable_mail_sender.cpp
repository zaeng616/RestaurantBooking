#include "mail_sender.cpp"
#include <iostream>
class TestableMailSender : public MailSender {
public:
	void sendMail(Schedule* schedule) override {
		std::cout << "테스트용 MailSender class의 send메서드 실행됨\n";
		countSendMailMethodIsCalled++;
	}
	int getCountSendMethodIsCalled() {
		return countSendMailMethodIsCalled;
	}
private:
	int countSendMailMethodIsCalled = 0;
};