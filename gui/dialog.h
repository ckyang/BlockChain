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
#include <unordered_map>

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
class block;

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
    void accumulateVerify(const QString& hash);

// Below functions are Qt internal only, don't call them directly.
public slots:
    void handleAppendLog(const QString &);
    void handleUpdateBlockChainList();
    void handleAccumulateVerify(const QString&);

private slots:
    void verifyBlock();

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
    unordered_map<string, pair<int, block*>> m_verifyBlockHash;

    dialog_controller *m_controller;
};

class dialog_controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
    
public slots:
    void operateAppendLog(const QString& log);
    void operateUpdateBlockChainList();
    void operateAccumulateVerify(const QString& hash);

signals:
    void resultReadyAppendLog(const QString& log);
    void resultReadyUpdateBlockChainList();
    void resultReadyAccumulateVerify(const QString& hash);
};

#endif /* dialog_h */
