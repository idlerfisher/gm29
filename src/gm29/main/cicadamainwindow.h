#ifndef CICADAMAINWINDOW_H
#define CICADAMAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QMainWindow>

class CDaoYouGmUi;

namespace Ui {
class CicadaMainWindow;
}

class CicadaMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CicadaMainWindow(QWidget *parent = 0);
    ~CicadaMainWindow();

private slots:
    void slotQuit();
    void slotTest();
    void slotAbout();
    
private:
    Ui::CicadaMainWindow *ui;
    CDaoYouGmUi* m_pDyGmUi;
};

#endif // CICADAMAINWINDOW_H
