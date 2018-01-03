//
//  dialog.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#ifndef dialog_h
#define dialog_h

#include <QDialog>
#include <QThread>
#include <string>

using namespace std;

class QApplication;
class QScrollArea;
class QGridLayout;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QLineEdit;
class QPixmap;
class QPMovie;
class dialog_controller;

class dialog : public QDialog
{
    Q_OBJECT
    QThread workerThread;

public:
    dialog(QWidget *parent = 0, QApplication* app = 0);
    ~dialog();

signals:
    void appendLog(const QString& log);
    void updateBlockChainList();

// Below functions are Qt internal only, don't call them directly.
public slots:
    void handleAppendLog(const QString &);
    void handleUpdateBlockChainList();

private slots:
    void addBlock();

private:
    QLabel *m_addBlockLabel, *m_blockChainTitleLabel, *m_blockChainListLabel, *m_logLabel;
    QApplication *m_app;
    QGridLayout *m_mainLayout;
    QHBoxLayout *m_addBlockLayout;
    QVBoxLayout *m_blockChainListLayout;
    QScrollArea *m_logScrollArea, *m_blockChainScrollArea;
    QPushButton *m_addBlockButton;
    QLineEdit *m_addBlockNameEdit;
    QMovie *m_loadingMovie;
    QPixmap *m_tickPix;

    dialog_controller *m_controller;
};

class dialog_controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
    
public slots:
    void operateAppendLog(const QString& log);
    void operateUpdateBlockChainList();

signals:
    void resultReadyAppendLog(const QString& log);
    void resultReadyUpdateBlockChainList();
};

#endif /* dialog_h */
