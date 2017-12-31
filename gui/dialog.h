//
//  dialog.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#ifndef dialog_h
#define dialog_h

#include <QDialog>
#include <string>

using namespace std;

class QApplication;
class QScrollArea;
class QGridLayout;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;

class dialog : public QDialog
{
    Q_OBJECT

public:
    dialog(QWidget *parent = 0, QApplication* app = 0);
    ~dialog();

    void updateBlockChainList();
    void appendLog(const string& log);

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
};

#endif /* dialog_h */
