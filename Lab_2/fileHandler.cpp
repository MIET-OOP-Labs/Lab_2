#include "fileHandler.h"

fileHandler::fileHandler() {
}

vector<string> fileHandler::split(const string& str, char delim) {
    vector<string> tokens;
    if (!str.empty()) {
        size_t start = 0;
        size_t end = 0;
        do {
            end = str.find(delim, start);
            tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != string::npos);
    }

    return tokens;
}

lessonTypesEnum fileHandler::getLesson(string lessonStr){
    lessonTypesEnum lesson = none;
    if (!lessonStr.compare("Lection")) {
        lesson = Lection;
    } else if (!lessonStr.compare("Practice")) {
        lesson = Practice;
    } else if (!lessonStr.compare("Lab")) {
        lesson = Lab;
    } else if (!lessonStr.compare("Exam")) {
        lesson = Exam;
    }
    return lesson;
}

string fileHandler::getLesson(lessonTypesEnum lesson){       //functions to convert enum type of lessons to string and vice-versa
    switch (lesson) {
    case Lection:   return "Lection";
    case Practice:   return "Practice";
    case Lab:   return "Lab";
    case Exam:   return "Exam";
    default: return "None";
    }
}
 //comparison function object for sorting records by classroom

vector<recordStruct> fileHandler::filterRecords(recordStruct filter){   //filter all records by filter struct. It will be also checked, if some parametr in filter isn't used
    vector<recordStruct> returnVec;
    for (recordStruct record : lessonsFileRecords) {
        bool subjectEqual = (!record.subjectName.compare(filter.subjectName)) || (!filter.subjectName.compare(" ")); //check if subjects are equal or subject name in filter is empty, which means this parametr isn't used
        bool lessonTypeEqual = (record.lessonType == filter.lessonType) || (!filter.lessonType);                //check if lesson types are equal or lesson type in filter is none (none in lessonTypesEnum = 0)
        bool classroomEqual = (record.classroom == filter.classroom) || (!filter.classroom);                    //check if classrooms are equal or classroom in filter is null
        if (subjectEqual && lessonTypeEqual && classroomEqual) {
            returnVec.push_back(record);
        }
    }
    return returnVec;
}

void fileHandler::printSortedRecordsInFile(){
    string sortedFileName = fileName.substr(0,fileName.find_last_of('/')+1).append("sorted.csv");
    ofstream sortedFile(sortedFileName);

    for (recordStruct record : lessonsFileRecords) {//function for printing all records in recordStruct vector
        char buff[64] = "";
        sprintf(buff, "%d;%s;%s;%d", record.num, record.subjectName.c_str(), getLesson(record.lessonType).c_str(), record.classroom);
        string foo = string(buff);
        sortedFile << foo << endl;       // Write to the file
    }
    sortedFile.close();
}

bool fileHandler::openFile(){
    file.open(fileName);
    if (!file.is_open()) {
        fileOpened = false;
        return fileOpened;
    }
    fileOpened = true;
    return fileOpened;
}


bool fileHandler::getRecord(vector<string> str, recordStruct *record){
    if (str.size() != 4) {
        return false;
    }
    record->num = stoi(str[0]);
    record->subjectName = str[1];
    record->lessonType = getLesson(str[2]);                 //function for filling record struct from string-line, taken from .csv file
    record->classroom = stoi(str[3]);
    return true;
}

string fileHandler::fillLessonsVector(){
    if(!fileOpened){
        return "";
    }
    vector<string> row;                         //vector that stores splitted line from .csv file
    string line;
    while(getline(file, line)) {
        row.clear();
        row = split(line, ';');
        recordStruct currRecord;
        if (!getRecord(row, &currRecord)) {
            return line;
        }
        lessonsFileRecords.push_back(currRecord);
    }
    file.close();
    return "";
}

vector<recordStruct> fileHandler::sortLessonsVector() {
    sort (lessonsFileRecords.begin(), lessonsFileRecords.end(), sortFunc);
    return lessonsFileRecords;
}
