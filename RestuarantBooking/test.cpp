#include "gmock/gmock.h"
#include "booking_scheduler.cpp"

class BookingItem : public testing::Test {
public:
	void SetUp() override {
		ON_THE_HOUR = getTime(2021 - 1900, 03 - 1, 26, 9, 0, 0);
		NOT_ON_THE_HOUR = getTime(2021 - 1900, 03 - 1, 26, 9, 5, 0);
	}
	tm getTime(int year, int mon, int day, int hour, int min, int sec) {
		tm result = { sec, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		mktime(&result);
		return result;
	}

	tm ON_THE_HOUR;
	tm NOT_ON_THE_HOUR;
	Customer CUSTOMER{ "Fake name", "010-1234-5678" };
	const int UNDER_CAPACITY = 1;
	const int CAPACITY_PER_HOUR = 3;
	BookingScheduler bookingScheduler{ CAPACITY_PER_HOUR };
};

TEST_F(BookingItem, 예약은정시에만가능하다정시가아닌경우예약불가) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	EXPECT_THROW({
	bookingScheduler.addSchedule(schedule);
		}, std::runtime_error);
}

TEST_F(BookingItem, 예약은정시에만가능하다정시인경우예약가능) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	bookingScheduler.addSchedule(schedule);

	EXPECT_TRUE(bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, 시간대별인원제한이있다같은시간대에Capacity초과할경우예외발생) {

}

TEST_F(BookingItem, 시간대별인원제한이있다같은시간대가다르면Capacity차있어도스케쥴추가성공) {

}

TEST_F(BookingItem, 예약완료시SMS는무조건발송) {

}

TEST_F(BookingItem, 이메일이없는경우에는이메일미발송) {

}

TEST_F(BookingItem, 이메일이있는경우에는이메일발송) {

}

TEST_F(BookingItem, 현재날짜가일요일인경우예약불가예외처리) {

}

TEST_F(BookingItem, 현재날짜가일요일이아닌경우예약가능) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}