#include "gmock/gmock.h"
#include "booking_scheduler.cpp"
time_t getTime(int year, int mon, int day, int hour, int min, int sec) {
	tm result = { sec, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
	return mktime(&result);
}

string getTimeString(const tm& tmTime) {
	std::ostringstream oss;
	oss << std::put_time(&tmTime, "%Y-%m-%d  %H:%M:%S (%A)");
	return oss.str();
}
TEST(BookingSchedulerTest, 예약은정시에만가능하다정시가아닌경우예약불가) {
	tm notOnTheHour = { 0 };
	notOnTheHour.tm_year = 2021 - 1900;
	notOnTheHour.tm_mon = 03 - 1;
	notOnTheHour.tm_mday = 26;
	notOnTheHour.tm_hour = 9;
	notOnTheHour.tm_min = 5;
	notOnTheHour.tm_isdst = -1;
	mktime(&notOnTheHour);
	Customer customer{ "Fake name", "010-1234-5678" };
	Schedule* schedule = new Schedule{ notOnTheHour, 1, customer };
	BookingScheduler bookingScheduler{ 3 };

	EXPECT_THROW({
	bookingScheduler.addSchedule(schedule);
		}, std::runtime_error);
}

TEST(BookingSchedulerTest, 예약은정시에만가능하다정시인경우예약가능) {
	tm notOnTheHour = { 0 };
	notOnTheHour.tm_year = 2021 - 1900;
	notOnTheHour.tm_mon = 03 - 1;
	notOnTheHour.tm_mday = 26;
	notOnTheHour.tm_hour = 9;
	notOnTheHour.tm_min = 0;
	notOnTheHour.tm_isdst = -1;
	mktime(&notOnTheHour);
	Customer customer{ "Fake name", "010-1234-5678" };
	Schedule* schedule = new Schedule{ notOnTheHour, 1, customer };
	BookingScheduler bookingScheduler{ 3 };
	bookingScheduler.addSchedule(schedule);

	EXPECT_TRUE(bookingScheduler.hasSchedule(schedule));
}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대에Capacity초과할경우예외발생) {

}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대가다르면Capacity차있어도스케쥴추가성공) {

}

TEST(BookingSchedulerTest, 예약완료시SMS는무조건발송) {

}

TEST(BookingSchedulerTest, 이메일이없는경우에는이메일미발송) {

}

TEST(BookingSchedulerTest, 이메일이있는경우에는이메일발송) {

}

TEST(BookingSchedulerTest, 현재날짜가일요일인경우예약불가예외처리) {

}

TEST(BookingSchedulerTest, 현재날짜가일요일이아닌경우예약가능) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}