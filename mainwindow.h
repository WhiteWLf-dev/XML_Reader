#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDomElement>
#include <QFile>
#include <QXmlStreamReader>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void testFunc(QDomElement element);

private slots:
    void on_action_Exit_triggered();

    void on_action_Exit_2_triggered();

private:
    Ui::MainWindow *ui;
    QDomDocument temp;
   // void extract(const QDomNode& a);

};
#endif // MAINWINDOW_HPP
