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
		
		//@author A0115656A
        TEST_METHOD(EntryTimeTest) {    
            Time timeTest;
            int expectedHour = 20;
            int expectedMinute = 20;
			date today(day_clock::local_day());
            timeTest.insertHour(expectedHour);
            timeTest.insertMinute(expectedMinute);
            timeTest.initialiseTime(today);
           
			int actualHour = timeTest.getHour();
            Assert::AreEqual(expectedHour, actualHour);
            int actualMinute = timeTest.getMinute();
            Assert::AreEqual(expectedMinute, actualMinute);

            Assert::IsTrue(timeTest.getTimeStatus());                
        }

		TEST_METHOD(EntryEditTest) {
            //scheduled entries
            EntryEdit editTestSch(true);
            bool testBool = editTestSch.getEditStatus();
            Assert::AreEqual(true, testBool);
            testBool = editTestSch.getDateEditStatus();
            Assert::AreEqual(false, testBool);
            testBool = editTestSch.getTimeEditStatus();
            Assert::AreEqual(false, testBool);
            testBool = editTestSch.getTagAddedStatus();
            Assert::AreEqual(false, testBool);
            testBool = editTestSch.getTagRemovedStatus();
            Assert::AreEqual(false, testBool);

			string testEntryComponents = " 17 name yeah man. place here and there";
			int testEntryNumber = editTestSch.getEntryNumber(testEntryComponents);
			Assert::AreEqual(17, testEntryNumber);
			string expectedString = "name yeah man. place here and there";
			Assert::AreEqual(expectedString, testEntryComponents);

			testEntryComponents = "yeah man. place here and there";
			EntryEdit::_NEW_CHANGES testChange;
			bool isEndOfEdit;
			editTestSch.extractName(testEntryComponents, testChange, isEndOfEdit);
			expectedString = "place here and there";
			Assert::AreEqual(expectedString, testEntryComponents);
		}

		TEST_METHOD(UndoActionsTest) {
			UndoActions testUndo;
			UndoActions::_ACTION_TO_UNDO testAction;
			testAction._isScheduled = true;
			testAction._counterCommand = UndoActions::Delete;
			testAction._indexNumber = 1;
			vector<Entry> testSched;
			vector<Entry> testFloat;
			Entry dummy;
			testSched.push_back(dummy);
			unsigned int expectedSize = 1;
			Assert::AreEqual(expectedSize, testSched.size());
			testUndo.undoAdd(testAction, testSched, testFloat);
			expectedSize = 0;
			Assert::AreEqual(expectedSize, testSched.size());

			testAction._counterCommand = UndoActions::Add;
			testUndo.undoDelete(testAction, testSched, testFloat);
			expectedSize = 1;
			Assert::AreEqual(expectedSize, testSched.size());
		}

		//@author A0100750Y
		TEST_METHOD(EntryTest) {
			Entry testInfo;
		
			//test for name
			testInfo.insertName("dinner with me");
			string actualAnswer = testInfo.getName();	
			string expectedAnswer = "dinner with me";
			Assert::AreEqual(expectedAnswer, actualAnswer);
			
			//test for entryNumber
			testInfo.insertEntryNumber(1);
			int b=testInfo.getEntryNumber();
			Assert::AreEqual(1, b);

			//test for location
			testInfo.insertLocation("utown");
			actualAnswer=testInfo.getLocation();	
			expectedAnswer = "utown";
			Assert::AreEqual(expectedAnswer, actualAnswer);
		}

		TEST_METHOD(TestUITest) {
			string testInfo = "edit dinner with me";
			TextUI line(testInfo);
			string expectedCommandWord = "edit";
			string actualCommandWord = line.findCommand(testInfo);
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

		//@author A0100750Y
		//test on editEntry tag for floating tasks
		TEST_METHOD(EntryListEditNameFloatingTest) {		
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

		//test on editEntry name for scheduled tasks
		TEST_METHOD(EntryListEditNameTest) {
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

		//editEntry tag for floating
		TEST_METHOD(EntryListEditTagFloatingTest) {		
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
			testInfo.addEntry(testScheduled, dummyNumber);			

			string dummyString;
			string userInput = "1 add #play. remove #study";		
			testInfo.editEntry(true, userInput, dummyString);		
			string actualResult;
			vector<Entry> dummyEntry = testInfo.getScheduledList();
			testScheduled = dummyEntry.back();
			actualResult = testScheduled.getTags();		

			Assert::AreEqual(expectedAnswer,actualResult);	
		}
		
		//tests on editEntry loc for floating tasks
		TEST_METHOD(EntryListEditLocFloatingTest) {		
			string expectedAnswer = "yih";
			
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

		//removeEntry for scheduled and floating
		TEST_METHOD(EntryListsRemoveTest) {
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

		//@author A0115902N
		//tests on DateTimeInspector
		TEST_METHOD(DateTimeInspectorTest) {
			DateTimeInspector aDay;
			Assert::IsTrue(aDay.dateIsValid(31, 03, 2014));			
			Assert::IsTrue(aDay.timeIsValid(12,59));
			Assert::IsFalse(aDay.timeIsValid(25,10));
			Assert::IsFalse(aDay.timeIsValid(20,61));
		}
		
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