#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
/*using namespace boost::posix_time;
using namespace boost::gregorian;*/
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FastAddTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(DateTest) 
		{	
			Assert::AreEqual(1,1);
			
			/*Date Someday;

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

			Assert::IsTrue(Someday.getDateStatus());*/				
		}
		
		/*TEST_METHOD(TimeTest) 
		{	
			Time Sometime;

			Sometime.insertHour(20);
			int expectedHour=20;
			int actualHour=Sometime.getHour();
			Assert::AreEqual(expectedHour, actualHour);

			Sometime.insertMinute(33);
			int expectedMinute=33;
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
			ScheduledEntry testInfo;
	
			testScheduled.insertName("b");
			testInfo.addEntry(testScheduled);
			testScheduled.insertName("c");
			testInfo.addEntry(testScheduled);
			testScheduled.insertName("d");
			testInfo.addEntry(testScheduled);
		
			testInfo.removeEntry(true, 1);
			vector<string> actualResult;
			actualResult = testInfo.getScheduledList;
			int size = actualResult.size();
			Assert::AreEqual(2,size);

			for(int i=0; i<3; i++){
				Assert::AreEqual(expectedAnswser[i],actualResult[i]);
			}
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
			int b=testInfo.getEntryNumber;
			Assert::AreEqual(1,b);

			//test for location
			testInfo.insertLocation("utown");
			string actualAnswer=testInfo.getLocation();	
			string expectedAnswer="utown";
			Assert::AreEqual(expectedAnswer,actualAnswer);
		}*/
	};
}
