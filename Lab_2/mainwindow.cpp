#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::findLesson() {
    QString logStr = "You entered: ";
    QString userRequest = ui->editSearch->text();
    ui->textOut->append(logStr.append(userRequest));

    recordStruct filter;
    char subjectName_c[16];
    char lessonType_c[16];
    char *userRequest_c = new char[userRequest.length() + 1];
    strcpy(userRequest_c, userRequest.toStdString().c_str());
    sscanf(userRequest_c, "%[^;];%[^;];%d", subjectName_c, lessonType_c, &filter.classroom);
    delete[] userRequest_c;
    filter.lessonType = myCSV_file.getLesson(lessonType_c);
    filter.subjectName = subjectName_c;

    printLessonsRecords(myCSV_file.filterRecords(filter));
}

void MainWindow::printLessonsRecords(vector<recordStruct> lessonRecords){
    for (recordStruct record : lessonRecords) {            //function for printing all records in recordStruct vector
        QString outStr;
        outStr.sprintf("%-2d %-15s %-10s %-5d\n", record.num, record.subjectName.c_str(), myCSV_file.getLesson(record.lessonType).c_str(), record.classroom);
        ui->textOut->append(outStr);
    }
}

void MainWindow::on_chooseFile_clicked() {
    myCSV_file.fileName = QFileDialog::getOpenFileName(this, "Open a .csv file", QDir::currentPath()).toStdString();
    if (!myCSV_file.openFile()){
        QMessageBox::information(this,"Failed to open file ",QString::fromStdString(myCSV_file.fileName));
        return;
    }
    QMessageBox::information(this,"Opened file ", QString::fromStdString(myCSV_file.fileName));
    string fillReturnVal = myCSV_file.fillLessonsVector();
    if (fillReturnVal.length()){
        fillReturnVal.insert(0, "Error in line");
        ui->textOut->append(QString::fromStdString(fillReturnVal));
        return;
    }

    ui->textOut->append("Sorted by classroom records");
    printLessonsRecords(myCSV_file.sortLessonsVector());



    myCSV_file.printSortedRecordsInFile();
}

