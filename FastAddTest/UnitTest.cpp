#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FastAddTest {		
	TEST_CLASS(UnitTest1) {
	public:

		//@author A0116660L
		TEST_METHOD(EntryDateTest) {	
			Date Someday;

			Someday.insertDay(27);
			Someday.insertMonth(9);
			Someday.insertYear(2013);
			Someday.initialiseDate();

			int expectedDate = 27;
			int expectedMonthNumber = 9;
			string expectedMonth = "Sep";
			int expectedYear = 2013;
			int actualDate=Someday.getDay();
			Assert::AreEqual(expectedDate, actualDate);

			Someday.insertMonth(9);
			int actualMonthNumber=Someday.getMonthNumber();
			Assert::AreEqual(expectedMonthNumber, actualMonthNumber);
			string actualMonth=Someday.getMonth();
			Assert::AreEqual(expectedMonth, actualMonth);
			
			Someday.insertYear(2013);
			int actualYear=Someday.getYear();
			Assert::AreEqual(expectedYear, actualYear);

			Assert::IsTrue(Someday.getDateStatus());				
		}
		
		TEST_METHOD(EntryTimeTest) {	
			Time Sometime;
			date today(day_clock::local_day());
			int expectedHour = 20;
			int expectedMinute = 20;
			Sometime.insertHour(expectedHour);
			Sometime.insertMinute(expectedMinute);
			Sometime.initialiseTime(today);
			int actualHour = Sometime.getHour();
			Assert::AreEqual(expectedHour, actualHour);
			int actualMinute = Sometime.getMinute();
			Assert::AreEqual(expectedMinute, actualMinute);

			Assert::IsTrue(Sometime.getTimeStatus());				
		}

		
		TEST_METHOD(EntryTest) {
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
			expectedAnswer = "utown";
			Assert::AreEqual(expectedAnswer,actualAnswer);
		}

		TEST_METHOD(TestUITest) {
			string testInfo = "edit dinner with me";
			TextUI line(testInfo);
			string expectedCommandWord = "edit";
			string actualCommandWord=line.findCommand(testInfo);
			Assert::AreEqual(expectedCommandWord, actualCommandWord);
		}
		

		//addEntry for scheduled and floating
		TEST_METHOD(EntryListAddTest) {
				
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;
	
			int dummy;
			testScheduled.insertName("a");
			testInfo.addEntry(testScheduled, dummy);
			testScheduled.insertName("b");
			testInfo.addEntry(testScheduled, dummy);
			testScheduled.insertName("c");
			testInfo.addEntry(testScheduled, dummy);
			testScheduled.insertName("d");
			testInfo.addEntry(testScheduled, dummy);
			
			vector<Entry> actualResult;
			actualResult = testInfo.getScheduledList();
			int size = actualResult.size();
			Assert::AreEqual(4,size);
		
		}		

		//@author A0116660L
		TEST_METHOD(EntryAddTest) {	
			string expectedName = "testing";
			string expectedLocation = "NUS ";
			string expectedTag = "#meeting";
			string expectedStatus = "done";
			string expectedStartDate = "20 Apr 2015";
			string expectedEndDate = "21 Apr 2015";
			string expectedStartTime = "18.30";
			string expectedEndTime = "21.45";
			string input = " testing. from 20 Apr 2015 18.30 to 21 Apr 2015 21.45 at NUS #meeting";
			string actualName;
			string actualLocation;
			vector<string> actualTag;
			string actualStatus;
			string actualStartDate;
			string actualEndDate;
			string actualStartTime;
			string actualEndTime;

			EntryAdd testDissectCommand;
			testDissectCommand.dissectCommand(input,actualName, actualStartDate, actualStartTime, actualEndDate, 
											  actualEndTime, actualLocation, actualTag);
			Assert::AreEqual(expectedName, actualName);
			Assert::AreEqual(expectedStartDate, actualStartDate);
			Assert::AreEqual(expectedStartTime, actualStartTime);
			Assert::AreEqual(expectedEndDate, actualEndDate);
			Assert::AreEqual(expectedEndTime, actualEndTime);
			Assert::AreEqual(expectedLocation, actualLocation);

		}

		//test on editEntry tag for floating tasks
			TEST_METHOD(EntryListEditNameFloatingTest) 
			{		
			string expectedAnswer="k";
			
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;

			testScheduled.insertName("a");
			testScheduled.insertEntryNumber(1);
			
			testScheduled.initialiseStatus();
			testScheduled.insertLocation("utown");
			vector<string> vectorTag;
			vectorTag.push_back("#study");
			testScheduled.insertTags(vectorTag);

			int dummyNumber;
			testInfo.addEntry(testScheduled,dummyNumber);			
			
			string dummyString;
			string userInput = "1 name k";
			testInfo.editEntry(true, userInput, dummyString);	
			string actualResult;
			vector<Entry> dummyEntry = testInfo.getScheduledList();
			testScheduled = dummyEntry.back();
			actualResult = testScheduled.getName();
					
			Assert::AreEqual(expectedAnswer,actualResult);
		}

		//@author A0100750Y
		//test on editEntry name for scheduled tasks
		TEST_METHOD(EntryListEditNameTest) 
		{
			string expectedAnswer="k";
						
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;
	
			testScheduled.insertName("a");
			testScheduled.insertEntryNumber(1);
			Date startDate;
			startDate.insertDay(17);
			startDate.insertMonth(2);
			startDate.insertYear(2014);
			startDate.initialiseDate();
			testScheduled.insertStartDate(startDate);

			Date endDate;
			endDate.insertDay(26);
			endDate.insertMonth(2);
			endDate.insertYear(2014);
			endDate.initialiseDate();
			testScheduled.insertEndDate(endDate);

			Time startTime;
			startTime.insertHour(12);
			startTime.insertMinute(13);
			testScheduled.insertStartTime(startTime);
			
			Time endTime;
			startTime.insertHour(14);
			startTime.insertMinute(16);
			testScheduled.insertEndTime(endTime);
	
			testScheduled.initialiseStatus();
			testScheduled.insertLocation("utown");
			vector<string> vectorTag;
			vectorTag.push_back("#study");
			testScheduled.insertTags(vectorTag);

			int dummyNumber;
			testInfo.addEntry(testScheduled,dummyNumber);			
			
			string dummyString;
			string userInput = "1 name k";
			testInfo.editEntry(true, userInput, dummyString);	
			string actualResult;
			vector<Entry> dummyEntry = testInfo.getScheduledList();
			testScheduled = dummyEntry.back();
			actualResult = testScheduled.getName();

			Assert::AreEqual(expectedAnswer,actualResult);
		}

		//@author A0100750Y
		//editEntry tag for floating
		TEST_METHOD(EntryListEditTagFloatingTest) 
			{		
			string expectedAnswer="#play ";
			
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;

			testScheduled.insertName("a");
			testScheduled.insertEntryNumber(1);
			
			testScheduled.initialiseStatus();
			testScheduled.insertLocation("utown");
			vector<string> vectorTag;
			vectorTag.push_back("#study");
			testScheduled.insertTags(vectorTag);

			int dummyNumber;
			testInfo.addEntry(testScheduled,dummyNumber);			

			string dummyString;
			string userInput = "1 add #play. remove #study";		
			testInfo.editEntry(true, userInput, dummyString);		
			string actualResult;
			vector<Entry> dummyEntry = testInfo.getScheduledList();
			testScheduled = dummyEntry.back();
			actualResult = testScheduled.getTags();		

			Assert::AreEqual(expectedAnswer,actualResult);	
		}
		
		//@author A0100750Y
		//tests on editEntry loc for floating tasks
		TEST_METHOD(EntryListEditLocFloatingTest) 
		{		
			string expectedAnswer="yih";
			
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;

			testScheduled.insertName("a");
			testScheduled.insertEntryNumber(1);			
			
			testScheduled.initialiseStatus();
			testScheduled.insertLocation("utown");
			vector<string> vectorTag;
			vectorTag.push_back("#study");
			testScheduled.insertTags(vectorTag);

			int dummyNumber;
			testInfo.addEntry(testScheduled,dummyNumber);			
			
			string dummyString;
			string userInput = "1 place yih";			
			testInfo.editEntry(true, userInput, dummyString);		
			string actualResult;
			vector<Entry> dummyEntry = testInfo.getScheduledList();
			testScheduled = dummyEntry.back();
			actualResult = testScheduled.getLocation();	

			Assert::AreEqual(expectedAnswer,actualResult);				
		}

		//@author A0100750Y
		//removeEntry for scheduled and floating
		TEST_METHOD(EntryListsRemoveTest) 
		{
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;
	
			int dummyNumber;
			testScheduled.insertName("a");
			testInfo.addEntry(testScheduled, dummyNumber);
			testScheduled.insertName("b");
			testInfo.addEntry(testScheduled, dummyNumber);
			testScheduled.insertName("c");
			testInfo.addEntry(testScheduled, dummyNumber);
			testScheduled.insertName("d");
			testInfo.addEntry(testScheduled, dummyNumber);
			
			string dummyString;
			testInfo.removeEntry(false, 1, dummyString);		
			/*vector<Entry> actualResult;
			actualResult = testInfo.getScheduledList();
			int size = actualResult.size();
			Assert::AreEqual(3,size);*/
		}	

		//@author A0100750Y
		//tests on DateTimeInspector
		TEST_METHOD(DateTimeInspectorTest)
		{
			DateTimeInspector aDay;
			Assert::IsTrue(aDay.dateIsValid(31, 03, 2014));			
			Assert::IsTrue(aDay.timeIsValid(12,59));
			Assert::IsFalse(aDay.timeIsValid(25,10));
			Assert::IsFalse(aDay.timeIsValid(20,61));
		}
		
	};
}

