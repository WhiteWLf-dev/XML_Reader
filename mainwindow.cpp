#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_Exit->setIcon(QIcon("C:\\Users\\The Witcher Hunt\\Documents\\lab6XML_Reader\\choose.png"));
    ui->action_Exit_2->setIcon(QIcon("C:\\Users\\The Witcher Hunt\\Documents\\lab6XML_Reader\\exit.jpg"));
    setWindowIcon(QIcon("C:\\Users\\The Witcher Hunt\\Documents\\lab6XML_Reader\\xml.jpg"));
    setWindowTitle("XML Reader");

    QPalette darkPalette;

        // Настраиваем палитру для цветовых ролей элементов интерфейса
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::black);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        // Устанавливаем данную палитру
        qApp->setPalette(darkPalette);

//    connect(ui->selectXMLButton, SIGNAL(clicked()), this, SLOT(on_selectXMLButton_clicked()));
}


//void MainWindow::extract(const QDomNode& a) {
//    QDomNode t=a.firstChild();
//    while(!t.isNull()) {
//        if(t.isElement()) {
//            QDomElement h=t.toElement();
//            if(!h.isNull()) {
//                QString name;
//                QString text;
//                qDebug()<<h.text();
//                if(h.tagName()=="log") {
//                    QDomNode node=h.firstChild();
////                    QString name;
////                    QString text;
//                    while(!node.isNull()) {
//                        QDomElement e=node.toElement();
//                        if(!e.isNull()) {
//                            if(e.tagName()=="name") {
//                                name=e.text();
//                            } else if(e.tagName()=="message") {
//                                text=e.text();
//                            }
//                        }
//                        node=node.nextSibling();
//                    }
////                    ui->messageList->append(name);
////                    ui->messageList->append(text);
////                    qDebug()<<"F";
////                    ui->messageList->append(domElement.text());
////                    qDebug()<<"da";
//                }
//                ui->messageList->append(name);
//                ui->messageList->append(text);
//                qDebug()<<"F";
//            }
//        }
////        addFromXML(domNode);
//        t=t.nextSibling();
//    }
//}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_action_Exit_triggered()
{
    //Выбор файла, диалгговое окно, потом создаем QDomElement и т.п.
    //Сохраняем его в поле класса и вызываем отдельный метод выгрузки данных в QTextEdit
    QString  a = QFileDialog::getOpenFileName(this, tr("Open XML"), "C:\\Users\\The Witcher Hunt\\Desktop", tr("XML Files (*.xml)"));
    if (!a.isEmpty()){
    QFile file(a);
    if(file.open(QIODevice::ReadOnly)) {
        if(temp.setContent(&file)) {
//            QDomElement domElement=domDoc.documentElement();
//            addFromXML(domElement);
            QDomElement topElement=temp.documentElement();
            QDomNode domNode=topElement.firstChild();
            while(!domNode.isNull()) {
                QDomElement domElement=domNode.toElement();
                if(domElement.tagName()=="log") {
                    QDomNode node=domElement.firstChild();
                    while(!node.isNull()) {
                        QDomElement element=node.toElement();
                        if(!element.isNull()) {
                            QString log;
                            QString tagName(element.tagName());
                            if(tagName=="name") {

                                log.append("<strong>"+element.text()+"</strong>: ");
                                if(node.nextSiblingElement().tagName()=="ip") {
                                    log.prepend("["+node.nextSiblingElement().text()+"] ");

                                }
                                if(node.nextSibling().nextSiblingElement().tagName()=="dateAndTime") {
                                    log.prepend(node.nextSibling().nextSiblingElement().text());
                                }
                                if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="message") {
                                    log.append(node.nextSibling().nextSibling().nextSiblingElement().text());
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="serverMessage") {
                                    log.append("<em>"+node.nextSibling().nextSibling().nextSiblingElement().text()+"<\em>");
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="formattedMessage") {
                                    QString message=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(")")+1);
                                    QString color=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf("(")+1, node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(",")-1);

                                    QString font=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(",")+1, node.nextSibling().nextSiblingElement().text().indexOf(")")-2);

                                    QString weight=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSiblingElement().text().indexOf(")")-2, node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(")"));

                                    log.append("<font color="+color/*+" font-size="+weight+" font-family="+font+*/+">"+message+"</font>");
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="imageMessage") {
                                    ui->messageList->append(log);
                                    QImage image=QImage::fromData(QByteArray::fromBase64(node.nextSibling().nextSibling().nextSiblingElement().text().toUtf8()), "PNG");
                                    QImage image_new=image.scaled(320,240);
                                    QTextCursor newCursor=ui->messageList->textCursor();
                                    newCursor.movePosition(QTextCursor::End);
                                    ui->messageList->setTextCursor(newCursor);
                                    ui->messageList->textCursor().insertBlock();
                                    ui->messageList->textCursor().insertImage(image_new);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="fileMessage") {
                                    QString filename;
                                    QString md5;
//                                    filename=node.nextSibling().nextSibling().nextSiblingElement().text().left(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(","));
//                                    md5=node.nextSibling().nextSibling().nextSiblingElement().text().right(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(",")+1);
                                    log.append(node.nextSibling().nextSibling().nextSiblingElement().text());
                                    ui->messageList->append(log);
                                }
                            } else if(tagName=="message") {

                            } else if(tagName=="serverMessage") {

                            }
                        }
                        node=node.nextSibling();
                    }
                }
                domNode=domNode.nextSibling();
            }
        }
        file.close();}

//        QDomElement root=domDoc.documentElement();
//        QDomNode node=root.firstChild();
//        while(!node.isNull()) {
//            if(node.toElement().tagName()=="logs") {
//                testFunc(node.toElement());
//                node=node.nextSibling();
//            }
//        }

//        QDomNodeList logs=root.elementsByTagName("log");
//        for(std::size_t i=0; i<logs.count(); ++i) {
//            QDomNode log=logs.at(i);
//            if(log.isElement()) {
//                QDomElement message=log.toElement();
//                qDebug()<<"In main:"<<message.attribute("name");
//                testFunc(message, "log", "name");
//            }
//        }
    }
}


void MainWindow::on_action_Exit_2_triggered()
{
    this->close();
}

