#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FastAddTest {		
	TEST_CLASS(UnitTest1) {
	public:

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

		TEST_METHOD(EntryListEditNameTest) 
		{
			//vector<string> expectedAnswer;
			string expectedAnswer="k";

			//expectedAnswer.push_back(expected);
			
			Entry testScheduled; 
			Entry testFloating;	
			EntryLists testInfo;
	
			testScheduled.insertName("a");
			testScheduled.insertEntryNumber(1);

			/*Date startDate;
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
			testScheduled.insertTags(vectorTag);*/

			int dummyNumber;
			testInfo.addEntry(testScheduled, dummyNumber);			
			
			//vector<Entry> actualResult;
			string userInput = "1 name k";
			string dummyString;
			testInfo.editEntry(true, userInput, dummyString);		
			string actualResult;

			vector<Entry> whatever = testInfo.getScheduledList();
			testScheduled = whatever.back();
			actualResult = testScheduled.getName();
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
		TEST_METHOD(EntryListAddScheduledTest) {
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
		TEST_METHOD(EntryListsRemoveTest) {
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
		TEST_METHOD(EntryListsGetEntryDisplayTest) {
			string expectedAnswer = "b";
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
		//@author A0115902N
		TEST_METHOD(ClashInspectorTest) {
			vector<Entry> dummy;
			Entry firstEntry;
			Entry secondEntry;

			Date firstDate;
			Date secondDate;
			Time firstStartTime;
			Time firstEndTime;
			Time secondStartTime;
			Time secondEndTime;

			firstDate.insertDay(10);
			firstDate.insertMonth(5);
			firstDate.insertYear(2015);
			firstDate.initialiseDate();
			secondDate.insertDay(10);
			secondDate.insertMonth(5);
			secondDate.insertYear(2015);
			secondDate.initialiseDate();

			firstStartTime.insertHour(10);
			firstStartTime.insertMinute(30);
			firstEndTime.insertHour(11);
			firstEndTime.insertMinute(30);

			secondStartTime.insertHour(10);
			secondStartTime.insertMinute(30);
			secondEndTime.insertHour(11);
			secondEndTime.insertMinute(30);

			firstEntry.insertStartDate(firstDate);
			firstEntry.insertEndDate(firstDate);
			firstEntry.insertStartTime(firstStartTime);
			firstEntry.insertEndTime(firstEndTime);

			secondEntry.insertStartDate(secondDate);
			secondEntry.insertEndDate(secondDate);
			secondEntry.insertStartTime(secondStartTime);
			secondEntry.insertEndTime(secondEndTime);

			bool clash = false;
			bool print = false;
			int dummyInt = 1;
			ClashInspector inspector(dummy);
			inspector.inspectEntries(firstEntry, secondEntry, dummyInt, clash, print);
			
			Assert::AreEqual(true, clash);
		}
		//@author A0115902N
		TEST_METHOD(StringConvertorTest) {
			StringConvertor convertor;
			string dateInput = "14 mar 15";
			int day;
			int month;
			int year;
			int expectedDay = 14;
			int expectedMonth = 3;
			int expectedYear = 2015;
			int number;
			int expectedNumber = 12;
			convertor.convertDate(dateInput, day, month, year);
			Assert::AreEqual(expectedDay, day);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedYear, year);

			string numberInput = "12";
			convertor.convertStringToNumber(numberInput, number);
			Assert::AreEqual(expectedNumber, number);
			string dateLongInput = "14 mar 15 to 15 mar 15";
			string expectedStartDate = "14 mar 15";
			string expectedEndDate = "15 mar 15";
			string resultStartDate;
			string resultEndDate;
			convertor.extractStringDate(dateLongInput, resultStartDate);
			dateLongInput = dateLongInput.substr(3);
			convertor.extractStringDate(dateLongInput, resultEndDate);
			Assert::AreEqual(expectedStartDate, resultStartDate);
			Assert::AreEqual(expectedEndDate, resultEndDate);
		}
	};
	}
