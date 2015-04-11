#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FastAddTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(DateTest) 
		{	
			Date Someday;

			Someday.insertDay(27);
			int expectedDate=27;
			int actualDate=Someday.getDay();
			Assert::AreEqual(expectedDate, actualDate);

			Someday.insertMonth(9);
			int expectedMonthNumber=9;
			int actualMonthNumber=Someday.getMonthNumber();
			Assert::AreEqual(expectedMonthNumber, actualMonthNumber);

			string expectedMonth="Sep";
			string actualMonth=Someday.getMonth();
			Assert::AreEqual(expectedMonth, actualMonth);
			
			Someday.insertYear(2013);
			int expectedYear=2013;
			int actualYear=Someday.getYear();
			Assert::AreEqual(expectedYear, actualYear);

			Assert::IsTrue(Someday.getDateStatus());				
		}
		
		TEST_METHOD(TimeTest) 
		{	
			Time Sometime;
			date today(day_clock::local_day());
			int expectedHour=20;
			int expectedMinute=20;
			Sometime.insertHour(expectedHour);
			Sometime.insertMinute(expectedMinute);
			Sometime.initialiseTime(today);
			int actualHour=Sometime.getHour();
			Assert::AreEqual(expectedHour, actualHour);
			int actualMinute=Sometime.getMinute();
			Assert::AreEqual(expectedMinute, actualMinute);

			Assert::IsTrue(Sometime.getTimeStatus());				
		}
		

		TEST_METHOD(ScheduledEntryTest) //addEntry and removeEntry for scheduled
		{
			vector<string> expectedAnswser;
			expectedAnswser.push_back("b");
			expectedAnswser.push_back("c");
			expectedAnswser.push_back("d");
				
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;
	
			testScheduled.insertName("b");
			testInfo.addEntry(testScheduled);
			testScheduled.insertName("c");
			testInfo.addEntry(testScheduled);
			testScheduled.insertName("d");
			testInfo.addEntry(testScheduled);
		
			//testInfo.removeEntry(true, 1);
			vector<Entry> actualResult;
			actualResult = testInfo.getScheduledList();
			int size = actualResult.size();
			Assert::AreEqual(3,size);

			/*for(int i=0; i<3; i++){
				Assert::AreEqual(expectedAnswser[i],actualResult[i]);
			}*/
		}


		TEST_METHOD(EntryTest) 
		{
			Entry testInfo;
		
			//test for name
			testInfo.insertName("dinner with me");
			string actualAnswer = testInfo.getName();	
			string expectedAnswer = "dinner with me";
			Assert::AreEqual(expectedAnswer,actualAnswer);
			
			//test for entryNumber
			testInfo.insertEntryNumber(1);
			int b=testInfo.getEntryNumber();
			Assert::AreEqual(1,b);

			//test for location
			testInfo.insertLocation("utown");
			actualAnswer=testInfo.getLocation();	
			expectedAnswer="utown";
			Assert::AreEqual(expectedAnswer,actualAnswer);
		}
	};
}
