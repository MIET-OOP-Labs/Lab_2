#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>


#include "fileHandler.h"
#include "searchHandler.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void findLesson();

private slots:
    void on_chooseFile_clicked();

private:
    Ui::MainWindow *ui;

    fileHandler myCSV_file;
    searchHandler mySearch;
    void printLessonsRecords(vector<recordStruct> lessonRecords);
};
#endif // MAINWINDOW_H
