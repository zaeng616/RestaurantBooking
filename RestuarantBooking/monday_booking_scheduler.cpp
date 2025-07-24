#include "booking_scheduler.cpp"
class MondayBookingScheduler :public BookingScheduler {
public:
	using BookingScheduler::BookingScheduler;
	time_t getNow() {
		return getTime(2024, 6, 3, 17, 0);
	}
private:
	time_t getTime(int year, int mon, int day, int hour, int min) {
		tm result = { 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		return mktime(&result);
	}
};