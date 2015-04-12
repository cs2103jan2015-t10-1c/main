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

		TEST_METHOD(EntryDateTest) 
		{	
			Date Someday;

			Someday.insertDay(27);
			Someday.insertMonth(9);
			Someday.insertYear(2013);
			Someday.initialiseDate();

			int expectedDate=27;
			int expectedMonthNumber=9;
			string expectedMonth="Sep";
			int expectedYear=2013;

			int actualDate=Someday.getDay();
			Assert::AreEqual(expectedDate, actualDate);

			int actualMonthNumber=Someday.getMonthNumber();
			Assert::AreEqual(expectedMonthNumber, actualMonthNumber);

			string actualMonth=Someday.getMonth();
			Assert::AreEqual(expectedMonth, actualMonth);
			
			int actualYear=Someday.getYear();
			Assert::AreEqual(expectedYear, actualYear);

			Assert::IsTrue(Someday.getDateStatus());				
		}
		
		TEST_METHOD(EntryTimeTest) 
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

		TEST_METHOD(EntryListEditNameTest) 
		{
			//vector<string> expectedAnswer;
			string expectedAnswer="k. from 17 Feb 2014 12.13 to 26 Feb 2014 14.15 at utown #study";
			//expectedAnswer.push_back(expected);
			
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
			testInfo.addEntry(testScheduled, dummyNumber);			
			
			//vector<Entry> actualResult;
			string userInput = "1 name k";
			string dummyString;
			testInfo.editEntry(true, userInput, dummyString);		
			string actualResult;
			actualResult = testInfo.getEntryDisplay(true, 1);
			//testInfo.getName();

			Assert::AreEqual(expectedAnswer, actualResult);
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

		TEST_METHOD(TestUITest) 
		{
			string testInfo="edit dinner with me";
			TextUI line(testInfo);
			string expectedCommandWord="edit";
			string actualCommandWord=line.findCommand(testInfo);
			Assert::AreEqual(expectedCommandWord, actualCommandWord);
		}
		

		//addEntry for scheduled and floating
		TEST_METHOD(EntryListAddScheduledTest) 
		{
			vector<string> expectedAnswser;
			expectedAnswser.push_back("a");
			expectedAnswser.push_back("b");
			expectedAnswser.push_back("c");
			expectedAnswser.push_back("d");
				
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

		//removeEntry for scheduled and floating
		TEST_METHOD(EntryListsRemoveTest) 
		{
			vector<string> expectedAnswser;
			expectedAnswser.push_back("a");
			expectedAnswser.push_back("b");
			expectedAnswser.push_back("c");
			expectedAnswser.push_back("d");
				
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
			
			string deleteFeedback;
			testInfo.removeEntry(true, 1, deleteFeedback);			
			int size = actualResult.size();
			Assert::AreEqual(3,size);
		}

		//test for getEntryDisplay from Entrylists
		TEST_METHOD(EntryListsGetEntryDisplayTest) 
		{
			string expectedAnswer= "b";
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
			
			string actualResult;
			actualResult = testInfo.getEntryDisplay(true, 2);

			Assert::AreEqual(expectedAnswer,actualResult);
	
		}
	};
}
