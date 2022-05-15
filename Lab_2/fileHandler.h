#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef enum lessonTypesEnum {none, Lection, Practice, Lab, Exam};  //enumeration of types of lessons

typedef struct {
    int num;
    string subjectName;
    lessonTypesEnum lessonType; //structure that stores info about each record of lessons
    int classroom;
} recordStruct;

class fileHandler {
    vector<recordStruct> lessonsFileRecords;    //vector that stores all lesson records
    static bool sortFunc (recordStruct i,recordStruct j) { return (i.classroom < j.classroom);}
    bool getRecord(vector<string> str, recordStruct *record);
    ifstream file;
    bool fileOpened = false;

public:
    fileHandler();
    string fileName;
    vector<string> split(const string& str, char delim);
    vector<recordStruct> filterRecords(recordStruct filter);
    void printSortedRecordsInFile();
    bool openFile();
    string fillLessonsVector();
    string getLesson(lessonTypesEnum lesson);
    vector<recordStruct> sortLessonsVector();
    lessonTypesEnum getLesson(string lessonStr);
};

#endif // FILEHANDLER_H
